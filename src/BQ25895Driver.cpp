#include "BQ25895Driver.h"

#if defined(ARDUINO)
// Arduino-specific time function
unsigned long millis();
#else
// Mock time functions for testing (defined in test files)
extern unsigned long mock_millis;
extern unsigned long millis();
#endif

#if defined(ARDUINO)
#include <Arduino.h>
#include <cmath>
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINTF(fmt, ...) Serial.printf(fmt, __VA_ARGS__)
#define PLATFORM_DELAY(ms) delay(ms)
#define HEX 16
#else
#include <cstdio>
#include <cmath>
#include <thread>
#include <chrono>
#define DEBUG_PRINT(x) printf("%s", String(x).c_str())
#define DEBUG_PRINTLN(x) printf("%s\n", String(x).c_str())
#define DEBUG_PRINTF(fmt, ...) printf(fmt, __VA_ARGS__)
#define PLATFORM_DELAY(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
#define HEX 16
#endif

// Constructor
BQ25895Driver::BQ25895Driver(Adafruit_I2CDevice* i2c_dev) : i2c_dev_(i2c_dev) {
    if (!i2c_dev_) {
        setError("I2C device is null");
    }
}

// Initialization and configuration
bool BQ25895Driver::initialize(const BQ25895Config& config) {
    if (!i2c_dev_) {
        setError("I2C device not available");
        return false;
    }
    
    // Initialize the I2C device
    if (!i2c_dev_->begin()) {
        setError("Failed to initialize I2C device");
        return false;
    }
    
    config_ = config;
    initialized_ = false;
    emergencyMode_ = false;
    lastError_ = "";
    
    DEBUG_PRINTLN("=== BQ25895 Initialization ===");
    
    // Step 1: Verify device communication
    if (!verifyDevice()) {
        setError("Device verification failed");
        return false;
    }
    
    // Step 2: Clear any existing faults (mark as initialized temporarily for this operation)
    initialized_ = true;
    clearFaults();
    
    // Step 3: Disable watchdog timer if requested
    if (config_.disableWatchdog) {
        if (!updateRegisterBits(REG07_MISC_OPERATION, WATCHDOG_MASK, WATCHDOG_DISABLE << WATCHDOG_SHIFT)) {
            setError("Failed to disable watchdog timer");
            initialized_ = false;
            return false;
        }
        DEBUG_PRINTLN("Watchdog timer disabled");
    }
    
    // Step 4: Disable safety timer if requested
    if (config_.disableSafetyTimer) {
        if (!updateRegisterBits(REG05_TIMER, 0x08, 0x08)) {
            setError("Failed to disable safety timer");
            initialized_ = false;
            return false;
        }
        DEBUG_PRINTLN("Safety timer disabled");
    }
    
    // Step 5: Configure VINDPM threshold
    uint8_t vindpmReg = 0x80; // Force VINDPM enabled
    vindpmReg |= ((config_.vindpmThresholdMV - 2600) / 100) & 0x0F;
    if (!writeRegisterWithRetry(REG0D_VINDPM, vindpmReg)) {
        setError("Failed to set VINDPM threshold");
        initialized_ = false;
        return false;
    }
    DEBUG_PRINTF("Set VINDPM threshold to %dmV\n", config_.vindpmThresholdMV);
    
    // Step 6: Set input current limit (driver is now marked as initialized)
    if (!setInputCurrentLimit(config_.inputCurrentMA)) {
        setError("Failed to set input current limit");
        initialized_ = false;
        return false;
    }
    
    // Step 7: Set charge current
    if (!setChargeCurrent(config_.chargeCurrentMA)) {
        setError("Failed to set charge current");
        initialized_ = false;
        return false;
    }
    
    // Step 8: Set charge voltage
    if (!setChargeVoltage(config_.chargeVoltageNV)) {
        setError("Failed to set charge voltage");
        initialized_ = false;
        return false;
    }
    
    // Step 9: Set termination current
    if (!setTerminationCurrent(config_.terminationCurrentMA)) {
        setError("Failed to set termination current");
        initialized_ = false;
        return false;
    }
    
    // Initialization successful
    initialized_ = true;
    DEBUG_PRINTLN("BQ25895 initialization complete!");
    
    return true;
}

bool BQ25895Driver::isInitialized() const {
    return initialized_;
}

void BQ25895Driver::reset() {
    initialized_ = false;
    emergencyMode_ = false;
    lastError_ = "";
}

void BQ25895Driver::factoryReset() {
    if (!i2c_dev_) {
        setError("I2C device not available");
        return;
    }
    
    DEBUG_PRINTLN("Performing factory reset...");
    
    // Send reset command
    writeRegisterWithRetry(REG14_RESET, 0x80);
    
    // Wait for reset to complete (simulated delay)
    #if defined(ARDUINO)
    PLATFORM_DELAY(500);
    #endif
    
    DEBUG_PRINTLN("Factory reset complete");
    
    reset(); // Mark as uninitialized
}

// Status and measurements
BQ25895Status BQ25895Driver::getStatus() {
    BQ25895Status status;
    status.timestamp = millis();
    
    if (!initialized_) {
        setError("Driver not initialized");
        status.lastError = lastError_;
        return status;
    }
    
    uint8_t value;
    
    // Read system status register (REG0B)
    if (readRegisterWithRetry(REG0B_SYSTEM_STATUS, value)) {
        status.vbusType = static_cast<VBusType>((value & VBUS_STAT_MASK) >> VBUS_STAT_SHIFT);
        status.chargeStatus = static_cast<ChargeStatus>((value >> 3) & 0x03);
        status.inputDetected = (status.vbusType != VBusType::NONE);
        status.chargingEnabled = (status.chargeStatus != ChargeStatus::NOT_CHARGING);
        
        // Minimal safety intervention - let the BQ25895 work autonomously
        // Trust the IC's built-in protections and detection
    }
    
    // Read fault register (read twice to get current status)
    readRegisterWithRetry(REG0C_FAULT, value); // Clear latched faults
    if (readRegisterWithRetry(REG0C_FAULT, value)) {
        status.faultRegister = value;
        status.watchdogFault = (value & 0x80) != 0;
        status.chargeFault = (value & 0x30) != 0;
        status.batteryFault = (value & 0x08) != 0;
        status.ntcFault = (value & 0x07) != 0;
    }
    
    status.lastError = lastError_;
    return status;
}

