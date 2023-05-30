/**
 * File: Photon_Moisture_Watch.ino v001
 * Author: Isaiah Guilfoile
 * Date: 05.14.2023
 * 
 * Notes:
 * Created for gaining digital values at different moisture states
 */


/////////////////////////////////////////////////////////////////
// After Watering   3300    3:00 p.m.   5/29
//                  3300    7:30 p.m.   5/29
//                  -       -           -
//                  -       -           -
// Lowest           -       -           -
/////////////////////////////////////////////////////////////////

#include <LCD_ST7032.h>
#include <SEN_13322.h>
#include "Particle.h"

LCD_ST7032 display;
SEN_13322 plant;

int digValue;

void setup() {
    display.begin();
    display.setcontrast(25);

    Particle.variable("digValue", digValue);

    plant.begin(A0, A1); // Pin A0 provides power to moisture sensor, Pin A1 performs ADC

    Serial.begin(9600);
}

void loop() {
    plant.readSequence();

    /** LCD Print Plant status on first line */
    display.setCursor(0,0);
    display.clear();
    display.print(plant.getStatus());
    uint8_t *waterTime = plant.getTimeFromLastWater();
    digValue = plant.getMoistureValue();

    /** LCD Print Time since last water on second line */
    display.setCursor(1,1);
    display.print(digValue, DEC);
    

    Serial.println(plant.getMoistureValue());

    Serial.print(*(waterTime+0));
    Serial.print(":");
    Serial.print(*(waterTime+1));
    Serial.print(":");
    Serial.println(*(waterTime+2));

    Serial.println(" ");

    delay(5s);
}
