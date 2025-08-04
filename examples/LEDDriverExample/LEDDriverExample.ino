/**
 * @file LEDDriverExample.ino
 * @brief LED Driver specific example with voltage safety protection
 * 
 * This example demonstrates using the BQ25895 in applications that drive LEDs
 * or other components sensitive to voltage spikes. It includes:
 * - Voltage safety monitoring (5.5V limit for LED protection)
 * - Power transition handling (USB connect/disconnect)
 * - Emergency shutdown on voltage violations
 * - LED strip power management
 * 
 * Safety Features:
 * - Automatic emergency shutdown if system voltage > 5.5V
 * - Graceful handling of USB power transitions
 * - Battery-only operation when external power is unsafe
 * 
 * Hardware Requirements:
 * - Teensy 4.x (recommended) or Arduino compatible
 * - BQ25895 breakout board
 * - LED strip or other 5V-sensitive load
 * - External power source (USB, wall adapter, etc.)
 * - Li-Ion battery
 */

#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include "BQ25895Driver.h"

// Pin definitions (adjust for your hardware)
#define LED_POWER_PIN 2        // Controls LED strip power (optional)
#define STATUS_LED_PIN 13      // Built-in LED for status indication
#define EXTERNAL_POWER_PIN 4   // Optional: external power detection pin

// Create I2C device and driver
#if defined(__IMXRT1062__) // Teensy 4.x recommended
  Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire1);
#else
  Adafruit_I2CDevice i2c_dev(BQ25895_I2C_ADDR, &Wire);
#endif

BQ25895Driver charger(&i2c_dev);

// Safety and power management variables
bool emergencyMode = false;
bool ledPowerEnabled = false;
unsigned long lastSafetyCheck = 0;
unsigned long lastStatusUpdate = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000);
  
  // Initialize pins
  pinMode(LED_POWER_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  if (EXTERNAL_POWER_PIN > 0) {
    pinMode(EXTERNAL_POWER_PIN, INPUT_PULLUP);
  }
  
  // Start with LED power OFF for safety
  digitalWrite(LED_POWER_PIN, LOW);
  digitalWrite(STATUS_LED_PIN, LOW);
  
  Serial.println("BQ25895 Driver - LED Application Example");
  Serial.println("========================================");
  Serial.println("This example demonstrates safe LED driving with voltage protection");
  
  // Initialize I2C
#if defined(__IMXRT1062__) // Teensy 4.x
  Wire1.begin();
  Wire1.setClock(100000);
#else
  Wire.begin();
  Wire.setClock(100000);
#endif
  
  // Configure for LED-safe operation using preset
  BQ25895Config config = BQ25895ConfigPresets::LEDDriver();
  // Optionally customize specific settings:
  // config.inputCurrentMA = 1200;   // Reduce if needed
  // config.voltageSafetyLimitMV = 5200;  // Lower safety limit if desired
  
  // Initialize charger
  Serial.print("Initializing BQ25895 for LED-safe operation... ");
  if (charger.initialize(config)) {
    Serial.println("SUCCESS");
    
    // Enable charging if voltage is safe
    if (performInitialSafetyCheck()) {
      charger.enableCharging();
      Serial.println("Charging enabled - voltage safe for LEDs");
    } else {
      Serial.println("WARNING: Initial voltage check failed");
    }
  } else {
    Serial.println("FAILED");
    Serial.print("Error: ");
    Serial.println(charger.getLastError());
    return;
  }
  
  Serial.println("\nVoltage Safety Monitoring Active");
  Serial.println("LED power will be controlled based on system voltage");
  Serial.println("\nCommands: 'led on', 'led off', 'emergency', 'status', 'help'");
  Serial.println();
}

void loop() {
  // Perform safety checks every 100ms
  if (millis() - lastSafetyCheck >= 100) {
    lastSafetyCheck = millis();
    performVoltageSafetyCheck();
  }
  
  // Status updates every 2 seconds
  if (millis() - lastStatusUpdate >= 2000) {
    lastStatusUpdate = millis();
    printSystemStatus();
  }
  
  // Handle serial commands
  if (Serial.available()) {
    handleSerialCommand();
  }
  
  // Update status LED
  updateStatusLED();
}

bool performInitialSafetyCheck() {
  Serial.print("Checking initial voltage safety... ");
  
  delay(100); // Allow readings to stabilize
  
  BQ25895Metrics metrics = charger.getMetrics();
  BQ25895Status status = charger.getStatus();
  
  Serial.print("System: ");
  Serial.print(metrics.systemVoltage / 1000.0, 2);
  Serial.print("V, Input: ");
  Serial.print(metrics.inputVoltage / 1000.0, 2);
  Serial.print("V ");
  
  // Check system voltage (should be < 5.5V for LED safety)
  if (metrics.systemVoltage > 5500) {
    Serial.println("UNSAFE - System voltage too high for LEDs");
    enterEmergencyMode("High system voltage detected");
    return false;
  }
  
  // Check input voltage if present
  if (status.inputDetected && metrics.inputVoltage > 6000) {
    Serial.println("WARNING - High input voltage detected");
    // Continue but monitor closely
  }
  
  Serial.println("SAFE");
  return true;
}

