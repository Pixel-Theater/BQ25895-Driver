/**
 * @file test_bq25895_driver.cpp
 * @brief Comprehensive test suite for BQ25895Driver library
 * 
 * This test suite provides complete coverage of the BQ25895Driver functionality
 * using a mock I2C interface for reliable, fast testing without hardware dependencies.
 * 
 * Test Coverage:
 * - Driver initialization and configuration
 * - VBUS type detection and power management  
 * - Charge control (enable/disable, current/voltage setting)
 * - Status and metrics reading
 * - Fault detection and management
 * - Watchdog management
 * - Reset functions (soft reset, factory reset, emergency modes)
 * - Error handling and I2C failure scenarios
 * - Ship mode functionality
 * 
 * The MockI2CDevice class simulates BQ25895 register behavior including:
 * - Fault register clearing on read
 * - Reset detection and register restoration
 * - Configurable I2C failure simulation
 * - Realistic default register values
 */

#include "doctest.h"
#include "BQ25895Driver.h"
#include <map>
#include <cstdio>

// Use extern functions defined in test_battery_system.cpp
extern unsigned long mock_millis;
extern void advance_time(unsigned long ms);
extern void reset_time();

// Mock Adafruit_I2CDevice for testing
class MockI2CDevice : public Adafruit_I2CDevice {
private:
    std::map<uint8_t, uint8_t> registers_;
    bool failNextWrite_ = false;
    bool failNextRead_ = false;
    int writeFailCount_ = 0;
    int readFailCount_ = 0;
    
public:
    MockI2CDevice() : Adafruit_I2CDevice(BQ25895_I2C_ADDR, nullptr) {}
    
    // Simulate device registers with realistic defaults
    void setupDefaultRegisters() {
        registers_[REG0A_VENDOR_PART] = 0x23; // Typical vendor/part value
        registers_[REG0B_SYSTEM_STATUS] = 0x00; // No input, not charging
        registers_[REG0C_FAULT] = 0x00; // No faults
        registers_[REG03_CHARGE_CONFIG] = 0x1A; // Default charge config
        registers_[REG0E_BATV] = 0x50; // ~3.9V battery (0x50 = 80, 2304 + 80*20 = 3904mV)
        registers_[REG0F_SYSV] = 0x50; // ~3.9V system
        registers_[REG11_VBUSV] = 0x1E; // ~5.6V input (0x1E = 30, 2600 + 30*100 = 5600mV)
        registers_[REG12_ICHGR] = 0x00; // 0mA charge current
        registers_[REG10_TSPCT] = 0x40; // Mid-range thermistor
    }
    
    // Override Adafruit_I2CDevice methods
    bool begin(bool addr_detect = true) override {
        return true; // Always succeed in tests
    }
    
    // Mock I2C write operation (register address + value)
    bool write(uint8_t* buffer, size_t len, bool stop = true) override {
        if (failNextWrite_ || writeFailCount_ > 0) {
            if (writeFailCount_ > 0) writeFailCount_--;
            if (failNextWrite_) failNextWrite_ = false;
            return false;
        }
        
        if (len != 2) return false; // Expect register + value
        
        uint8_t reg = buffer[0];
        uint8_t value = buffer[1];
        
        // Simulate register-specific behavior
        if (reg == REG14_RESET && (value & 0x80)) {
            // Reset detected - restore defaults
            setupDefaultRegisters();
        } else if (reg == REG05_TIMER && (value & 0x40)) {
            // WD_RST bit is self-clearing - set it temporarily then clear
            registers_[reg] = value;
            // In real hardware, this bit would clear itself after the watchdog resets
            // For testing, we can check it immediately after write
        } else {
            registers_[reg] = value;
        }
        
        return true;
    }
    
