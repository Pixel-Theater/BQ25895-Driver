/**
 * @file BasicUsage.ino
 * @brief Basic example demonstrating BQ25895 driver usage
 * 
 * This example shows the fundamental operations:
 * - Initialize the BQ25895 charge controller
 * - Configure charging parameters
 * - Monitor battery status and measurements
 * - Handle basic fault detection
 * 
 * Hardware Requirements:
 * - Arduino, Teensy, or ESP32
 * - BQ25895 breakout board
 * - I2C connections (SDA/SCL + 4.7kΩ pull-ups)
 * - Li-Ion battery (optional for testing)
 * 
 * Connections:
 * - Teensy 4.x: SDA=18, SCL=19 (Wire1) 
 * - Arduino Uno: SDA=A4, SCL=A5 (Wire)
 * - ESP32: SDA=21, SCL=22 (Wire) or custom pins
 */

#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include "BQ25895Driver.h"

// Create I2C device and driver instances
#if defined(__IMXRT1062__) // Teensy 4.x
  Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire1);  // Use Wire1 for better pin placement
#else
  Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire);   // Use default Wire for most boards
#endif

BQ25895Driver charger(&i2c_dev);

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000); // Wait for serial or timeout
  
  Serial.println("BQ25895 Driver - Basic Usage Example");
  Serial.println("=====================================");
  
  // Initialize I2C
#if defined(__IMXRT1062__) // Teensy 4.x
  Wire1.begin();
  Wire1.setClock(100000);  // 100kHz for reliability
#elif defined(ESP32)
  Wire.begin(21, 22);      // ESP32: SDA=21, SCL=22
  Wire.setClock(100000);
#else
  Wire.begin();
  Wire.setClock(100000);
#endif
  
  // Configure the charger for basic Li-Ion battery charging
  BQ25895Config config;
  config.inputCurrentMA = 1500;      // 1.5A input current limit
  config.chargeCurrentMA = 1000;     // 1A charge current (adjust for your battery)
  config.chargeVoltageNV = 4192;     // 4.192V charge voltage (conservative)
  config.terminationCurrentMA = 64;  // 64mA termination current
  config.vindpmThresholdMV = 4400;   // 4.4V VINDPM threshold
  config.disableWatchdog = true;     // Disable I2C watchdog for development
  config.disableSafetyTimer = false; // Keep safety timer enabled
  
  // Initialize the charger
  Serial.print("Initializing BQ25895... ");
  if (charger.initialize(config)) {
    Serial.println("SUCCESS");
    Serial.println("Driver initialized successfully");
    
    // Enable charging
    if (charger.enableCharging()) {
      Serial.println("Charging enabled");
    } else {
      Serial.println("Failed to enable charging");
    }
  } else {
    Serial.println("FAILED");
    Serial.print("Error: ");
    Serial.println(charger.getLastError());
    Serial.println("Check I2C connections and BQ25895 power");
  }
  
  Serial.println("\nStarting monitoring loop...");
  Serial.println("Time(s)\tVBUS\tStatus\tVBAT(V)\tICHG(mA)\tFaults");
  Serial.println("------------------------------------------------------------");
}

void loop() {
  static unsigned long lastPrint = 0;
  
  // Print status every 2 seconds
  if (millis() - lastPrint >= 2000) {
    lastPrint = millis();
    
    // Get current status and measurements
    BQ25895Status status = charger.getStatus();
    BQ25895Metrics metrics = charger.getMetrics();
    
    // Print basic status line
    Serial.print(millis() / 1000);
    Serial.print("\t");
    Serial.print(charger.getVBusTypeName(status.vbusType));
    Serial.print("\t");
    
    // Print charge status
    switch (status.chargeStatus) {
      case ChargeStatus::NOT_CHARGING:
        Serial.print("Not Charging");
        break;
      case ChargeStatus::PRE_CHARGE:
        Serial.print("Pre-Charge");
        break;
      case ChargeStatus::FAST_CHARGE:
        Serial.print("Fast Charge");
        break;
      case ChargeStatus::CHARGE_TERMINATION:
        Serial.print("Terminated");
        break;
    }
    Serial.print("\t");
    
    // Print voltage and current
    Serial.print(metrics.batteryVoltage / 1000.0, 3);
    Serial.print("\t");
    Serial.print(metrics.chargeCurrentMA);
    Serial.print("\t");
    
    // Print faults if any
    if (status.faultRegister != 0) {
      Serial.print(charger.decodeFaults(status.faultRegister));
    } else {
      Serial.print("None");
    }
    Serial.println();
    
    // Handle any errors
    if (charger.getLastError() != "") {
      Serial.print("Warning: ");
      Serial.println(charger.getLastError());
    }
  }
  
  // Check for serial commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "status") {
      printDetailedStatus();
    } else if (command == "enable") {
      charger.enableCharging();
      Serial.println("Charging enabled");
    } else if (command == "disable") {
      charger.disableCharging();
      Serial.println("Charging disabled");
    } else if (command == "reset") {
      charger.reset();
      Serial.println("Driver reset - will reinitialize on next loop");
    } else if (command == "help") {
      printHelp();
    } else {
      Serial.println("Unknown command. Type 'help' for available commands.");
    }
  }
}

void printDetailedStatus() {
  Serial.println("\n=== Detailed Status Report ===");
  Serial.print(charger.getPowerStatusSummary());
  Serial.print(charger.getFaultStatusReport());
  Serial.print(charger.getVoltageAnalysis());
  Serial.println("==============================\n");
}

void printHelp() {
  Serial.println("\nAvailable Commands:");
  Serial.println("  status  - Show detailed status report");
  Serial.println("  enable  - Enable charging");
  Serial.println("  disable - Disable charging");
  Serial.println("  reset   - Reset driver");
  Serial.println("  help    - Show this help");
  Serial.println();
}