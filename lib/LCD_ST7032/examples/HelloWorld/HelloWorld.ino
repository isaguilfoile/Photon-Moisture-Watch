//-------------------------------------------------------------------------------------------
// Tested Module    : ERC1602-4, EASTRISING TECHNOLOGY CO,.LTD.
// Drive IC         : ST7032
// INTERFACE        : I2C
// VDD              : 2.7V-5.5V
// Tested with MCU	: Arduino Uno, Attiny85@1mhz(5.0V), Attiny85@8mhz(5.0V) and ESP8266(3.3V)
//-------------------------------------------------------------------------------------------

#include <LCD_ST7032.h>

LCD_ST7032 display;

void setup() {
  display.begin();
  display.setcontrast(24); //contrast value range is 0-63, try 25@5V or 50@3.3V as a starting value
}

void loop() {
  static int counter = 0;
  
  // Write a piece of text on the first line...
  display.setCursor(0, 0);  //LINE 1, ADDRESS 0
  display.print("Hello World");

  // Write the counter on the second line...
  display.setCursor(1, 0);
  display.print(counter/10, DEC);
  display.write('.');
  display.print(counter%10, DEC);
  display.write(' ');
  delay(500);
  counter++;
}