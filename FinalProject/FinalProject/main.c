#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000L
#include <util/delay.h>


#include "Drivers/nokia5110.h"
#include "Drivers/dht.h"
#include "Drivers/uart.h"
#include "Drivers/hw_dht11.h"
#define UART_BAUD_RATE 9600
// itoa can print numbers
// char * stringName = "What we want in the string"


// this file generated by Image2GLCD
const unsigned char img[504] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x3E,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0F, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xE1, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C,
	0xE1, 0xEF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0xE1, 0xCF, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x39, 0xE1, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0xC1, 0xDF,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xC1, 0xDF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1F, 0x81, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0xFC, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xCF, 0x38, 0xF7,

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xDE, 0x3C, 0xF7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x9E, 0x7C, 0xF3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xBE, 0x7C, 0xFB, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x03, 0x3E, 0x7C, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3E,
	0x7C, 0xFD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7E, 0x7C, 0xFC, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7E, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xFE, 0xFC,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3E, 0xFE, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0xFE, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};







const int i;
const int j;

int main(void)
{	
	//sei();
	nokia_lcd_init();
	nokia_lcd_clear();
	//char *test1 = "Hey this is a number %u";
	//int test = 2;
	int i = 0;
	int y = 0;
	int test = 15;
	int counter = 0;
	//int counter2 = 0;
	//char write[8];
	char str[10];
	//ar * str = "whatever";
	//nokia_lcd_write_string(itoa(test,str,10),1);
	//kia_lcd_write_string(str, 1);
	/*
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
	*/
	char printbuff[100];

	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init interrupt
	sei();

	int8_t temperature = 0;
	int8_t humidity = 0;
	

	for (;;) {
		dht_gettemperaturehumidity(&temperature, &humidity);

						nokia_lcd_write_string(itoa(temperature, printbuff, 10), 1);
			nokia_lcd_render();
			
		


		_delay_ms(1500);
	}
	
	return 0;
	
	while(1) {}
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