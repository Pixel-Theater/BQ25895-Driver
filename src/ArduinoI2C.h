#ifndef ARDUINO_I2C_H
#define ARDUINO_I2C_H

#include "BQ25895Driver.h"

#if defined(ARDUINO)
#include <Wire.h>
#include <Adafruit_I2CDevice.h>

// Helper class to create Adafruit_I2CDevice instances
class ArduinoI2C {
public:
    // Create an Adafruit_I2CDevice for BQ25895
    static Adafruit_I2CDevice* createDevice(TwoWire& wire = Wire1) {
        return new Adafruit_I2CDevice(BQ25895_I2C_ADDR, &wire);
    }
    
    // For backward compatibility - create and return device pointer
    explicit ArduinoI2C(TwoWire& wire = Wire1) : device_(createDevice(wire)) {}
    
    // Get the underlying Adafruit_I2CDevice
    Adafruit_I2CDevice* getDevice() { return device_; }
    
    ~ArduinoI2C() {
        delete device_;
    }
    
private:
    Adafruit_I2CDevice* device_;
};

#else
// Mock for testing - create a mock Adafruit_I2CDevice
class ArduinoI2C {
public:
    static Adafruit_I2CDevice* createDevice(void* wire = nullptr) {
        return new Adafruit_I2CDevice(BQ25895_I2C_ADDR, wire);
    }
    
    explicit ArduinoI2C(void* wire = nullptr) : device_(createDevice(wire)) {}
    
    Adafruit_I2CDevice* getDevice() { return device_; }
    
    ~ArduinoI2C() {
        delete device_;
    }
    
private:
    Adafruit_I2CDevice* device_;
};
#endif // ARDUINO

#endif // ARDUINO_I2C_H