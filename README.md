# BQ25895 Driver Library

A comprehensive, platform-independent Arduino library for the Texas Instruments BQ25895 Li-Ion Battery Charge Management IC. This library provides high-level control, comprehensive status monitoring, and safety features for battery charging applications.

## Features

### Core Functionality
- **Complete Register Access**: Full control over all BQ25895 registers and features
- **Hardware Abstraction**: Platform-independent I2C interface with Arduino implementation
- **Comprehensive Status Monitoring**: Real-time voltage, current, and fault monitoring
- **Safety Features**: Voltage protection, thermal monitoring, and emergency shutdown
- **Power Management**: VBUS detection, power source switching, and ship mode support
- **Robust Error Handling**: Detailed error reporting and automatic retry mechanisms

### Advanced Features
- **Voltage Safety Protection**: Automatic shutdown at configurable voltage thresholds (default 5.5V for LED protection)
- **Power Transition Detection**: Automatic handling of USB connect/disconnect scenarios
- **Fault Diagnosis**: Detailed fault decoding and reporting
- **Charge Optimization**: DPM override, current limit adjustments, and charge restart
- **Emergency Modes**: Battery-only mode and ship mode for low-power applications
- **Comprehensive Diagnostics**: Register dumps, status reports, and voltage analysis

## Hardware Requirements

### Supported Platforms
- **Arduino Compatible Devices**: Arduino Uno, Nano, ESP32, ESP8266
- **Teensy Microcontrollers**: Teensy 4.0, 4.1 (primary target)
- **Custom Hardware**: Any microcontroller with I2C support

### I2C Configuration
- **Default Address**: 0x6A (fixed for BQ25895)
- **Clock Speed**: 100kHz (recommended for reliability)
- **Pull-up Resistors**: 4.7kΩ required on SDA/SCL lines
- **Voltage Levels**: 3.3V or 5V I2C compatible

## Quick Start

### Installation
```bash
# Clone the repository
git clone https://github.com/[org]/BQ25895Driver.git

# For PlatformIO projects
lib_deps = https://github.com/[org]/BQ25895Driver.git

# For Arduino IDE
# Download ZIP and install via Sketch > Include Library > Add .ZIP Library
```

### Basic Usage
```cpp
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include "BQ25895Driver.h"

// Create I2C device and driver (using industry-standard Adafruit BusIO)
Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire1);  // Use Wire1 for Teensy
BQ25895Driver charger(&i2c_dev);

void setup() {
    Serial.begin(115200);
    Wire1.begin();
    Wire1.setClock(100000);  // 100kHz for reliability
    
    // Configure for Li-Ion battery
    BQ25895Config config;
    config.inputCurrentMA = 1500;      // 1.5A input limit
    config.chargeCurrentMA = 1000;     // 1A charge current
    config.chargeVoltageNV = 4192;     // 4.192V (safe for 4.16V batteries)
    config.terminationCurrentMA = 64;  // 64mA termination
    config.vindpmThresholdMV = 4400;   // 4.4V VINDPM
    
    // Initialize the charger
    if (charger.initialize(config)) {
        Serial.println("BQ25895 initialized successfully");
        charger.enableCharging();
    } else {
        Serial.printf("Initialization failed: %s\n", charger.getLastError().c_str());
    }
}

void loop() {
    // Get current status and metrics
    BQ25895Status status = charger.getStatus();
    BQ25895Metrics metrics = charger.getMetrics();
    
    // Check for faults
    if (status.faultRegister != 0) {
        Serial.printf("Fault detected: %s\n", charger.decodeFaults(status.faultRegister).c_str());
    }
    
    // Print status
    Serial.printf("Charging: %s, VBAT: %.2fV, Current: %dmA\n",
                  status.chargingEnabled ? "YES" : "NO",
                  metrics.batteryVoltage / 1000.0,
                  metrics.chargeCurrentMA);
    
    delay(1000);
}
```

### Advanced Configuration
```cpp
// Configure for external VIN operation (≤5.5V for LED safety)
BQ25895Config config;
config.inputCurrentMA = 2000;      // Higher current for external supply
config.chargeCurrentMA = 1500;     // Faster charging
config.chargeVoltageNV = 4208;     // Higher voltage for full capacity
config.vindpmThresholdMV = 4600;   // Higher VINDPM for 6V+ supplies
config.disableWatchdog = true;     // Disable I2C watchdog
config.disableSafetyTimer = false; // Keep safety timer for production

// Voltage safety for LED applications
charger.initialize(config);
charger.enableCharging();

// Monitor voltage safety
if (!charger.checkVoltageSafety()) {
    Serial.println("EMERGENCY: Voltage too high for LEDs!");
    // System automatically enters protective mode
}
```

## API Reference

### Core Classes

#### `BQ25895Driver`
Main driver class providing complete BQ25895 control.

**Key Methods:**
```cpp
// Initialization
bool initialize(const BQ25895Config& config);
bool isInitialized() const;
void reset();

// Status and Monitoring
BQ25895Status getStatus();
BQ25895Metrics getMetrics();
VBusType getVBusType();

// Charging Control
bool enableCharging();
bool disableCharging();
bool setChargeCurrent(uint16_t currentMA);
bool setInputCurrentLimit(uint16_t currentMA);
bool setChargeVoltage(uint16_t voltageMV);

// Safety and Emergency
bool checkVoltageSafety();
bool forceEmergencyShutdown();
bool enterShipMode();

// Diagnostics
String getFaultStatusReport();
String getPowerStatusSummary();
String getRegisterDiagnostics();
```