BQ25895Metrics BQ25895Driver::getMetrics() {
    BQ25895Metrics metrics;
    metrics.timestamp = millis();
    
    if (!initialized_) {
        setError("Driver not initialized");
        return metrics;
    }
    
    // Start ADC conversion
    writeRegisterWithRetry(0x02, 0x80);
    
    #if defined(ARDUINO)
    PLATFORM_DELAY(20); // Wait for conversion
    #endif
    
    uint8_t value;
    
    // Read battery voltage (REG0E)
    if (readRegisterWithRetry(REG0E_BATV, value)) {
        metrics.batteryVoltage = 2304 + (value & 0x7F) * 20; // mV
    }
    
    // Read system voltage (REG0F)
    if (readRegisterWithRetry(REG0F_SYSV, value)) {
        metrics.systemVoltage = 2304 + (value & 0x7F) * 20; // mV
    }
    
    // Read input voltage (REG11)
    if (readRegisterWithRetry(REG11_VBUSV, value)) {
        metrics.inputVoltage = 2600 + (value & 0x7F) * 100; // mV
    }
    
    // Read charge current (REG12)
    if (readRegisterWithRetry(REG12_ICHGR, value)) {
        metrics.chargeCurrentMA = (value & 0x7F) * 50; // mA
    }
    
    // Read thermistor voltage (REG10)
    if (readRegisterWithRetry(REG10_TSPCT, value)) {
        // TS voltage calculation: VREGN * (REG10[6:0] / 127)
        metrics.tsVoltage = (uint16_t)((5000.0 * (value & 0x7F)) / 127.0);
    }
    
    return metrics;
}

void BQ25895Driver::updateAll() {
    // Updates both status and metrics (for future caching implementation)
    getStatus();
    getMetrics();
}

// Charging control
bool BQ25895Driver::enableCharging() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    return updateRegisterBits(REG03_CHARGE_CONFIG, 0x10, 0x10); // Set CHG_CONFIG bit
}

bool BQ25895Driver::disableCharging() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    return updateRegisterBits(REG03_CHARGE_CONFIG, 0x10, 0x00); // Clear CHG_CONFIG bit
}

bool BQ25895Driver::setChargeCurrent(uint16_t currentMA) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    // BQ25895 charge current calculation: ICHG = 0mA + ICHG[6:0] × 64mA
    // Min: 0mA, Max: 8064mA, Step: 64mA
    uint8_t regValue = (currentMA / 64) & 0x7F;
    
    return writeRegisterWithRetry(REG04_CHARGE_CURRENT, regValue);
}

bool BQ25895Driver::setInputCurrentLimit(uint16_t currentMA) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    // BQ25895 input current limit calculation
    // Base: 100mA, Step: 50mA up to 3.25A
    uint8_t regValue;
    if (currentMA <= 100) {
        regValue = 0x00;
    } else if (currentMA <= 3250) {
        regValue = ((currentMA - 100) / 50) & 0x3F;
    } else {
        regValue = 0x3F; // Maximum
    }
    
    return writeRegisterWithRetry(REG00_INPUT_CURRENT, regValue);
}

bool BQ25895Driver::setChargeVoltage(uint16_t voltageMV) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    // BQ25895 charge voltage calculation: VREG = 3.840V + VREG[7:2] × 16mV
    // Min: 3.840V, Max: 4.848V, Step: 16mV
    // Note: Voltage field is in bits 7:2, not 5:0
    uint8_t voltageField = ((voltageMV - 3840) / 16) & 0x3F;
    
    // Read current register to preserve other bits
    uint8_t currentReg06;
    if (!readRegisterWithRetry(REG06_CHARGE_VOLTAGE, currentReg06)) {
        setError("Failed to read current charge voltage register");
        return false;
    }
    
    // Set voltage field in bits 7:2, preserve other bits
    uint8_t newReg06 = (currentReg06 & 0x03) | (voltageField << 2);
    
    DEBUG_PRINTF("Setting charge voltage: %dmV (field=0x%02X, reg=0x%02X->0x%02X)\n", 
                 voltageMV, voltageField, currentReg06, newReg06);
    
    return writeRegisterWithRetry(REG06_CHARGE_VOLTAGE, newReg06);
}

bool BQ25895Driver::setTerminationCurrent(uint16_t currentMA) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    // BQ25895 termination current calculation: ITERM = 64mA + ITERM[3:0] × 64mA
    // Min: 64mA, Max: 1024mA, Step: 64mA
    uint8_t itermValue;
    if (currentMA <= 64) {
        itermValue = 0x00;
    } else if (currentMA <= 1024) {
        itermValue = ((currentMA - 64) / 64) & 0x0F;
    } else {
        itermValue = 0x0F; // Maximum (1024mA)
    }
    
    // Read current REG05 value to preserve other bits
    uint8_t regValue;
    if (!readRegisterWithRetry(REG05_TIMER, regValue)) {
        setError("Failed to read REG05 for ITERM setting");
        return false;
    }
    
    // Clear ITERM bits (3:0) and set new value
    regValue = (regValue & 0xF0) | itermValue;
    
    return writeRegisterWithRetry(REG05_TIMER, regValue);
}

// VBUS and power management
VBusType BQ25895Driver::getVBusType() {
    if (!initialized_) {
        return VBusType::NONE;
    }
    
    uint8_t value;
    if (readRegisterWithRetry(REG0B_SYSTEM_STATUS, value)) {
        return static_cast<VBusType>((value & VBUS_STAT_MASK) >> VBUS_STAT_SHIFT);
    }
    
    return VBusType::NONE;
}

String BQ25895Driver::getVBusTypeName(VBusType type) {
    switch (type) {
        case VBusType::NONE: return "No Input";
        case VBusType::USB_SDP: return "USB SDP (500mA)";
        case VBusType::USB_CDP: return "USB CDP (1.5A)";
        case VBusType::USB_DCP: return "USB DCP (3.25A)";
        case VBusType::HVDCP: return "HVDCP (1.5A)";
        case VBusType::UNKNOWN: return "Unknown (500mA)";
        case VBusType::NON_STANDARD: return "Non-Standard";
        case VBusType::OTG: return "OTG Mode";
        default: return "Invalid";
    }
}

