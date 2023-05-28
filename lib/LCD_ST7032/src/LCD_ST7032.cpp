/**
 * File: LCD_ST7032.cpp
 * Author: Isaiah Guilfoile
 * Date: 5.15.2023
 * 
 * Master Library for ST7032 LCD Character Display
 * Based on LCD_ST7032 library by Olav Kallhovd sept2017 https://github.com/olkal/LCD_ST7032/tree/master
 */

#include <Arduino.h>
#include <LCD_ST7032.h>

LCD_ST7032::LCD_ST7032() 
{ 
} 

void LCD_ST7032::begin() 
{
	Wire.begin();
	delay(100);
	Write_Instruction(0b00111000);	// Function set, normal instruction mode
    Write_Instruction(0b00111001);	// Function set, extended instruction mode
	Write_Instruction(0b00010100);	// Interval osc
	Write_Instruction(0b01110000);	// constrast C3-C0
	Write_Instruction(0b01011110);	// Ion, Bon, C5-C4
	Write_Instruction(0b01101100);	// follower control

	delay(200);

	Write_Instruction(0b00111000);	// function set, normal instruction mode
	Write_Instruction(0b00001100);	// Display On
	Write_Instruction(0b00000001);	// Clear Display

	Serial.println("Done with initialization");
}	

void LCD_ST7032::Write_Instruction(uint8_t cmd)
{
	Wire.beginTransmission(Write_Address);
	Wire.write(CNTRBIT_CO);  
	Wire.write(cmd);
	Wire.endTransmission();
	delayMicroseconds(WRITE_DELAY_MS);
}

void LCD_ST7032::Write_Data(uint8_t data)
{
	Wire.beginTransmission(Write_Address);
	Wire.write(CNTRBIT_RS); 
	Wire.write(data);
	Wire.endTransmission();
	delayMicroseconds(WRITE_DELAY_MS);
}

size_t LCD_ST7032::write(uint8_t chr) 
{
	this->Write_Data(chr);
	return 1;
}

void LCD_ST7032::clear() { //clear display
	Write_Instruction(CLEAR_DISPLAY);
	delayMicroseconds(HOME_CLEAR_DELAY_MS);
}

void LCD_ST7032::home() { //return to first line address 0
	this->Write_Instruction(RETURN_HOME);
	delayMicroseconds(HOME_CLEAR_DELAY_MS);
}

void LCD_ST7032::setCursor(uint8_t line, uint8_t pos) 
{
	uint8_t p;
	if(pos > 15) pos = 0;
	if(line == 0) p = LINE_1_ADR + pos;
	else p = LINE_2_ADR + pos;
	Write_Instruction(SET_DDRAM_ADDRESS | p);
}

void LCD_ST7032::display() //turn on display
{ 
	displayOnOffSetting |= DISPLAY_ON_OFF_D;
	Write_Instruction(displayOnOffSetting);
}

void LCD_ST7032::noDisplay() //turn off display
{ 
	displayOnOffSetting &= ~DISPLAY_ON_OFF_D;
	Write_Instruction(displayOnOffSetting);
}

void LCD_ST7032::cursor() //display underline cursor
{ 
	displayOnOffSetting |= DISPLAY_ON_OFF_C;
	Write_Instruction(displayOnOffSetting);
}

void LCD_ST7032::noCursor() //stop display underline cursor
{ 
	displayOnOffSetting &= ~DISPLAY_ON_OFF_C;
	Write_Instruction(displayOnOffSetting);
}

void LCD_ST7032::blink() //cursor block blink
{ 
	displayOnOffSetting |= DISPLAY_ON_OFF_B;
	Write_Instruction(displayOnOffSetting);
}

void LCD_ST7032::noBlink() //stop cursor block blink
{ 
	displayOnOffSetting &= ~DISPLAY_ON_OFF_B;
	Write_Instruction(displayOnOffSetting);
}

void LCD_ST7032::setcontrast(int val) 
{
	if (val > CONTRAST_MAX) val = CONTRAST_MIN;
	else if (val < CONTRAST_MIN) val = CONTRAST_MAX;
	Write_Instruction(CONTRAST_SET | (val & B00001111));
	Write_Instruction((val >> 4) | POWER_ICON_BOST_CONTR | POWER_ICON_BOST_CONTR_Bon);
	contrast = val;
}

void LCD_ST7032::adjcontrast(int val) 
{
	setcontrast(val + contrast);
}

uint8_t LCD_ST7032::getcontrast() 
{
	return contrast;
}
