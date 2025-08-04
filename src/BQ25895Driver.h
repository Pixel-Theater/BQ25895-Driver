#ifndef BQ25895_DRIVER_H
#define BQ25895_DRIVER_H

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <string>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <sstream>
#endif

// Safe string handling for both Arduino and native environments
#if defined(ARDUINO)
  #define SAFE_STRING String
  #define STRING_FROM_INT(x) String(x)
  #define STRING_FROM_HEX(x) String(x, HEX)
  #define STRING_FROM_FLOAT(x, precision) String(x, precision)
#else
  #define SAFE_STRING std::string
  #define STRING_FROM_INT(x) std::to_string((x))
  #define STRING_FROM_HEX(x) (std::ostringstream() << std::hex << (x)).str()
  #define STRING_FROM_FLOAT(x, precision) (std::ostringstream() << std::fixed << std::setprecision(precision) << (x)).str()
  typedef std::string String; // For compatibility
#endif

// BQ25895 Register Definitions
#define BQ25895_I2C_ADDR 0x6A

#define REG00_INPUT_CURRENT 0x00
#define REG03_CHARGE_CONFIG 0x03
#define REG04_CHARGE_CURRENT 0x04
#define REG05_TIMER 0x05
#define REG06_CHARGE_VOLTAGE 0x06
#define REG07_MISC_OPERATION 0x07
#define REG08_SYSTEM_STATUS 0x08
#define REG09_NEW_FAULT 0x09
#define REG0A_VENDOR_PART 0x0A
#define REG0B_SYSTEM_STATUS 0x0B
#define REG0C_FAULT 0x0C
#define REG0D_VINDPM 0x0D
#define REG0E_BATV 0x0E
#define REG0F_SYSV 0x0F
#define REG10_TSPCT 0x10
#define REG11_VBUSV 0x11
#define REG12_ICHGR 0x12
#define REG13_VDPMSTAT 0x13
#define REG14_RESET 0x14

// VBUS Status Detection (REG0B bits 7:5)
#define VBUS_STAT_MASK 0xE0
#define VBUS_STAT_SHIFT 5

// Watchdog Timer Control (REG07 bits 5:4)
#define WATCHDOG_MASK 0x30
#define WATCHDOG_SHIFT 4
#define WATCHDOG_DISABLE 0x00
#define WATCHDOG_40S 0x01
#define WATCHDOG_80S 0x02
#define WATCHDOG_160S 0x03

// VBUS Input Types
enum class VBusType : uint8_t {
  NONE = 0,           // No Input
  USB_SDP = 1,        // USB Host SDP (500mA)
  USB_CDP = 2,        // USB CDP (1.5A)
  USB_DCP = 3,        // USB DCP (3.25A)
  HVDCP = 4,          // High Voltage DCP (1.5A)
  UNKNOWN = 5,        // Unknown Adapter (500mA)
  NON_STANDARD = 6,   // Non-Standard Adapter
  OTG = 7             // OTG Mode
};

// Charge Status Values
enum class ChargeStatus : uint8_t {
  NOT_CHARGING = 0,
  PRE_CHARGE = 1,
  FAST_CHARGE = 2,
  CHARGE_TERMINATION = 3
};

// I2C communication using Adafruit_BusIO
#if defined(ARDUINO)
#include <Adafruit_I2CDevice.h>
#else
// Mock I2C device for testing
class Adafruit_I2CDevice {
public:
  Adafruit_I2CDevice(uint8_t addr, void* wire = nullptr) : address(addr) {}
  virtual ~Adafruit_I2CDevice() = default;
  virtual bool begin(bool addr_detect = true) { return true; }
  virtual bool write_then_read(uint8_t* write_buffer, size_t write_len, 
                               uint8_t* read_buffer, size_t read_len, 
                               bool stop = false) { return true; }
  virtual bool write(uint8_t* buffer, size_t len, bool stop = true) { return true; }
private:
  uint8_t address;
};
#endif

