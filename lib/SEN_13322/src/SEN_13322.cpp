/**
 * File: SEN_13322.cpp
 * Author: Isaiah Guilfoile
 * Date: 05.14.2023
 * 
 * Notes:
 * Master Library for SEN 13322 Soil Moisture Sensor
 * https://www.sparkfun.com/products/13322
 * Completely Original
 * © 2023 Isaiah Guilfoile
 */

#include <Arduino.h>
#include <SEN_13322.h>

SEN_13322::SEN_13322()
{
}

/// @brief Initialize ADC functionallity and power for sensor
/// @param power Pin name of power supply to sensor. Must recieve power from I/O pin
/// @param analog Pin name of ADC conversion pin
void SEN_13322::begin(pin_t power, pin_t analog) {
    pinMode(power, OUTPUT);
    digitalWrite(power, LOW);
    powerPin = power;
    analogPin = analog;
}

/// @brief Perform ADC conversion and save digital value
void SEN_13322::takeReading() {
    value = analogRead(analogPin);
    delay(10);
}

/// @brief Supply the sensor with power
void SEN_13322::powerOn() {
    digitalWrite(powerPin, HIGH);
}

/// @brief Remove power from the sensor Vin pin
void SEN_13322::powerOff() {
    digitalWrite(powerPin, LOW);
}

/// @brief Update the status string based on current digital value
/// NOTE: these values are not tested yet and are meaningless/ not operational
void SEN_13322::updateStatus() {
    if (value >= SOAKED) {
        status = " WET :) ";
    }
    else if (value <= DRY) {
        status = " DRY :( ";
        lastWaterTime = Time.now();
    }
    else {
        status = "DAMP :| ";
    }
}

/// @brief Perform read sequence as recommended by Sparkfun to limit corrosion. Update status after conversion is complete
void SEN_13322::readSequence() {
    powerOn();
    delay(10);
    takeReading();
    powerOff();
    updateStatus();
}

/// @brief Get current status of plant moisture
/// @return Moisture status string
String SEN_13322::getStatus() {
    return status;
}

/// @brief Find how long it has been in days:hours:minutes since the plant was last watered
/// @return Pointer to 3 elem array containing time values
uint8_t * SEN_13322::getTimeFromLastWater() {
    uint32_t totalSeconds = Time.now() - lastWaterTime; // Find number of seconds since the last water
    timeFromLastWater[0] = totalSeconds/86400;  // number of days since last water
    timeFromLastWater[1] = (totalSeconds - (timeFromLastWater[0]*86400))/3600;  // number of hours since last water - days
    timeFromLastWater[2] = (totalSeconds - (timeFromLastWater[1]*3600) - (timeFromLastWater[0]*86400))/60;
    
    return timeFromLastWater;
}

/// @brief Get digital value from moisture sensor at last reading
/// @return moisture value from last ADC sequence
uint16_t SEN_13322::getMoistureValue() {
    return value;
}