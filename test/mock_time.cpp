/**
 * @file mock_time.cpp
 * @brief Mock time functions for unit testing
 * 
 * This file provides mock implementations of Arduino's millis() function
 * and related time utilities for deterministic testing without hardware.
 */

#include <cstdint>

// Global mock time variable
unsigned long mock_millis = 1000; // Start with non-zero value for tests

/**
 * Mock implementation of Arduino's millis() function
 * @return Current mock time in milliseconds
 */
unsigned long millis() {
    return mock_millis;
}

/**
 * Advance the mock time by specified milliseconds
 * @param ms Milliseconds to advance
 */
void advance_time(unsigned long ms) {
    mock_millis += ms;
}

/**
 * Reset mock time to zero
 */
void reset_time() {
    mock_millis = 0;
}