// Configuration structure
struct BQ25895Config {
  uint16_t inputCurrentMA = 1500;      // Input current limit (mA)
  uint16_t chargeCurrentMA = 2000;     // Charge current (mA)
  uint16_t chargeVoltageNV = 4208;     // Charge voltage (mV)
  uint16_t terminationCurrentMA = 128; // Charge termination current (mA)
  uint16_t vindpmThresholdMV = 3900;   // VINDPM threshold (mV)
  uint16_t voltageSafetyLimitMV = 5500; // Voltage safety limit for emergency shutdown (mV)
  bool disableWatchdog = true;         // Disable I2C watchdog
  bool disableSafetyTimer = true;      // Disable safety timer for testing
};

// Configuration presets for common applications
class BQ25895ConfigPresets {
public:
  // LED Driver configuration with 5.5V safety limit
  static BQ25895Config LEDDriver() {
    BQ25895Config config;
    config.inputCurrentMA = 1500;          // Conservative input current
    config.chargeCurrentMA = 1000;         // 1A charging
    config.chargeVoltageNV = 4192;         // Conservative 4.192V
    config.terminationCurrentMA = 64;      // Low termination current
    config.vindpmThresholdMV = 4400;       // 4.4V VINDPM
    config.voltageSafetyLimitMV = 5500;    // 5.5V LED safety limit
    config.disableWatchdog = true;         // Disable for development
    config.disableSafetyTimer = false;     // Keep safety timer
    return config;
  }
  
  // Portable device configuration
  static BQ25895Config PortableDevice() {
    BQ25895Config config;
    config.inputCurrentMA = 2000;          // Higher input current
    config.chargeCurrentMA = 1500;         // Faster charging
    config.chargeVoltageNV = 4208;         // Higher voltage for capacity
    config.terminationCurrentMA = 128;     // Standard termination
    config.vindpmThresholdMV = 4600;       // Higher VINDPM
    config.voltageSafetyLimitMV = 6000;    // Higher safety limit
    config.disableWatchdog = false;        // Enable watchdog
    config.disableSafetyTimer = false;     // Keep safety timer
    return config;
  }
  
  // Fast charging configuration
  static BQ25895Config FastCharging() {
    BQ25895Config config;
    config.inputCurrentMA = 3000;          // Maximum input current
    config.chargeCurrentMA = 2000;         // High charge current
    config.chargeVoltageNV = 4208;         // Full voltage
    config.terminationCurrentMA = 256;     // Higher termination
    config.vindpmThresholdMV = 4600;       // High VINDPM
    config.voltageSafetyLimitMV = 6000;    // Standard safety limit
    config.disableWatchdog = false;        // Enable watchdog
    config.disableSafetyTimer = false;     // Keep safety timer
    return config;
  }
  
  // Lab testing configuration with debugging features
  static BQ25895Config LabTesting() {
    BQ25895Config config;
    config.inputCurrentMA = 500;           // Low current for safety
    config.chargeCurrentMA = 500;          // Low charge current
    config.chargeVoltageNV = 4100;         // Conservative voltage
    config.terminationCurrentMA = 64;      // Low termination
    config.vindpmThresholdMV = 4000;       // Low VINDPM
    config.voltageSafetyLimitMV = 5000;    // Low safety limit
    config.disableWatchdog = true;         // Disable for debugging
    config.disableSafetyTimer = true;      // Disable for testing
    return config;
  }
};

// Current measurements and status
struct BQ25895Metrics {
  uint16_t batteryVoltage = 0;    // mV
  uint16_t systemVoltage = 0;     // mV
  uint16_t inputVoltage = 0;      // mV
  int16_t chargeCurrentMA = 0;    // mA
  uint16_t tsVoltage = 0;         // mV - thermistor voltage
  unsigned long timestamp = 0;   // When measurements were taken
};

// Status information
struct BQ25895Status {
  VBusType vbusType = VBusType::NONE;
  ChargeStatus chargeStatus = ChargeStatus::NOT_CHARGING;
  bool chargingEnabled = false;
  bool inputDetected = false;
  bool batteryDetected = false;
  uint8_t faultRegister = 0;
  bool watchdogFault = false;
  bool chargeFault = false;
  bool batteryFault = false;
  bool ntcFault = false;
  String lastError = "";
  unsigned long timestamp = 0;
};