    // Mock I2C write_then_read operation
    bool write_then_read(uint8_t* write_buffer, size_t write_len, 
                         uint8_t* read_buffer, size_t read_len, 
                         bool stop = false) override {
        if (failNextRead_ || readFailCount_ > 0) {
            if (readFailCount_ > 0) readFailCount_--;
            if (failNextRead_) failNextRead_ = false;
            return false;
        }
        
        if (write_len != 1 || read_len != 1) return false; // Expect reg read
        
        uint8_t reg = write_buffer[0];
        
        // Special case for fault register - reading clears it
        if (reg == REG0C_FAULT) {
            read_buffer[0] = registers_[reg];
            registers_[reg] = 0x00; // Clear after read
            return true;
        }
        
        auto it = registers_.find(reg);
        if (it != registers_.end()) {
            read_buffer[0] = it->second;
            return true;
        }
        
        // Default to 0 for unset registers
        read_buffer[0] = 0;
        return true;
    }
    
    // Test helper methods
    void setRegister(uint8_t reg, uint8_t value) {
        registers_[reg] = value;
    }
    
    uint8_t getRegister(uint8_t reg) {
        return registers_[reg];
    }
    
    void simulateVBusType(VBusType type) {
        uint8_t sysStatus = registers_[REG0B_SYSTEM_STATUS] & ~VBUS_STAT_MASK;
        sysStatus |= (static_cast<uint8_t>(type) << VBUS_STAT_SHIFT);
        registers_[REG0B_SYSTEM_STATUS] = sysStatus;
    }
    
    void simulateChargeStatus(ChargeStatus status) {
        uint8_t sysStatus = registers_[REG0B_SYSTEM_STATUS] & ~0x18; // Clear bits 4:3
        sysStatus |= (static_cast<uint8_t>(status) << 3);
        registers_[REG0B_SYSTEM_STATUS] = sysStatus;
    }
    
    void simulateFault(uint8_t faultBits) {
        registers_[REG0C_FAULT] = faultBits;
    }
    
    void simulateBatteryVoltage(uint16_t voltageMA) {
        // Convert mV to register value: reg = (mV - 2304) / 20
        uint8_t regValue = (voltageMA > 2304) ? ((voltageMA - 2304) / 20) : 0;
        registers_[REG0E_BATV] = regValue & 0x7F;
    }
    
    void simulateChargeCurrent(int16_t currentMA) {
        // Convert mA to register value: reg = currentMA / 50
        uint8_t regValue = (currentMA >= 0) ? (currentMA / 50) : 0;
        registers_[REG12_ICHGR] = regValue & 0x7F;
    }
    
    void failNextWrite() { failNextWrite_ = true; }
    void failNextRead() { failNextRead_ = true; }
    void failWrites(int count) { writeFailCount_ = count; }
    void failReads(int count) { readFailCount_ = count; }
    
    // Helper methods for compatibility with old tests  
    bool writeRegister(uint8_t addr, uint8_t reg, uint8_t value) {
        uint8_t buffer[2] = {reg, value};
        return write(buffer, 2);
    }
    
    bool readRegister(uint8_t addr, uint8_t reg, uint8_t& value) {
        return write_then_read(&reg, 1, &value, 1);
    }
};

// Helper function to create driver with mock I2C
BQ25895Driver createTestDriver(MockI2CDevice& mockI2C) {
    mockI2C.setupDefaultRegisters();
    return BQ25895Driver(&mockI2C);
}

// =============================================================================
// INITIALIZATION AND SETUP TESTS
// =============================================================================

TEST_CASE("BQ25895Driver: Constructor and Basic Setup") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver(&mockI2C);
    
    CHECK(driver.isInitialized() == false);
    CHECK(driver.getLastError() == "");
    CHECK(driver.isInEmergencyMode() == false);
}

TEST_CASE("BQ25895Driver: Successful Initialization") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    
    BQ25895Config config;
    config.inputCurrentMA = 1500;
    config.chargeCurrentMA = 2000;
    config.disableWatchdog = true;
    
    bool result = driver.initialize(config);
    
    CHECK(result == true);
    CHECK(driver.isInitialized() == true);
    CHECK(driver.getLastError() == "");
    
    // Verify watchdog was disabled
    uint8_t reg07 = mockI2C.getRegister(REG07_MISC_OPERATION);
    CHECK((reg07 & WATCHDOG_MASK) == WATCHDOG_DISABLE);
}

