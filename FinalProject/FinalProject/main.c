#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000L
#include <util/delay.h>


#include "Drivers/nokia5110.h"
#include "Drivers/rtc2.h"
#define UART_BAUD_RATE 9600
// itoa can print numbers
// char * stringName = "What we want in the string"

// this file generated by Image2GLCD
const unsigned char img[504] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x02, 0x1E, 0xF7, 0xBF, 0x7E, 0xFB, 0xEF, 0xBF, 0x00, 0x00, 0xE0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x9C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1E,
	0x18, 0x06, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x30, 0x03, 0x10, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x20, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x60, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0E, 0x60, 0x01, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x18, 0x30, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0C, 0x06, 0x10, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x06, 0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x61, 0xF0,
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xC0, 0x00, 0x17, 0xBD, 0xEF, 0x7D, 0xF7, 0xDF,
	0x7D, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x10, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x10, 0x00, 0x1F, 0xF0, 0x00,
	0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x1E, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x00,
	0x03, 0xE0, 0x12, 0x00, 0x01, 0x18, 0x00, 0x00, 0x00, 0x00, 0x06, 0x40, 0x02, 0x00, 0x03, 0x0C,

	0x00, 0x07, 0xF8, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x0E, 0x06, 0x00, 0x04, 0xCC, 0x00, 0x08, 0x00,
	0x0C, 0x00, 0x18, 0x03, 0x00, 0x1C, 0x07, 0x80, 0x0E, 0x00, 0x04, 0x00, 0x30, 0x01, 0xC0, 0x64,
	0x04, 0xC0, 0x03, 0x87, 0x18, 0x00, 0xE0, 0x78, 0x7C, 0x40, 0x00, 0x40, 0x00, 0xFD, 0xF0, 0x1F,
	0x80, 0xCC, 0x06, 0x48, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x1C, 0x41, 0x04, 0x18, 0x79, 0x8F, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x41, 0x8C, 0x10, 0x07, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xF8,
	0x10, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0xFC, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x84, 0x20, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x84, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x21, 0x94, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x14, 0x40, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x21, 0x1C, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x84,
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x03,
	0xF8, 0x00, 0x03, 0xC0, 0x01, 0xFF, 0xF8, 0x00, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0F, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};







int main(void)
{	
	nokia_lcd_init();
	nokia_lcd_clear();
	DDRD |= 0b00000011;
	char buf[10] = {0};
	char cursorPosition = 0;
	char cursorBlink = 0;
	char timeMinutes = 0;
	char timeHours = 0;
	char slash = 0x5C;
	
	rtc2_init();
	
	RTC2_VALUE->seconds = 1;
	RTC2_VALUE->minutes = 31;
	RTC2_VALUE->hours = 13;
	RTC2_VALUE->date = 3;
	RTC2_VALUE->month = 31;
	RTC2_VALUE->year = 17;
	RTC2_VALUE->format = RTC2_FORMAT_PM;
	rtc2_preset(RTC2_VALUE);
	
	/*
	nokia_lcd_clear();
	nokia_lcd_set_cursor(10,20);
	nokia_lcd_write_string("Please Enter",1);
	nokia_lcd_set_cursor(17,28);
	nokia_lcd_write_string("The Time.",1);
	nokia_lcd_render();
	nokia_lcd_clear();
	_delay_ms(2000);
	*/
			
	while(1){
			if(cursorPosition == 3){break;}
			if(cursorPosition == 0){ nokia_lcd_set_cursor(12,0); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(20,0); nokia_lcd_write_char(slash,2);}
			nokia_lcd_set_cursor(5,16);
			if(timeHours < 10) {nokia_lcd_write_string("0",3);}
			nokia_lcd_write_string(itoa(timeHours,buf,10), 3);
			nokia_lcd_set_cursor(40,16);
			if(timeMinutes < 10) {nokia_lcd_write_string("0",3);}
			nokia_lcd_write_string(itoa(timeMinutes,buf,10), 3);
			nokia_lcd_render();
			if ((PIND & 0x01) && (cursorPosition == 0)){timeHours++; _delay_ms(500);}
			else if ((PIND & 0x01) && (cursorPosition == 1)){timeMinutes++; _delay_ms(100);}
			else if (PIND & 0x02){cursorPosition++; _delay_ms(500);}
	}
	
	while(1){
	drawImage(img);
	rtc2_update(RTC2_VALUE);
	nokia_lcd_set_cursor(6, 6);
	nokia_lcd_write_string(itoa(RTC2_VALUE->hours,buf,10),1);
	nokia_lcd_write_string(":",1);
	nokia_lcd_write_string(itoa(RTC2_VALUE->minutes,buf,10),1);
	nokia_lcd_write_string(":",1);
	if(RTC2_VALUE->seconds < 10){nokia_lcd_write_string("0",1);}
	nokia_lcd_write_string(itoa(RTC2_VALUE->seconds,buf,10),1);
	nokia_lcd_render();
	nokia_lcd_clear();
	_delay_ms(100);
	}
}

void drawImage(const unsigned char img[504]){
	int y = 0;
	int i = 0;
	int counter = 0;
	while(y != 48){
		while(i <= 79){
			if(img[counter] & 0x80){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(i == 84){break;}
			if(img[counter] & 0x40){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(i == 84){break;}
			if(img[counter] & 0x20){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(i == 84){break;}
			if(img[counter] & 0x10){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(i == 84){break;}
			if(img[counter] & 0x08){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(i == 84){break;}
			if(img[counter] & 0x04){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(i == 84){break;}
			if(img[counter] & 0x02){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(img[counter] & 0x01){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(i == 84){break;}
			counter++;

		}
		if(i == 84){
			y++;
			i = 0;
			if(img[counter] & 0x08){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(img[counter] & 0x04){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(img[counter] & 0x02){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(img[counter] & 0x01){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			counter++;
		}
		else{
			i = 0;
		y++;}

	}
}