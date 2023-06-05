/**
 * @file SEN_13322.h
 * @author Isaiah Guilfoile (isaiahguilfoile@gmail.com)
 * @brief Header file for SEN 13322 Soil Moisture Sensor Class
 * @version 0.1
 * @date 2023-05-14
 * 
 * @copyright Copyright (c) 2023 Isaiah Guilfoile
 * 
 */

#ifndef SEN_1322_h
#define SEN_1322_h

#define samplePeriod 10min
#define SOAKED 3300
#define DRY 1800
#define MOIST 2550

#include <Arduino.h>

class SEN_13322
{
    public:
        /**
         * @brief Construct a new sen 13322 object
         * 
         */
        SEN_13322();

        /**
         * @brief Initialize ADC functionality and power for sensor
         * 
         * #### Faults
         * 
         * - n/a
         * 
         * @param power Pin name of power supply to sensor. Must receive power from I/O pin
         * @param analog Pin name of ADC conversion pin
         */
        void begin(pin_t power, pin_t analog);

        /**
         * @brief Perform read sequence as recommended by Sparkfun to limit corrosion. Update status after conversion is complete
         * 
         * #### Extended Description
         * 
         * - Moisture sensor only receives power when performing a read
         * 
         * #### Faults
         * 
         * - n/a
         * 
         */
        void readSequence();

        /**
         * @brief Get the Status String from digital moisture value
         * 
         * #### Extended Description
         * 
         * - Status string is given in format fit for LCD Character Display
         * 
         * #### Faults
         * 
         * - Probably inefficient to track moisture status as a String
         * - Conversion from digital value to status String has not been tested yet
         * 
         * @return String Indication of soil moisture status
         */
        String getStatus();

        /**
         * @brief Find how long it has been in days:hours:minutes since the plant was last watered
         * 
         * #### Faults:
         * 
         * - Still have to determine how frequently the plant must be watered
         * 
         * @return uint8_t* Pointer to 3 elem array containing time values
         */
        uint8_t * getTimeFromLastWater();

        /**
         * @brief Get digital value from moisture sensor at last reading
         * 
         * #### Faults
         * 
         * - n/a
         * 
         * @return uint16_t moisture value from last ADC sequence
         */
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