#### `BQ25895Config`
Configuration structure for charger initialization.
```cpp
struct BQ25895Config {
    uint16_t inputCurrentMA = 1500;      // Input current limit
    uint16_t chargeCurrentMA = 2000;     // Charge current
    uint16_t chargeVoltageNV = 4208;     // Charge voltage (mV)
    uint16_t terminationCurrentMA = 128; // Termination current
    uint16_t vindpmThresholdMV = 3900;   // VINDPM threshold
    bool disableWatchdog = true;         // I2C watchdog control
    bool disableSafetyTimer = true;      // Safety timer control
};
```

#### `BQ25895Status` & `BQ25895Metrics`
Comprehensive status and measurement structures.
```cpp
struct BQ25895Status {
    VBusType vbusType;
    ChargeStatus chargeStatus;
    bool chargingEnabled;
    bool inputDetected;
    bool batteryDetected;
    uint8_t faultRegister;
    String lastError;
    unsigned long timestamp;
};

struct BQ25895Metrics {
    uint16_t batteryVoltage;    // mV
    uint16_t systemVoltage;     // mV  
    uint16_t inputVoltage;      // mV
    int16_t chargeCurrentMA;    // mA
    uint16_t tsVoltage;         // mV (thermistor)
    unsigned long timestamp;
};
```

### I2C Hardware Abstraction

#### `Adafruit_I2CDevice`
Using the industry-standard [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO) library for robust I2C communication.
```cpp
#include <Adafruit_I2CDevice.h>

Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire1);  // Use specific Wire interface
BQ25895Driver driver(&i2c_dev);
```

**Benefits of Adafruit BusIO:**
- ✅ Battle-tested by thousands of users
- ✅ Superior error handling and retry logic  
- ✅ Better platform compatibility
- ✅ Maintained by Adafruit team

## Safety Features

### Voltage Protection
The library includes automatic voltage monitoring to protect connected components (especially LEDs):

```cpp
// Automatic voltage safety checking
if (!charger.checkVoltageSafety()) {
    // System voltage > 5.5V - automatic emergency shutdown
    Serial.println("EMERGENCY: Voltage protection activated");
}

// Check if system is in emergency mode
if (charger.isInEmergencyMode()) {
    Serial.println("System in protective shutdown mode");
}
```

### Thermal Protection
Built-in thermal monitoring with NTC thermistor support:
```cpp
BQ25895Metrics metrics = charger.getMetrics();
if (metrics.tsVoltage < 2400 || metrics.tsVoltage > 3700) {
    Serial.printf("Thermal protection: TS voltage %.2fV\n", metrics.tsVoltage / 1000.0);
}
```

### Fault Detection
Comprehensive fault monitoring and reporting:
```cpp
uint8_t faults = charger.getFaultRegister();
if (faults != 0) {
    String faultDesc = charger.decodeFaults(faults);
    Serial.printf("Faults detected: %s\n", faultDesc.c_str());
    charger.clearFaults();  // Clear after handling
}
```

## Debugging and Diagnostics

### Register Diagnostics
```cpp
// Full register dump for debugging
Serial.print(charger.getRegisterDiagnostics());

// Voltage analysis
Serial.print(charger.getVoltageAnalysis());

// Power status summary
Serial.print(charger.getPowerStatusSummary());
```

### Error Handling
```cpp
if (!charger.setChargeCurrent(1500)) {
    Serial.printf("Failed to set charge current: %s\n", charger.getLastError().c_str());
}
```

## Integration Examples

### Arduino Uno/Nano
```cpp
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include "BQ25895Driver.h"

Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire);  // Use default Wire
BQ25895Driver charger(&i2c_dev);
```

### Teensy 4.x (Recommended)
```cpp
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include "BQ25895Driver.h"

Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire1);  // Use Wire1 for better pin placement
BQ25895Driver charger(&i2c_dev);
```

### ESP32
```cpp
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include "BQ25895Driver.h"

// Custom I2C pins for ESP32
Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire);
BQ25895Driver charger(&i2c_dev);

void setup() {
    Wire.begin(21, 22);  // SDA=21, SCL=22 for ESP32
    // ... rest of setup
}
```

## Refactoring from Application Code

### Changes Required for Standalone Library

1. **Remove Application-Specific Constants**
   - Move voltage limits to configurable parameters
   - Remove LED-specific safety hardcoding
   - Make emergency thresholds configurable

2. **Enhance Hardware Abstraction** 
   - Add more I2C interface implementations
   - Support different Wire interfaces more flexibly
   - Add platform detection and optimization

3. **Configuration Improvements**
   - Add preset configurations for common applications
   - Battery chemistry profiles (Li-Ion, LiFePO4, etc.)
   - Application-specific profiles (LED drivers, portable devices, etc.)

4. **Documentation and Examples**
   - Platform-specific examples
   - Integration guides for different hardware
   - Advanced configuration examples

### Removed from main.cpp Integration
The following application-specific code will be moved to the main application:
- LED control and animation logic
- Button handling and user interface
- Status display and logging formatting
- Application-specific state machines
- Power management policies specific to the product

### New Dependencies for main.cpp
After refactoring, main.cpp will:
- Use the library as a clean dependency
- Implement application-specific logic in the main file
- Handle battery detection using BatterySystem library
- Manage LED safety through library's voltage monitoring

## Contributing

1. Fork the repository
2. Create a feature branch
3. Add tests for new functionality
4. Ensure compatibility across supported platforms
5. Submit a pull request

## License

[License details to be determined]

## Version History

- **v1.0.0**: Initial standalone release
  - Complete BQ25895 register control
  - Arduino/Teensy compatibility
  - Voltage safety features
  - Comprehensive diagnostics

## Support

- GitHub Issues: Report bugs and request features
- Documentation: Full API reference and examples
- Community: Platform-specific integration help

---

This library is designed for professional battery charging applications requiring robust control, comprehensive monitoring, and safety features. It provides the foundation for building reliable battery-powered devices across multiple platforms.