bool BQ25895Driver::isExternalPowerPresent() {
    return getVBusType() != VBusType::NONE;
}

// Fault management
bool BQ25895Driver::clearFaults() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    uint8_t faultReg;
    if (readRegisterWithRetry(REG0C_FAULT, faultReg) && faultReg != 0) {
        DEBUG_PRINTF("Clearing BQ25895 faults: 0x%02X\n", faultReg);
        
        // Decode fault bits for debugging
        if (faultReg & 0x80) DEBUG_PRINTLN("  - WATCHDOG_FAULT");
        if (faultReg & 0x40) DEBUG_PRINTLN("  - OTG_FAULT");
        if (faultReg & 0x30) DEBUG_PRINTLN("  - CHRG_FAULT");
        if (faultReg & 0x08) DEBUG_PRINTLN("  - BAT_FAULT");
        if (faultReg & 0x07) DEBUG_PRINTLN("  - NTC_FAULT");
    }
    
    // Clear faults by re-writing key registers
    writeRegisterWithRetry(REG00_INPUT_CURRENT, 0x08); // Reset input current config
    writeRegisterWithRetry(REG03_CHARGE_CONFIG, 0x1A); // Reset charge config
    
    // Force ADC conversion to reset ADC-related faults
    writeRegisterWithRetry(0x02, 0x80);
    
    DEBUG_PRINTLN("Fault clearing complete");
    return true;
}

uint8_t BQ25895Driver::getFaultRegister() {
    if (!initialized_) {
        return 0xFF;
    }
    
    uint8_t value;
    // Read twice to get current fault status
    readRegisterWithRetry(REG0C_FAULT, value); // Clear latched faults
    if (readRegisterWithRetry(REG0C_FAULT, value)) {
        return value;
    }
    
    return 0xFF;
}

String BQ25895Driver::decodeFaults(uint8_t faultReg) {
    if (faultReg == 0) {
        return "No faults";
    }
    
    String result = "";
    if (faultReg & 0x80) result += "Watchdog ";
    if (faultReg & 0x40) result += "OTG ";
    if (faultReg & 0x30) result += "Charge ";
    if (faultReg & 0x08) result += "Battery ";
    if (faultReg & 0x07) result += "NTC ";
    
    if (result.length() > 0) {
#if defined(ARDUINO)
        result = result.substring(0, result.length() - 1); // Remove trailing space
#else
        result = result.substr(0, result.length() - 1); // Remove trailing space
#endif
        result += " fault(s)";
    }
    
    return result;
}

// Emergency modes
bool BQ25895Driver::enterEmergencyBatteryMode() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    DEBUG_PRINTLN("Entering emergency battery mode...");
    
    // Disable charging completely
    if (!writeRegisterWithRetry(REG03_CHARGE_CONFIG, 0x00)) {
        setError("Failed to disable charging");
        return false;
    }
    
    // Disable input current detection
    if (!writeRegisterWithRetry(REG00_INPUT_CURRENT, 0x01)) {
        setError("Failed to set minimum input current");
        return false;
    }
    
    // Disable VBUS detection
    if (!writeRegisterWithRetry(REG0D_VINDPM, 0x80)) {
        setError("Failed to disable VBUS detection");
        return false;
    }
    
    // Disable USB detection circuits
    if (!writeRegisterWithRetry(REG07_MISC_OPERATION, 0x40)) {
        setError("Failed to disable USB detection");
        return false;
    }
    
    // Clear fault register
    uint8_t dummy;
    readRegisterWithRetry(REG0C_FAULT, dummy);
    
    emergencyMode_ = true;
    DEBUG_PRINTLN("Emergency battery mode activated");
    
    return true;
}

bool BQ25895Driver::exitEmergencyMode() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    emergencyMode_ = false;
    
    // Re-initialize with current configuration
    return initialize(config_);
}

bool BQ25895Driver::isInEmergencyMode() const {
    return emergencyMode_;
}

// Watchdog management
bool BQ25895Driver::disableWatchdog() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    return updateRegisterBits(REG07_MISC_OPERATION, WATCHDOG_MASK, WATCHDOG_DISABLE << WATCHDOG_SHIFT);
}

bool BQ25895Driver::resetWatchdog() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    return updateRegisterBits(REG05_TIMER, 0x40, 0x40); // Set WD_RST bit
}

// Ship mode (low power)
bool BQ25895Driver::enterShipMode() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    DEBUG_PRINTLN("Entering ship mode...");
    
    // Set BATFET_DIS bit to enter ship mode
    return writeRegisterWithRetry(REG09_NEW_FAULT, 0x20);
}

// Power management and transitions
bool BQ25895Driver::checkStartupScenario(bool externalPowerPresent) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    logWithTimestamp("Checking startup scenario...");
    
    if (externalPowerPresent) {
        logWithTimestamp("USB startup detected - normal operation");
        return true;
    } else {
        logWithTimestamp("Battery startup detected - entering emergency mode");
        return enterEmergencyBatteryMode();
    }
}