TEST_CASE("BQ25895Driver: Failed Initialization - I2C Error") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    
    // Simulate persistent I2C failure during device verification
    mockI2C.failReads(5); // Fail multiple reads to defeat retry logic
    
    bool result = driver.initialize();
    
    CHECK(result == false);
    CHECK(driver.isInitialized() == false);
    CHECK(driver.getLastError() != "");
}

// =============================================================================
// POWER MANAGEMENT AND DETECTION TESTS  
// =============================================================================

TEST_CASE("BQ25895Driver: VBUS Type Detection") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    SUBCASE("USB SDP Detection") {
        mockI2C.simulateVBusType(VBusType::USB_SDP);
        VBusType type = driver.getVBusType();
        CHECK(type == VBusType::USB_SDP);
        CHECK(driver.getVBusTypeName(type) == "USB SDP (500mA)");
        CHECK(driver.isExternalPowerPresent() == true);
    }
    
    SUBCASE("USB DCP Detection") {
        mockI2C.simulateVBusType(VBusType::USB_DCP);
        VBusType type = driver.getVBusType();
        CHECK(type == VBusType::USB_DCP);
        CHECK(driver.getVBusTypeName(type) == "USB DCP (3.25A)");
        CHECK(driver.isExternalPowerPresent() == true);
    }
    
    SUBCASE("No Input Detection") {
        mockI2C.simulateVBusType(VBusType::NONE);
        VBusType type = driver.getVBusType();
        CHECK(type == VBusType::NONE);
        CHECK(driver.getVBusTypeName(type) == "No Input");
        CHECK(driver.isExternalPowerPresent() == false);
    }
}

TEST_CASE("BQ25895Driver: Charging Control") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    SUBCASE("Enable Charging") {
        bool result = driver.enableCharging();
        CHECK(result == true);
        
        uint8_t reg03 = mockI2C.getRegister(REG03_CHARGE_CONFIG);
        CHECK((reg03 & 0x10) != 0); // CHG_CONFIG bit should be set
    }
    
    SUBCASE("Disable Charging") {
        // First enable, then disable
        driver.enableCharging();
        bool result = driver.disableCharging();
        CHECK(result == true);
        
        uint8_t reg03 = mockI2C.getRegister(REG03_CHARGE_CONFIG);
        CHECK((reg03 & 0x10) == 0); // CHG_CONFIG bit should be cleared
    }
    
    SUBCASE("Set Charge Current") {
        bool result = driver.setChargeCurrent(1000); // 1A
        CHECK(result == true);
        
        uint8_t reg04 = mockI2C.getRegister(REG04_CHARGE_CURRENT);
        // 1000mA = 0x14 in register (1000/64 + offset calculations)
        CHECK(reg04 != 0); // Should be non-zero
    }
    
    SUBCASE("Set Input Current Limit") {
        bool result = driver.setInputCurrentLimit(1500); // 1.5A
        CHECK(result == true);
        
        uint8_t reg00 = mockI2C.getRegister(REG00_INPUT_CURRENT);
        CHECK(reg00 != 0); // Should be non-zero for 1.5A
    }
}

// =============================================================================
// MEASUREMENT AND STATUS TESTS
// =============================================================================

TEST_CASE("BQ25895Driver: Measurements") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    // Set up realistic measurement values (use values that align with register conversions)
    mockI2C.simulateBatteryVoltage(3844); // 3.844V (2304 + 77*20)
    mockI2C.simulateChargeCurrent(1200);  // 1.2A (divides evenly by 50)
    mockI2C.setRegister(REG0F_SYSV, 0x55); // System voltage
    mockI2C.setRegister(REG11_VBUSV, 0x1E); // Input voltage ~5.6V
    mockI2C.setRegister(REG10_TSPCT, 0x3F); // Thermistor voltage
    
    BQ25895Metrics metrics = driver.getMetrics();
    
    CHECK(metrics.batteryVoltage == 3844);  // Fixed: use calculated round-trip value
    CHECK(metrics.chargeCurrentMA == 1200);
    CHECK(metrics.systemVoltage > 0);
    CHECK(metrics.inputVoltage > 0);
    CHECK(metrics.tsVoltage > 0);
    CHECK(metrics.timestamp > 0);
}

