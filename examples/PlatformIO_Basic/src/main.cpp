/*
 * BQ25895 Driver - PlatformIO Example
 * 
 * This example is designed specifically for PlatformIO projects.
 * For Arduino IDE, use the .ino examples in the parent directories.
 */

#include <Arduino.h>
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
  while (!Serial && millis() < 3000); // Wait for Serial on USB boards
  
  Serial.println("BQ25895 Driver - PlatformIO Example");
  Serial.println("===================================");
  
  // Initialize I2C
  #if defined(__IMXRT1062__) // Teensy 4.x
    Wire1.begin();
    Serial.println("Using Wire1 (Teensy 4.x)");
  #else
    Wire.begin();
    Serial.println("Using Wire (default)");
  #endif
  
  // Configure for general use
  BQ25895Config config = BQ25895ConfigPresets::PortableDevice();
  
  if (charger.initialize(config)) {
    Serial.println("✅ BQ25895 initialized successfully!");
    
    // Run self-test
    if (charger.performSelfTest()) {
      Serial.println("✅ Self-test passed");
    } else {
      Serial.println("❌ Self-test failed");
    }
    
    Serial.println("\nCommands: 'status', 'enable', 'disable', 'reset'");
  } else {
    Serial.println("❌ Failed to initialize BQ25895");
    Serial.print("Error: ");
    Serial.println(charger.getLastError());
  }
}

void loop() {
  static unsigned long lastUpdate = 0;
  
  // Update status every 5 seconds
  if (millis() - lastUpdate > 5000) {
    lastUpdate = millis();
    
    if (charger.isInitialized()) {
      BQ25895Status status = charger.getStatus();
      
      Serial.println("\n--- Status Update ---");
      Serial.print("Charging Enabled: ");
      Serial.println(status.chargingEnabled ? "Yes" : "No");
      Serial.print("Charge Status: ");
      Serial.println(static_cast<int>(status.chargeStatus));
      Serial.print("VBUS Type: ");
      Serial.println(static_cast<int>(status.vbusType));
      Serial.print("Input Detected: ");
      Serial.println(status.inputDetected ? "Yes" : "No");
      
      if (status.lastError.length() > 0) {
        Serial.print("Error: ");
        Serial.println(status.lastError);
      }
    }
  }
  
  // Handle serial commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "status") {
      BQ25895Status status = charger.getStatus();
      Serial.println("\n=== Detailed Status ===");
      Serial.print(charger.getPowerStatusSummary());
    } else if (command == "enable") {
      charger.enableCharging();
      Serial.println("Charging enabled");
    } else if (command == "disable") {
      charger.disableCharging();
      Serial.println("Charging disabled");
    } else if (command == "reset") {
      charger.reset();
      Serial.println("Driver reset");
    } else if (command.length() > 0) {
      Serial.println("Unknown command. Available: status, enable, disable, reset");
    }
  }
}