bool BQ25895Driver::handleUSBReconnection(bool externalPowerPresent) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    unsigned long now = millis();
    
    // Detect USB reconnection
    if (externalPowerPresent && !usbReconnectionInProgress_) {
        usbReconnectionInProgress_ = true;
        usbReconnectionStartTime_ = now;
        logWithTimestamp("USB reconnection detected - starting recovery");
        return true;
    }
    
    // Handle ongoing reconnection
    if (usbReconnectionInProgress_) {
        // Wait 2 seconds for system to stabilize
        if (now - usbReconnectionStartTime_ < 2000) {
            return true; // Still waiting
        }
        
        // Check if BQ25895 USB detection is working
        uint8_t sysStatus;
        if (!readRegisterWithRetry(REG0B_SYSTEM_STATUS, sysStatus)) {
            logWithTimestamp("USB recovery failed - I2C communication error");
            usbReconnectionInProgress_ = false;
            return false;
        }
        
        uint8_t vbusStatus = (sysStatus >> 5) & 0x07;
        bool bq25895UsbDetected = (vbusStatus != 0x00);
        
        if (externalPowerPresent && !bq25895UsbDetected) {
            logWithTimestamp("USB recovery needed - BQ25895 USB detection broken");
            
            // Reset and re-initialize
            factoryReset();
            #if defined(ARDUINO)
            PLATFORM_DELAY(100);
            #endif
            
            bool initSuccess = initialize(config_);
            if (initSuccess) {
                enableCharging();
                logWithTimestamp("USB recovery complete - BQ25895 reset and reinitialized");
            } else {
                logWithTimestamp("USB recovery failed - initialization error");
            }
            
            usbReconnectionInProgress_ = false;
            return initSuccess;
        } else {
            logWithTimestamp("USB recovery not needed - BQ25895 detection working");
            usbReconnectionInProgress_ = false;
            return true;
        }
    }
    
    return true;
}

bool BQ25895Driver::handlePowerLoss() {
    if (!initialized_ || emergencyMode_) {
        return true; // Skip if not initialized or already in emergency mode
    }
    
    logWithTimestamp("External power lost - performing cleanup");
    
    // Disable charging completely
    if (!writeRegisterWithRetry(REG03_CHARGE_CONFIG, 0x00)) {
        logWithTimestamp("Warning: Failed to disable charging during power loss");
    }
    
    // Disable input current detection
    if (!writeRegisterWithRetry(REG00_INPUT_CURRENT, 0x01)) {
        logWithTimestamp("Warning: Failed to set minimum input current");
    }
    
    // Clear DPDM detection to prevent false USB detection
    if (!writeRegisterWithRetry(REG0D_VINDPM, 0x80)) {
        logWithTimestamp("Warning: Failed to disable DPDM detection");
    }
    
    // Reset VBUS detection circuits
    if (!writeRegisterWithRetry(REG07_MISC_OPERATION, 0x40)) {
        logWithTimestamp("Warning: Failed to reset VBUS detection");
    }
    
    // Clear fault registers
    uint8_t dummy;
    readRegisterWithRetry(REG0C_FAULT, dummy);
    
    logWithTimestamp("Power loss cleanup complete");
    return true;
}

bool BQ25895Driver::prepareForShutdown() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    logWithTimestamp("Preparing for system shutdown");
    
    // Disable all charging and input detection
    writeRegisterWithRetry(REG03_CHARGE_CONFIG, 0x00);
    writeRegisterWithRetry(REG00_INPUT_CURRENT, 0x01);
    
    // Clear USB/VBUS detection to prevent safety circuit conflicts
    writeRegisterWithRetry(REG0D_VINDPM, 0x80);
    writeRegisterWithRetry(REG07_MISC_OPERATION, 0x40);
    
    // Clear all fault conditions
    uint8_t dummy;
    readRegisterWithRetry(REG0C_FAULT, dummy);
    
    logWithTimestamp("Shutdown preparation complete");
    return true;
}

// Enhanced diagnostics
void BQ25895Driver::printExtendedDiagnostics() {
    if (!initialized_) {
        DEBUG_PRINTLN("Driver not initialized for extended diagnostics");
        return;
    }
    
    DEBUG_PRINTLN("=== EXTENDED BQ25895 DIAGNOSTICS ===");
    
    uint8_t reg0B, reg0C, reg06, reg04, reg11, reg12;
    bool success = true;
    
    success &= readRegisterWithRetry(REG0B_SYSTEM_STATUS, reg0B);
    success &= readRegisterWithRetry(REG0C_FAULT, reg0C);
    success &= readRegisterWithRetry(REG06_CHARGE_VOLTAGE, reg06);
    success &= readRegisterWithRetry(REG04_CHARGE_CURRENT, reg04);
    success &= readRegisterWithRetry(REG11_VBUSV, reg11);
    success &= readRegisterWithRetry(REG12_ICHGR, reg12);
    
    if (!success) {
        DEBUG_PRINTLN("ERROR: Failed to read critical registers");
        return;
    }
    
    DEBUG_PRINTF("System Status (REG0B): 0x%02X\n", reg0B);
    DEBUG_PRINTF("  %s\n", decodeSystemStatus(reg0B).c_str());
    
    DEBUG_PRINTF("Fault Status (REG0C): 0x%02X\n", reg0C);
    DEBUG_PRINTF("  %s\n", decodeFaults(reg0C).c_str());
    
    // Charge Voltage Configuration (REG06) - CRITICAL for BATOVP debugging
    uint16_t chargeVoltage = 3840 + (reg06 & 0x3F) * 16;
    uint16_t batovpThreshold = (chargeVoltage * 104) / 100; // 4% above VREG
    DEBUG_PRINTF("Charge Voltage (REG06): 0x%02X (%dmV, BATOVP@%dmV)\n", 
                 reg06, chargeVoltage, batovpThreshold);
    
    // Charge Current Limit (REG04)
    uint16_t chargeCurrentLimit = (reg04 & 0x7F) * 64;
    DEBUG_PRINTF("Charge Current Limit (REG04): 0x%02X (%dmA)\n", 
                 reg04, chargeCurrentLimit);
    
    DEBUG_PRINTF("VBUS Voltage (REG11): 0x%02X (%.2fV)\n", 
                 reg11, (2600 + (reg11 & 0x7F) * 100) / 1000.0);
    
    DEBUG_PRINTF("Charge Current (REG12): 0x%02X (%dmA)\n", 
                 reg12, (reg12 & 0x7F) * 50);
    
    DEBUG_PRINTLN("=====================================");
}

bool BQ25895Driver::disableThermistorMonitoring() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    // IMPORTANT: Thermistor monitoring cannot be disabled via software!
    // VLTF/VHTF are fixed hardware thresholds (percentages of VREGN).
    // The only solution is hardware modification of the resistor network
    // per v2.2-testing-and-analysis.md (R8=6.8kΩ, R9 removed, RT1→3.9kΩ)
    logWithTimestamp("Thermistor monitoring is hardware-controlled and cannot be disabled via registers");
    logWithTimestamp("Hardware modification required: RT1 → 3.9kΩ resistor for proper TS voltage");
    return true;
}