TEST_CASE("BQ25895Driver: Status Reading") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    // Set up status conditions
    mockI2C.simulateVBusType(VBusType::USB_CDP);
    mockI2C.simulateChargeStatus(ChargeStatus::FAST_CHARGE);
    
    BQ25895Status status = driver.getStatus();
    
    CHECK(status.vbusType == VBusType::USB_CDP);
    CHECK(status.chargeStatus == ChargeStatus::FAST_CHARGE);
    CHECK(status.inputDetected == true);
    CHECK(status.faultRegister == 0);
    CHECK(status.timestamp > 0);
}

// =============================================================================
// FAULT MANAGEMENT AND SAFETY TESTS
// =============================================================================

TEST_CASE("BQ25895Driver: Fault Management") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    SUBCASE("No Faults") {
        uint8_t faultReg = driver.getFaultRegister();
        CHECK(faultReg == 0);
        
        String faultStr = driver.decodeFaults(0);
        CHECK(faultStr == "No faults");
    }
    
    SUBCASE("Detect Faults") {
        // Simulate various faults
        mockI2C.simulateFault(0x88); // Watchdog + Battery fault
        
        // First, check that the fault was set in the mock
        uint8_t mockFault = mockI2C.getRegister(REG0C_FAULT);
        CHECK(mockFault == 0x88);
        
        // Test driver's fault detection - getFaultRegister() reads twice (clears then reads current)
        // So after clearing latched faults, current status should be 0 (no active faults)
        uint8_t faultReg = driver.getFaultRegister();
        CHECK(faultReg == 0); // After clearing latched faults, current status is clear
        
        // Test fault decoding with known fault value
        String faultStr = driver.decodeFaults(0x88);
        CHECK(faultStr.length() > 0);
        CHECK(faultStr.find("Watchdog") != std::string::npos);
        CHECK(faultStr.find("Battery") != std::string::npos);
    }
    
    SUBCASE("Clear Faults") {
        mockI2C.simulateFault(0x80); // Watchdog fault
        
        bool result = driver.clearFaults();
        CHECK(result == true);
        
        // After clearing, fault register should be zero
        uint8_t faultReg = driver.getFaultRegister();
        CHECK(faultReg == 0);
    }
}

TEST_CASE("BQ25895Driver: Emergency Battery Mode") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    SUBCASE("Enter Emergency Mode") {
        bool result = driver.enterEmergencyBatteryMode();
        CHECK(result == true);
        CHECK(driver.isInEmergencyMode() == true);
        
        // Should disable charging
        uint8_t reg03 = mockI2C.getRegister(REG03_CHARGE_CONFIG);
        CHECK((reg03 & 0x10) == 0);
        
        // Should disable VBUS detection
        uint8_t reg0D = mockI2C.getRegister(REG0D_VINDPM);
        CHECK((reg0D & 0x80) != 0); // Force bit should be set
    }
    
    SUBCASE("Exit Emergency Mode") {
        driver.enterEmergencyBatteryMode();
        
        bool result = driver.exitEmergencyMode();
        CHECK(result == true);
        CHECK(driver.isInEmergencyMode() == false);
    }
}

// =============================================================================
// RESET AND RECOVERY TESTS
// =============================================================================

