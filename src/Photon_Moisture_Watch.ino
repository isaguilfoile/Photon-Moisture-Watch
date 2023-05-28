/**
 * File: Photon_Moisture_Watch.ino v001
 * Author: Isaiah Guilfoile
 * Date: 05.14.2023
 * 
 * Notes:
 * Created for gaining digital values at different moisture states
 */

#include <LCD_ST7032.h>
#include <SEN_13322.h>
#include "Particle.h"

LCD_ST7032 display;
SEN_13322 plant;

void setup() {
    display.begin();
    display.setcontrast(25);

    plant.begin(A0, A1); // Pin A0 provides power to moisture sensor, Pin A1 performs ADC

    Serial.begin(9600);
}

void loop() {
    /** LCD Print Plant status on first line */
    display.setCursor(0,0);
    display.clear();
    display.print(plant.getStatus());
    uint8_t *waterTime = plant.getTimeFromLastWater();

    /** LCD Print Time since last water on second line */
    display.setCursor(1,0);
    display.print(*(waterTime+0), DEC); // Print days
    display.print(":");
    display.print(*(waterTime+1), DEC); // Print hours
    display.print(":");
    display.print(*(waterTime+2), DEC); // Print minutes

    Serial.println(plant.getMoistureValue());
    delay(500);
}