String BQ25895Driver::decodeSystemStatus(uint8_t statusReg) {
    String result = "";
    
    uint8_t vbusStatus = (statusReg >> 5) & 0x07;
    uint8_t chargeStatus = (statusReg >> 3) & 0x03;
    bool dpmStatus = (statusReg >> 2) & 0x01;
    bool pgStatus = (statusReg >> 1) & 0x01;
    bool vsysStatus = statusReg & 0x01;
    
    result += "VBUS: " + decodeVBusStatus(vbusStatus) + ", ";
    
    result += "Charge: ";
    switch (chargeStatus) {
        case 0: result += "Not charging"; break;
        case 1: result += "Pre-charge"; break;
        case 2: result += "Fast charge"; break;
        case 3: result += "Charge termination"; break;
    }
    result += ", ";
    
    result += "DPM: " + String(dpmStatus ? "Active" : "Inactive") + ", ";
    result += "PG: " + String(pgStatus ? "Good" : "Bad") + ", ";
    result += "VSYS: " + String(vsysStatus ? "Regulation" : "Good");
    
    return result;
}

String BQ25895Driver::decodeVBusStatus(uint8_t vbusStatus) {
    switch (vbusStatus) {
        case 0: return "No Input";
        case 1: return "USB SDP";
        case 2: return "USB CDP";
        case 3: return "USB DCP";
        case 4: return "Adjustable";
        case 5: return "Unknown";
        case 6: return "Non-Standard";
        case 7: return "OTG";
        default: return "Invalid";
    }
}

BQ25895Driver::PowerTransition BQ25895Driver::detectVBusChanges() {
    PowerTransition transition;
    
    if (!initialized_) {
        return transition;
    }
    
    VBusType currentVbusType = getVBusType();
    unsigned long now = millis();
    
    if (currentVbusType != lastVbusType_ && (now - lastVbusChangeTime_ > 1000)) {
        transition.stateChanged = true;
        transition.timestamp = now;
        transition.changeDescription = "VBUS: " + getVBusTypeName(lastVbusType_) + 
                                     " -> " + getVBusTypeName(currentVbusType);
        
        lastVbusType_ = currentVbusType;
        lastVbusChangeTime_ = now;
        
        logWithTimestamp(transition.changeDescription + " [Detection may be unreliable]");
    }
    
    return transition;
}

// Removed complex oscillation detection - let the BQ25895 work autonomously

// Configuration and diagnostics
BQ25895Config BQ25895Driver::getConfig() const {
    return config_;
}

String BQ25895Driver::getLastError() const {
    return lastError_;
}

bool BQ25895Driver::performSelfTest() {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    // Verify device communication
    if (!verifyDevice()) {
        setError("Self test failed: device communication error");
        return false;
    }
    
    // Check that we can read/write registers
    uint8_t originalValue, testValue;
    if (!readRegisterWithRetry(REG03_CHARGE_CONFIG, originalValue)) {
        setError("Self test failed: cannot read register");
        return false;
    }
    
    // Write a test value (toggle a safe bit)
    uint8_t newValue = originalValue ^ 0x01; // Toggle LSB
    if (!writeRegisterWithRetry(REG03_CHARGE_CONFIG, newValue)) {
        setError("Self test failed: cannot write register");
        return false;
    }
    
    // Read back and verify
    if (!readRegisterWithRetry(REG03_CHARGE_CONFIG, testValue)) {
        setError("Self test failed: cannot read back test value");
        return false;
    }
    
    // Restore original value
    writeRegisterWithRetry(REG03_CHARGE_CONFIG, originalValue);
    
    if (testValue != newValue) {
        setError("Self test failed: register write/read mismatch");
        return false;
    }
    
    DEBUG_PRINTLN("Self test passed");
    return true;
}

void BQ25895Driver::printRegisters() {
    if (!initialized_) {
        DEBUG_PRINTLN("Driver not initialized");
        return;
    }
    
    DEBUG_PRINTLN("=== BQ25895 REGISTER DUMP ===");
    for (uint8_t reg = 0x00; reg <= 0x14; reg++) {
        uint8_t value;
        if (readRegisterWithRetry(reg, value)) {
            DEBUG_PRINTF("REG%02X: 0x%02X (", reg, value);
            // Print binary representation
            for (int i = 7; i >= 0; i--) {
                DEBUG_PRINT(((value >> i) & 1) ? "1" : "0");
            }
            DEBUG_PRINTLN(")");
        } else {
            DEBUG_PRINTF("REG%02X: READ ERROR\n", reg);
        }
    }
    DEBUG_PRINTLN("=============================");
}

// Register access (for advanced users)
bool BQ25895Driver::readRegister(uint8_t reg, uint8_t& value) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    return readRegisterWithRetry(reg, value, 1); // Single attempt for direct access
}

bool BQ25895Driver::writeRegister(uint8_t reg, uint8_t value) {
    if (!initialized_) {
        setError("Driver not initialized");
        return false;
    }
    
    return writeRegisterWithRetry(reg, value, 1); // Single attempt for direct access
}

// Internal helper methods
bool BQ25895Driver::writeRegisterWithRetry(uint8_t reg, uint8_t value, int maxRetries) {
    if (!i2c_dev_) {
        setError("I2C device not available");
        return false;
    }
    
    for (int attempt = 0; attempt < maxRetries; attempt++) {
        uint8_t buffer[2] = {reg, value};
        if (i2c_dev_->write(buffer, 2)) {
            if (attempt > 0) {
                DEBUG_PRINTF("I2C Write succeeded on attempt %d: reg=0x%02X value=0x%02X\n", 
                            attempt + 1, reg, value);
            }
            return true;
        }
        
        if (attempt < maxRetries - 1) {
            DEBUG_PRINTF("I2C Write retry %d/%d: reg=0x%02X error\n", 
                        attempt + 1, maxRetries, reg);
            #if defined(ARDUINO)
            PLATFORM_DELAY(10); // Short delay between retries
            #endif
        }
    }
    
    setError("I2C write failed after retries");
    DEBUG_PRINTF("I2C Write FAILED after %d attempts: reg=0x%02X value=0x%02X\n", 
                maxRetries, reg, value);
    return false;
}

