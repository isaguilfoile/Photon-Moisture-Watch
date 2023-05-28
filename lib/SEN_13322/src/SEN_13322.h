/**
 * File: SEN_13322.h
 * Author: Isaiah Guilfoile
 * Date: 05.14.2023
 * 
 * Notes:
 * Master Library for SEN 13322 Soil Moisture Sensor
 * https://www.sparkfun.com/products/13322
 * Completely Original
 * © 2023 Isaiah Guilfoile
 */

#ifndef SEN_1322_h
#define SEN_1322_h

#define SOAKED 3000
#define WET 2000
#define DRY 1000

#define samplePeriod 10min

#include <Arduino.h>

class SEN_13322
{
    public:
        SEN_13322();
        void begin(pin_t power, pin_t analog);
        void readSequence();
        String getStatus();
        uint8_t * getTimeFromLastWater();
        uint16_t getMoistureValue();
        
    protected:
        uint16_t value = 0; // Digital Value from moisture soil sensor
        String status = "   NA   "; // Plant status to be printed to LCD
        time32_t lastWaterTime = Time.now(); // Last time the plant was watered
        uint8_t timeFromLastWater[3] = {0, 0, 0};
        pin_t powerPin;
        pin_t analogPin;
        void takeReading();
        void powerOn();
        void powerOff();
        void updateStatus();
};

#endif