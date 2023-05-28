//-------------------------------------------------------------------------------------------
// Tested Module    : ERC1602-4, EASTRISING TECHNOLOGY CO,.LTD.
// Drive IC         : ST7032
// INTERFACE        : I2C
// VDD              : 2.7V-5.5V
// Tested with MCU	: Arduino Uno, Attiny85@1mhz(5.0V), Attiny85@8mhz(5.0V) and ESP8266(3.3V)
//-------------------------------------------------------------------------------------------

#include <LCD_ST7032.h>

LCD_ST7032 display;

const byte contrastButtonPin = 3;
boolean lastButtonState = 1;

void setup() {
  pinMode(contrastButtonPin, INPUT);
  digitalWrite(contrastButtonPin, HIGH);
  display.begin();
  display.setcontrast(24); //contrast value range is 0-63, try 25@5V or 50@3.3V as a starting value
}

void loop() {
  boolean a = digitalRead(contrastButtonPin);
  if (a != lastButtonState) {
    if (!a) {
      display.adjcontrast(1); //increase contrast (-1 to decrease)
    }
    lastButtonState = a;
  }

  display.setCursor(0, 0);  //LINE 1 ADDRESS 0
  display.print("Contrast value:");
  display.setCursor(1, 0);  //LINE 2 ADDRESS 0
  byte c = display.getcontrast();
  display.print(c, DEC);
  display.write(' ');

}