bool BQ25895Driver::readRegisterWithRetry(uint8_t reg, uint8_t& value, int maxRetries) {
    if (!i2c_dev_) {
        setError("I2C device not available");
        return false;
    }
    
    for (int attempt = 0; attempt < maxRetries; attempt++) {
        if (i2c_dev_->write_then_read(&reg, 1, &value, 1)) {
            if (attempt > 0) {
                DEBUG_PRINTF("I2C Read succeeded on attempt %d: reg=0x%02X value=0x%02X\n", 
                            attempt + 1, reg, value);
            }
            return true;
        }
        
        if (attempt < maxRetries - 1) {
            DEBUG_PRINTF("I2C Read retry %d/%d: reg=0x%02X error\n", 
                        attempt + 1, maxRetries, reg);
            #if defined(ARDUINO)
            PLATFORM_DELAY(10); // Short delay between retries
            #endif
        }
    }
    
    setError("I2C read failed after retries");
    DEBUG_PRINTF("I2C Read FAILED after %d attempts: reg=0x%02X\n", maxRetries, reg);
    return false;
}

bool BQ25895Driver::updateRegisterBits(uint8_t reg, uint8_t mask, uint8_t value) {
    uint8_t currentValue;
    if (!readRegisterWithRetry(reg, currentValue, 2)) {
        setError("Failed to read register for bit update");
        return false;
    }
    
    // Clear target bits and set new bits (atomic read-modify-write)
    uint8_t newValue = (currentValue & ~mask) | (value & mask);
    
    if (newValue != currentValue) {
        bool writeSuccess = writeRegisterWithRetry(reg, newValue, 2);
        if (writeSuccess) {
            DEBUG_PRINTF("Bit update: reg=0x%02X, mask=0x%02X, old=0x%02X, new=0x%02X\n", 
                        reg, mask, currentValue, newValue);
        }
        return writeSuccess;
    }
    
    return true; // No change needed
}

void BQ25895Driver::setError(const String& error) {
    lastError_ = error;
    #if defined(ARDUINO)
    if (error.length() > 0) {
        DEBUG_PRINTF("BQ25895Driver Error: %s\n", error.c_str());
    }
    #else
    if (error.length() > 0) {
        DEBUG_PRINTF("BQ25895Driver Error: %s\n", error.c_str());
    }
    #endif
}

String BQ25895Driver::formatTimestamp(unsigned long timestamp) {
    unsigned long seconds = timestamp / 1000;
    unsigned long hours = seconds / 3600;
    unsigned long minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;
    
    #if defined(ARDUINO)
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "[%02lu:%02lu:%02lu]", hours, minutes, seconds);
    return String(buffer);
    #else
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "[%02lu:%02lu:%02lu]", hours, minutes, seconds);
    return std::string(buffer);
    #endif
}

void BQ25895Driver::logWithTimestamp(const String& message) {
    String timestamp = formatTimestamp(millis());
    DEBUG_PRINTF("%s >>> %s\n", timestamp.c_str(), message.c_str());
}

bool BQ25895Driver::verifyDevice() {
    if (!i2c_dev_) {
        setError("I2C interface not available");
        return false;
    }
    
    uint8_t vendorReg;
    if (!readRegisterWithRetry(REG0A_VENDOR_PART, vendorReg, 3)) {
        setError("Cannot communicate with BQ25895");
        return false;
    }
    
    uint8_t vendorId = (vendorReg >> 3) & 0x1F;
    uint8_t partNumber = vendorReg & 0x07;
    DEBUG_PRINTF("BQ25895 Vendor ID: 0x%02X, Part Number: 0x%02X\n", vendorId, partNumber);
    
    // Basic sanity check - vendor ID should be non-zero
    if (vendorId == 0 || vendorId == 0x1F) {
        setError("Invalid vendor ID detected");
        return false;
    }
    
    return true;
}

// Status reporting functions for clean UI
String BQ25895Driver::getFaultStatusReport() {
    String report = "";
    BQ25895Status status = getStatus();
    
    if (status.faultRegister == 0) {
        report += "No faults detected";
        return report;
    }
    
    report += "FAULT DETAILS:\n";
    if (status.faultRegister & 0x80) report += "  - WATCHDOG_FAULT: Watchdog timer expired\n";
    if (status.faultRegister & 0x40) report += "  - BOOST_FAULT: VBUS overload/OVP/low battery\n";
    if (status.faultRegister & 0x30) {
        uint8_t chrgFault = (status.faultRegister & 0x30) >> 4;
        report += "  - CHRG_FAULT: ";
        if (chrgFault == 1) report += "Input fault (VBUS issue)\n";
        else if (chrgFault == 2) report += "Thermal shutdown\n";
        else if (chrgFault == 3) report += "Safety timer expiration\n";
    }
    if (status.faultRegister & 0x08) report += "  - BAT_FAULT: Battery overvoltage (VBAT > 4.37V)\n";
    
    uint8_t ntcFault = status.faultRegister & 0x07;
    if (ntcFault != 0) {
        report += "  - NTC_FAULT: ";
        if (ntcFault == 1) report += "TS Cold\n";
        else if (ntcFault == 2) report += "TS Hot\n";
        else if (ntcFault == 5) report += "TS Cold (Boost)\n";
        else if (ntcFault == 6) report += "TS Hot (Boost)\n";
        else report += "Unknown (0x" + STRING_FROM_HEX(ntcFault) + ")\n";
    }
    
    return report;
}