// Main BQ25895 Driver Class
class BQ25895Driver {
private:
  Adafruit_I2CDevice* i2c_dev_;
  BQ25895Config config_;
  bool initialized_ = false;
  bool emergencyMode_ = false;
  unsigned long lastUpdate_ = 0;
  String lastError_ = "";
  
  // Power transition tracking
  VBusType lastVbusType_ = VBusType::NONE;
  unsigned long lastVbusChangeTime_ = 0;
  bool usbReconnectionInProgress_ = false;
  unsigned long usbReconnectionStartTime_ = 0;
  
  // Voltage safety protection
  bool voltageSafe_ = true;
  bool emergencyShutdownTriggered_ = false;
  
  // Internal helper methods
  bool writeRegisterWithRetry(uint8_t reg, uint8_t value, int maxRetries = 3);
  bool readRegisterWithRetry(uint8_t reg, uint8_t& value, int maxRetries = 3);
  bool updateRegisterBits(uint8_t reg, uint8_t mask, uint8_t value);
  void setError(const String& error);
  bool verifyDevice();
  String formatTimestamp(unsigned long timestamp);
  void logWithTimestamp(const String& message);
  
public:
  explicit BQ25895Driver(Adafruit_I2CDevice* i2c_dev);
  
  // Initialization and configuration
  bool initialize(const BQ25895Config& config = BQ25895Config{});
  bool isInitialized() const;
  void reset();
  void factoryReset();
  
  // Status and measurements
  BQ25895Status getStatus();
  BQ25895Metrics getMetrics();
  void updateAll(); // Update both status and metrics
  
  // Charging control
  bool enableCharging();
  bool disableCharging();
  bool setChargeCurrent(uint16_t currentMA);
  bool setInputCurrentLimit(uint16_t currentMA);
  bool setChargeVoltage(uint16_t voltageMV);
  bool setTerminationCurrent(uint16_t currentMA);
  
  // VBUS and power management
  VBusType getVBusType();
  String getVBusTypeName(VBusType type);
  bool isExternalPowerPresent();
  
  // Fault management
  bool clearFaults();
  uint8_t getFaultRegister();
  String decodeFaults(uint8_t faultReg);
  
  // Emergency modes
  bool enterEmergencyBatteryMode();
  bool exitEmergencyMode();
  bool isInEmergencyMode() const;
  
  // Power management and transitions
  bool checkStartupScenario(bool externalPowerPresent);
  bool handleUSBReconnection(bool externalPowerPresent);
  bool handlePowerLoss();
  bool prepareForShutdown();
  
  // Enhanced diagnostics
  void printExtendedDiagnostics();
  bool disableThermistorMonitoring();
  String decodeSystemStatus(uint8_t statusReg);
  String decodeVBusStatus(uint8_t vbusStatus);
  
  // Status reporting functions for clean UI
  String getFaultStatusReport();
  String getPowerStatusSummary();
  String getVoltageAnalysis();
  String getRegisterDiagnostics();
  
  // Advanced control functions (moved from main.cpp)
  bool repairRegisters();
  bool forceEnableBATFET();
  bool forceRestartCharging();
  String getChargeVoltageAnalysis();
  
  // Power transition detection with logging
  struct PowerTransition {
    bool stateChanged = false;
    String changeDescription = "";
    unsigned long timestamp = 0;
  };
  PowerTransition detectVBusChanges();
  
  // Simple monitoring (removed complex oscillation detection)
  bool isChargeOscillationDetected() const { return false; } // Legacy compatibility
  
  // Watchdog management
  bool disableWatchdog();
  
  // Voltage safety protection (LED protection)
  bool checkVoltageSafety();
  bool isVoltageSafe() const;
  bool forceEmergencyShutdown();
  bool resetWatchdog();
  
  // Ship mode (low power)
  bool enterShipMode();
  
  // Configuration and diagnostics
  BQ25895Config getConfig() const;
  String getLastError() const;
  bool performSelfTest();
  void printRegisters(); // Debug function
  
  // Register access (for advanced users)
  bool readRegister(uint8_t reg, uint8_t& value);
  bool writeRegister(uint8_t reg, uint8_t value);
};

#endif // BQ25895_DRIVER_H