void performVoltageSafetyCheck() {
  if (!charger.checkVoltageSafety()) {
    // Driver's built-in safety check failed
    enterEmergencyMode("Driver voltage safety check failed");
    return;
  }
  
  BQ25895Metrics metrics = charger.getMetrics();
  
  // Additional LED-specific safety check
  if (metrics.systemVoltage > 5500) {
    enterEmergencyMode("System voltage exceeded 5.5V LED safety limit");
    return;
  }
  
  // If we were in emergency mode and voltage is now safe, consider recovery
  if (emergencyMode && metrics.systemVoltage < 5200) {  // 300mV hysteresis
    considerEmergencyRecovery();
  }
}

void enterEmergencyMode(const String& reason) {
  if (!emergencyMode) {
    emergencyMode = true;
    
    // Immediately disable LED power
    setLEDPower(false);
    
    // Enter battery-only mode
    charger.enterEmergencyBatteryMode();
    
    Serial.println();
    Serial.print("*** EMERGENCY MODE ACTIVATED: ");
    Serial.println(reason);
    Serial.println("*** LED power disabled for safety");
    Serial.println("*** Switched to battery-only operation");
  }
}

void considerEmergencyRecovery() {
  // Only attempt recovery if voltage has been stable and low for some time
  static unsigned long stableTime = 0;
  BQ25895Metrics metrics = charger.getMetrics();
  
  if (metrics.systemVoltage < 5200) {
    if (stableTime == 0) {
      stableTime = millis();
    } else if (millis() - stableTime > 5000) { // 5 seconds stable
      exitEmergencyMode();
      stableTime = 0;
    }
  } else {
    stableTime = 0; // Reset if voltage goes high again
  }
}

void exitEmergencyMode() {
  if (emergencyMode) {
    emergencyMode = false;
    
    // Exit emergency mode and re-enable charging
    charger.exitEmergencyMode();
    charger.enableCharging();
    
    Serial.println();
    Serial.println("*** Emergency mode deactivated - voltage stable");
    Serial.println("*** Normal operation resumed");
  }
}

void setLEDPower(bool enable) {
  if (enable && !emergencyMode) {
    BQ25895Metrics metrics = charger.getMetrics();
    if (metrics.systemVoltage < 5400) { // Extra safety margin
      digitalWrite(LED_POWER_PIN, HIGH);
      ledPowerEnabled = true;
      Serial.println("LED power enabled");
    } else {
      Serial.println("LED power denied - voltage too high");
    }
  } else {
    digitalWrite(LED_POWER_PIN, LOW);
    ledPowerEnabled = false;
    if (enable) {
      Serial.println("LED power disabled - emergency mode active");
    } else {
      Serial.println("LED power disabled");
    }
  }
}

void printSystemStatus() {
  BQ25895Status status = charger.getStatus();
  BQ25895Metrics metrics = charger.getMetrics();
  
  Serial.print("VSYS: ");
  Serial.print(metrics.systemVoltage / 1000.0, 2);
  Serial.print("V | VBAT: ");
  Serial.print(metrics.batteryVoltage / 1000.0, 2);
  Serial.print("V | ICHG: ");
  Serial.print(metrics.chargeCurrentMA);
  Serial.print("mA | ");
  Serial.print(charger.getVBusTypeName(status.vbusType));
  Serial.print(" | LED: ");
  Serial.print(ledPowerEnabled ? "ON" : "OFF");
  
  if (emergencyMode) {
    Serial.print(" | *** EMERGENCY MODE ***");
  }
  
  if (status.faultRegister != 0) {
    Serial.print(" | FAULT: ");
    Serial.print(charger.decodeFaults(status.faultRegister));
  }
  
  Serial.println();
}

void updateStatusLED() {
  static unsigned long lastBlink = 0;
  static bool ledState = false;
  
  unsigned long blinkInterval;
  
  if (emergencyMode) {
    blinkInterval = 200; // Fast blink in emergency
  } else if (ledPowerEnabled) {
    blinkInterval = 1000; // Slow blink when LED power is on
  } else {
    blinkInterval = 500; // Medium blink when LED power is off
  }
  
  if (millis() - lastBlink >= blinkInterval) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(STATUS_LED_PIN, ledState);
  }
}

void handleSerialCommand() {
  String command = Serial.readStringUntil('\n');
  command.trim();
  command.toLowerCase();
  
  if (command == "led on") {
    setLEDPower(true);
  } else if (command == "led off") {
    setLEDPower(false);
  } else if (command == "emergency") {
    enterEmergencyMode("Manual emergency activation");
  } else if (command == "reset emergency") {
    exitEmergencyMode();
  } else if (command == "status") {
    Serial.println("\n=== Detailed System Status ===");
    Serial.print(charger.getPowerStatusSummary());
    Serial.print(charger.getVoltageAnalysis());
    Serial.print("LED Power: ");
    Serial.println(ledPowerEnabled ? "ENABLED" : "DISABLED");
    Serial.print("Emergency Mode: ");
    Serial.println(emergencyMode ? "ACTIVE" : "INACTIVE");
    Serial.println("===============================\n");
  } else if (command == "help") {
    Serial.println("\nAvailable Commands:");
    Serial.println("  led on         - Enable LED power (if voltage safe)");
    Serial.println("  led off        - Disable LED power");
    Serial.println("  emergency      - Manually activate emergency mode");
    Serial.println("  reset emergency- Manually exit emergency mode");
    Serial.println("  status         - Show detailed status");
    Serial.println("  help           - Show this help");
    Serial.println();
  } else if (command != "") {
    Serial.println("Unknown command. Type 'help' for available commands.");
  }
}