String BQ25895Driver::getPowerStatusSummary() {
    String summary = "";
    BQ25895Status status = getStatus();
    
    summary += "=== DETAILED BQ25895 STATUS ===\n";
    summary += "Charging Enabled: " + String(status.chargingEnabled ? "YES" : "NO") + "\n";
    summary += "Charge Status: ";
    switch(status.chargeStatus) {
        case ChargeStatus::NOT_CHARGING: summary += "Not Charging"; break;
        case ChargeStatus::PRE_CHARGE: summary += "Pre-charge"; break;
        case ChargeStatus::FAST_CHARGE: summary += "Fast Charge"; break;
        case ChargeStatus::CHARGE_TERMINATION: summary += "Complete"; break;
    }
    summary += "\n";
    
    summary += "VBUS Status: " + getVBusTypeName(getVBusType()) + "\n";
    summary += "Fault Register: 0x" + STRING_FROM_HEX(status.faultRegister) + "\n";
    
    // CRITICAL: Check BATFET status
    uint8_t reg09;
    if (readRegister(0x09, reg09)) {
        bool batfetDisabled = (reg09 & 0x20) != 0; // Bit 5 = BATFET_DIS
        summary += "BATFET Status: " + String(batfetDisabled ? "DISABLED - Cannot connect to battery!" : "ENABLED - Can connect to battery") + " (REG09[5] = " + STRING_FROM_INT(batfetDisabled ? 1 : 0) + ")\n";
        if (batfetDisabled) {
            summary += "*** CRITICAL: BATFET disabled - explains 0mA current and phantom readings! ***\n";
        }
    }
    
    // Check charge enable status in registers directly
    uint8_t reg03;
    if (readRegister(0x03, reg03)) {
        bool chargeEnabled = (reg03 & 0x10) != 0; // Bit 4 = CHG_CONFIG
        summary += "Hardware Charge Enable: " + String(chargeEnabled ? "ENABLED" : "DISABLED") + " (REG03[4] = " + STRING_FROM_INT(chargeEnabled ? 1 : 0) + ")\n";
    }
    
    return summary;
}

String BQ25895Driver::getVoltageAnalysis() {
    String analysis = "";
    BQ25895Metrics metrics = getMetrics();
    
    int vbat = metrics.batteryVoltage;
    int vsys = metrics.systemVoltage;
    int vdiff = vbat - vsys;
    
    analysis += "\n=== VOLTAGE ANALYSIS ===\n";
    analysis += "VBAT-VSYS Difference: " + STRING_FROM_INT(vdiff) + "mV\n";
    
    if (abs(vdiff) < 50) {
        analysis += "DIAGNOSIS: Likely phantom charging (VBAT≈VSYS)\n";
    } else if (vdiff > 50) {
        analysis += "DIAGNOSIS: Real battery detected (VBAT>VSYS)\n";
    } else {
        analysis += "DIAGNOSIS: Unusual voltage relationship\n";
    }
    analysis += "===============================\n";
    
    return analysis;
}

String BQ25895Driver::getRegisterDiagnostics() {
    String diagnostics = "";
    
    // Dump all critical registers
    diagnostics += "=== REGISTER DUMP ===\n";
    uint8_t regs[21]; // REG00 through REG14
    for (int i = 0; i <= 20; i++) {
        if (readRegister(i, regs[i])) {
            diagnostics += "REG" + String(i < 16 ? "0" : "") + STRING_FROM_HEX(i) + ": 0x" + STRING_FROM_HEX(regs[i]) + "\n";
        }
    }
    
    diagnostics += "=== REGISTER ANALYSIS ===\n";
    diagnostics += "REG00[5:0] Input Limit: " + STRING_FROM_INT(((regs[0] & 0x3F) * 50) + 100) + "mA\n";
    diagnostics += "REG02[6:0] Charge Current: " + STRING_FROM_INT((regs[2] & 0x7F) * 64) + "mA\n";
    diagnostics += "REG03[4] Charge Enable: " + String((regs[3] & 0x10) ? "YES" : "NO") + "\n";
    diagnostics += "REG06[7:2] Charge Voltage: " + STRING_FROM_INT(((regs[6] >> 2) * 16) + 3840) + "mV\n";
    diagnostics += "REG09[5] BATFET_DIS: " + String((regs[9] & 0x20) ? "DISABLED" : "ENABLED") + "\n";
    diagnostics += "REG0B[1:0] VBUS_STAT: 0x" + STRING_FROM_HEX(regs[11] & 0x03) + "\n";
    
    diagnostics += "=== CRITICAL ISSUES DETECTED ===\n";
    if ((regs[2] & 0x7F) == 0) {
        diagnostics += "🚨 REG02 CHARGE CURRENT = 0mA - This is why no charging occurs!\n";
    }
    if (((regs[6] >> 2) * 16) + 3840 < 4100) {
        diagnostics += "🚨 REG06 CHARGE VOLTAGE too low for Li-Ion (should be 4200mV)\n";
    }
    
    return diagnostics;
}

// Advanced control functions (moved from main.cpp)

bool BQ25895Driver::repairRegisters() {
    if (!initialized_) {
        lastError_ = "Driver not initialized";
        return false;
    }
    
    bool success = true;
    
    // Fix REG02 - Charge Current (1000mA = 1000/64 = 15.6, use 16 = 0x10)
    uint8_t chgCurrent = 16; // 16 * 64mA = 1024mA ≈ 1000mA
    if (writeRegister(0x02, chgCurrent)) {
        // Success will be logged by caller
    } else {
        success = false;
    }
    
    // Fix REG06 - Charge Voltage (4192mV for safety)
    uint8_t reg06;
    if (readRegister(0x06, reg06)) {
        uint8_t voltageField = 22; // 22 * 16 + 3840 = 4192mV (safe for 4.16V battery)
        reg06 = (reg06 & 0x03) | (voltageField << 2); // Keep lower 2 bits, set voltage
        if (!writeRegister(0x06, reg06)) {
            success = false;
        }
    } else {
        success = false;
    }
    
    // Fix REG00 - Input Current (1500mA = (1500-100)/50 = 28 = 0x1C)
    uint8_t inputField = 28; // 28 * 50 + 100 = 1500mA
    uint8_t reg00;
    if (readRegister(0x00, reg00)) {
        reg00 = (reg00 & 0xC0) | inputField; // Keep upper 2 bits, set input limit
        if (!writeRegister(0x00, reg00)) {
            success = false;
        }
    } else {
        success = false;
    }
    
    if (!success) {
        lastError_ = "One or more register repairs failed";
    }
    return success;
}

