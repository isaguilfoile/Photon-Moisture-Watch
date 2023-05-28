/**
 * File: Photon_Moisture_Watch.ino v001
 * Author: Isaiah Guilfoile
 * Date: 05.14.2023
 * 
 * Notes:
 * NOT fully operation
 * 2x8 Character display works properly
 * Main File implements current pseudocode for ADC reading and LCD changes. No IoT yet
 */

#include <LCD_ST7032.h>
#include <SEN_13322.h>
#include "Particle.h"

LCD_ST7032 display;
SEN_13322 plant;

Timer timer(1000, &SEN_13322::readSequence, plant);

bool notificationNeeded = false;

void sendNotification(uint8_t days) {
  particle.publish("Water-Needed");

}

void setup() {
  display.begin();
  display.setcontrast(25);

  plant.begin(A0, A1); // Pin A0 provides power to moisture sensor, Pin A1 performs ADC

  Serial.begin(9600);

  // timer.changePeriod(samplePeriod);  // Take ADC Sample every 10 minutes
  timer.start();
}

void loop() {
  display.setCursor(0,0);
  display.clear();
  display.print(plant.getStatus());
  uint8_t *waterTime = plant.getTimeFromLastWater();

  display.setCursor(1,0);
  display.print(*(waterTime+0), DEC); // Print days
  display.print(":");
  display.print(*(waterTime+1), DEC); // Print hours
  display.print(":");
  display.print(*(waterTime+2), DEC); // Print minutes

  Serial.println(plant.getMoistureValue());
  delay(10);
}