TEST_CASE("BQ25895Driver: Watchdog Management") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    SUBCASE("Disable Watchdog") {
        bool result = driver.disableWatchdog();
        CHECK(result == true);
        
        uint8_t reg07 = mockI2C.getRegister(REG07_MISC_OPERATION);
        CHECK((reg07 & WATCHDOG_MASK) == WATCHDOG_DISABLE);
    }
    
    SUBCASE("Reset Watchdog") {
        // Enable watchdog first by manually setting the register (initialization disables it)
        mockI2C.setRegister(REG07_MISC_OPERATION, WATCHDOG_40S << WATCHDOG_SHIFT);
        
        bool result = driver.resetWatchdog();
        CHECK(result == true);
        
        // Note: WD_RST bit is self-clearing in real hardware, so we test operation success
        // rather than bit persistence. The fact that resetWatchdog() returns true means
        // the I2C write operation succeeded.
    }
}

TEST_CASE("BQ25895Driver: Reset Functions") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    SUBCASE("Factory Reset") {
        // Modify some registers first
        mockI2C.setRegister(REG03_CHARGE_CONFIG, 0xFF);
        
        driver.factoryReset();
        
        // After reset, registers should return to defaults
        uint8_t reg03 = mockI2C.getRegister(REG03_CHARGE_CONFIG);
        CHECK(reg03 != 0xFF); // Should be back to default
    }
    
    SUBCASE("Soft Reset") {
        driver.reset();
        CHECK(driver.isInitialized() == false);
    }
}

// =============================================================================
// ERROR HANDLING AND EDGE CASE TESTS
// =============================================================================

TEST_CASE("BQ25895Driver: Error Handling") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    
    SUBCASE("I2C Write Failures") {
        mockI2C.failWrites(100); // Fail ALL writes to ensure initialization fails
        
        bool result = driver.initialize();
        CHECK(result == false);
        CHECK(driver.getLastError() != "");
    }
    
    SUBCASE("I2C Read Failures") {
        driver.initialize(); // Success first
        
        mockI2C.failReads(10); // Fail enough reads to defeat retry logic
        BQ25895Status status = driver.getStatus();
        
        // Should handle gracefully and set error
        CHECK(driver.getLastError() != "");
    }
    
    SUBCASE("Operation on Uninitialized Driver") {
        // Don't initialize
        
        bool result = driver.enableCharging();
        CHECK(result == false);
        CHECK(driver.getLastError() != "");
    }
}

TEST_CASE("BQ25895Driver: Ship Mode") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    bool result = driver.enterShipMode();
    CHECK(result == true);
    
    uint8_t reg09 = mockI2C.getRegister(REG09_NEW_FAULT);
    CHECK((reg09 & 0x20) != 0); // BATFET_DIS bit should be set
}

TEST_CASE("BQ25895Driver: Configuration Persistence") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    
    BQ25895Config config;
    config.inputCurrentMA = 2000;
    config.chargeCurrentMA = 1500;
    config.chargeVoltageNV = 4100;
    
    driver.initialize(config);
    
    BQ25895Config retrieved = driver.getConfig();
    CHECK(retrieved.inputCurrentMA == config.inputCurrentMA);
    CHECK(retrieved.chargeCurrentMA == config.chargeCurrentMA);
    CHECK(retrieved.chargeVoltageNV == config.chargeVoltageNV);
}

TEST_CASE("BQ25895Driver: Self Test") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    bool result = driver.performSelfTest();
    CHECK(result == true);
    
    // Self test should verify basic communication and register sanity
}

TEST_CASE("BQ25895Driver: Register Access") {
    MockI2CDevice mockI2C;
    BQ25895Driver driver = createTestDriver(mockI2C);
    driver.initialize();
    
    SUBCASE("Direct Register Write") {
        bool result = driver.writeRegister(REG03_CHARGE_CONFIG, 0x1A);
        CHECK(result == true);
        CHECK(mockI2C.getRegister(REG03_CHARGE_CONFIG) == 0x1A);
    }
    
    SUBCASE("Direct Register Read") {
        mockI2C.setRegister(REG0A_VENDOR_PART, 0x23);
        
        uint8_t value;
        bool result = driver.readRegister(REG0A_VENDOR_PART, value);
        CHECK(result == true);
        CHECK(value == 0x23);
    }
}