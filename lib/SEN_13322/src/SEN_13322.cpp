/**
 * @file SEN_13322.cpp
 * @author Isaiah Guilfoile (isaiahguilfoile@gmail.com)
 * @brief Master SEN 13222 Soil Moisture Sensor Class
 * @link https://www.sparkfun.com/products/13322
 * @version 0.1
 * @date 2023-05-14
 * 
 * @copyright Copyright (c) 2023 Isaiah Guilfoile
 * 
 */

#include <Arduino.h>
#include <SEN_13322.h>

SEN_13322::SEN_13322()
{
}

void SEN_13322::begin(pin_t power, pin_t analog) {
    pinMode(power, OUTPUT);
    digitalWrite(power, LOW);
    powerPin = power;
    analogPin = analog;
}

void SEN_13322::takeReading() {
    value = analogRead(analogPin);
    delay(10);
}

void SEN_13322::powerOn() {
    digitalWrite(powerPin, HIGH);
}

void SEN_13322::powerOff() {
    digitalWrite(powerPin, LOW);
}

void SEN_13322::updateStatus() {
    if (value >= SOAKED) {
        status = " WET :) ";
        lastWaterTime = Time.now();
    }
    else if (value <= DRY) {
        status = " DRY :( ";
    }
    else {
        status = "DAMP :| ";
    }
}

void SEN_13322::readSequence() {
    powerOn();
    delay(10);
    takeReading();
    powerOff();
    updateStatus();
}

String SEN_13322::getStatus() {
    return status;
}

uint8_t * SEN_13322::getTimeFromLastWater() {
    uint32_t totalSeconds = Time.now() - lastWaterTime; // Find number of seconds since the last water
    timeFromLastWater[0] = totalSeconds/86400;  // number of days since last water
    timeFromLastWater[1] = (totalSeconds - (timeFromLastWater[0]*86400))/3600;  // number of hours since last water - days
    timeFromLastWater[2] = (totalSeconds - (timeFromLastWater[1]*3600) - (timeFromLastWater[0]*86400))/60;
    
    return timeFromLastWater;
}

uint16_t SEN_13322::getMoistureValue() {
    return value;
}