bool BQ25895Driver::forceEnableBATFET() {
    if (!initialized_) {
        lastError_ = "Driver not initialized";
        return false;
    }
    
    uint8_t reg09;
    if (!readRegister(0x09, reg09)) {
        lastError_ = "Failed to read BATFET status";
        return false;
    }
    
    bool batfetDisabled = (reg09 & 0x20) != 0;
    if (batfetDisabled) {
        // Force enable BATFET by clearing BATFET_DIS bit
        reg09 &= ~0x20; // Clear bit 5
        if (!writeRegister(0x09, reg09)) {
            lastError_ = "Failed to write BATFET enable";
            return false;
        }
        return true;
    } else {
        // Already enabled
        return true;
    }
}

bool BQ25895Driver::forceRestartCharging() {
    if (!initialized_) {
        lastError_ = "Driver not initialized";
        return false;
    }
    
    // Disable charging first
    if (!disableCharging()) {
        return false;
    }
    PLATFORM_DELAY(100);
    
    // Enhanced DPM defeat during restart
    // Force input current limit via direct register write
    if (!writeRegister(0x00, 0x1C)) { // 1500mA
        lastError_ = "Failed to set input current limit";
        return false;
    }
    
    // Disable USB auto-detection that keeps overriding us
    uint8_t reg0D;
    if (readRegister(0x0D, reg0D)) {
        reg0D |= 0x80; // Set FORCE_DPDM bit
        writeRegister(0x0D, reg0D);
    }
    
    // Re-enable charging (this should reset the completion status)
    if (!enableCharging()) {
        return false;
    }
    
    // Re-apply our current limits multiple ways to ensure they stick
    setInputCurrentLimit(1500);
    setTerminationCurrent(64);
    
    return true;
}

String BQ25895Driver::getChargeVoltageAnalysis() {
    String analysis = "";
    
    uint8_t reg06;
    if (readRegister(0x06, reg06)) {
        uint8_t voltageField = (reg06 >> 2) & 0x3F; // Extract bits 7:2
        uint16_t chargeVoltage = 3840 + (voltageField * 16);
        uint16_t batovpThreshold = (chargeVoltage * 104) / 100; // 4% above charge voltage
        
        analysis += "=== CHARGE VOLTAGE ANALYSIS ===\n";
        analysis += "REG06: 0x" + STRING_FROM_HEX(reg06) + "\n";
        analysis += "Voltage Field [7:2]: 0x" + STRING_FROM_HEX(voltageField) + " (" + STRING_FROM_INT(voltageField) + ")\n";
        analysis += "Charge Voltage: " + STRING_FROM_INT(chargeVoltage) + "mV\n";
        analysis += "BATOVP Threshold: " + STRING_FROM_INT(batovpThreshold) + "mV (4% above charge voltage)\n";
        
        BQ25895Metrics metrics = getMetrics();
        analysis += "Current Battery: " + STRING_FROM_INT(metrics.batteryVoltage) + "mV\n";
        
        if (metrics.batteryVoltage > batovpThreshold) {
            analysis += "🚨 BATTERY EXCEEDS BATOVP! Fault expected.\n";
        } else {
            analysis += "✓ Battery below BATOVP threshold.\n";
        }
        analysis += "===============================\n";
    } else {
        analysis += "ERROR: Failed to read REG06\n";
    }
    
    return analysis;
}

// Voltage safety protection implementation
bool BQ25895Driver::checkVoltageSafety() {
    if (!initialized_) {
        return true; // Assume safe if not initialized
    }
    
    BQ25895Metrics metrics = getMetrics();
    
    // Check if input voltage exceeds configured safety limit
    if (metrics.inputVoltage > config_.voltageSafetyLimitMV) {
        if (voltageSafe_) {
            // First time detecting unsafe voltage
            voltageSafe_ = false;
            DEBUG_PRINTF("🚨 VOLTAGE SAFETY TRIGGERED: Input %dmV > %dmV limit\n", 
                        metrics.inputVoltage, config_.voltageSafetyLimitMV);
            DEBUG_PRINTLN("   LEDs at risk! Initiating emergency shutdown...");
            
            // Trigger immediate protective shutdown
            forceEmergencyShutdown();
        }
        return false;
    } else {
        voltageSafe_ = true;
        return true;
    }
}

bool BQ25895Driver::isVoltageSafe() const {
    return voltageSafe_;
}

bool BQ25895Driver::forceEmergencyShutdown() {
    if (!initialized_) {
        setError("Cannot perform emergency shutdown - driver not initialized");
        return false;
    }
    
    emergencyShutdownTriggered_ = true;
    DEBUG_PRINTLN("🚨 EMERGENCY SHUTDOWN: Protecting system from overvoltage");
    
    bool success = true;
    
    // 1. Disable charging immediately
    if (!disableCharging()) {
        DEBUG_PRINTLN("   ⚠️ Failed to disable charging during emergency shutdown");
        success = false;
    }
    
    // 2. Force BATFET off to disconnect battery from system if possible
    uint8_t reg09;
    if (readRegisterWithRetry(REG09_NEW_FAULT, reg09)) {
        reg09 |= 0x20; // Set BATFET_DIS bit
        if (!writeRegisterWithRetry(REG09_NEW_FAULT, reg09)) {
            DEBUG_PRINTLN("   ⚠️ Failed to disable BATFET during emergency shutdown");
            success = false;
        } else {
            DEBUG_PRINTLN("   ✓ BATFET disabled for protection");
        }
    }
    
    // 3. Set input current limit to minimum
    if (!setInputCurrentLimit(100)) {
        DEBUG_PRINTLN("   ⚠️ Failed to limit input current during emergency shutdown");
        success = false;
    } else {
        DEBUG_PRINTLN("   ✓ Input current limited to 100mA");
    }
    
    if (success) {
        DEBUG_PRINTLN("   ✓ Emergency shutdown completed successfully");
        DEBUG_PRINTLN("   💡 SOLUTION: Reduce external VIN to ≤5.5V and restart system");
    } else {
        DEBUG_PRINTLN("   ⚠️ Emergency shutdown completed with some failures");
    }
    
    return success;
}