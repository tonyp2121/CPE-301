#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>

#define F_CPU 8000000L
#include <util/delay.h>


#include "Drivers/nokia5110.h"
#include "Drivers/rtc2.h"
#define UART_BAUD_RATE 9600
#define DHT11_PIN 0

void temp_setup();
int read_dht11_dat();
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
	DDRD = 0xE0;
	char PinTracker;
	nokia_lcd_init();
	nokia_lcd_clear();
	DDRD |= 0b10000011;
	int delayTimeBetweenBeeps = 300;
	char buf[10] = {0};
	char ButtonBTime = 0;
	char cursorPosition = 0;
	char cursorBlink = 0;
	char timeMinutes = 0;
	char timeHours = 0;
	char timeMonth = 1;
	char timeDay = 1;
	char timeYear = 2017;
	char slash = 0x5C;
	char alarmHours = 25;
	char alarmMinutes = 61;
	temp_setup();
	int avgtemp=0;
	int avghumid=0;
	int thumid=0;
	int ttemper=0;
	int n=0;
	int dht11_dat[5];
	int dht11_in;
	int i;
	rtc2_init();

	RTC2_VALUE->seconds = 1;
	RTC2_VALUE->minutes = 31;
	RTC2_VALUE->hours = 13;
	RTC2_VALUE->date = 3;
	RTC2_VALUE->month = 31;
	RTC2_VALUE->year = 2017;
	RTC2_VALUE->format = RTC2_FORMAT_24;
	rtc2_preset(RTC2_VALUE);
	/* // code to implement knowing what day it is but when uploaded to the clock it produced errors, since it was an extra feature we cut it out of the final design
	nokia_lcd_clear();
	nokia_lcd_set_cursor(10,20);
	nokia_lcd_write_string("Please Enter",1);
	nokia_lcd_set_cursor(17,28);
	nokia_lcd_write_string("The Date.",1);
	nokia_lcd_render();
	nokia_lcd_clear();
	_delay_ms(2000);
	cursorPosition = 0;
	timeYear = 17;

	while(1){
		if(cursorPosition == 3){break;}
		if(cursorPosition == 0){ nokia_lcd_set_cursor(0,2); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(8,2); nokia_lcd_write_char(slash,2);}
		if(cursorPosition == 1){ nokia_lcd_set_cursor(32,2); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(40,2); nokia_lcd_write_char(slash,2);}
		if(cursorPosition == 2){ nokia_lcd_set_cursor(65,2); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(73,2); nokia_lcd_write_char(slash,2);}
		nokia_lcd_set_cursor(0,16);
		if(timeMonth < 10) {nokia_lcd_write_string("0",2);}
		nokia_lcd_write_string(itoa(timeMonth,buf,10), 2);
		//nokia_lcd_write_string("|",2);
		nokia_lcd_set_cursor(32,16);
		if(timeDay < 10) {nokia_lcd_write_string("0",2);}
		nokia_lcd_write_string(itoa(timeDay,buf,10), 2);
		nokia_lcd_set_cursor(63,16);
		nokia_lcd_write_string(itoa((timeYear),buf,10), 2);
		nokia_lcd_set_cursor(2,35);
		nokia_lcd_write_string("M  D  Y",2);
		nokia_lcd_render();
		if ((PIND & 0x01) && (cursorPosition == 0)){timeMonth++; _delay_ms(200);}
		else if ((PIND & 0x01) && (cursorPosition == 1)){timeDay++; _delay_ms(200);}
		else if ((PIND & 0x01) && (cursorPosition == 2)){timeYear++; _delay_ms(200);}
		if (PIND & 0x02){cursorPosition++; _delay_ms(200);}
		nokia_lcd_clear();
		if (timeDay > 31){timeDay = 1;}
		if (timeDay > 30 && (timeMonth == 4 || timeMonth == 6 || timeMonth == 8 || timeMonth == 10)){timeDay = 1;}
		if (timeDay > 28 && timeMonth == 2 && (timeMonth%4!=0)){timeDay = 1;}
		if (timeDay > 29 && timeMonth == 2 && (timeMonth%4==0)){timeDay = 1;}
		if (timeMonth > 12){timeMonth = 1;}
		if (timeYear > 30){ timeYear = 10;}
	}
	*/
	nokia_lcd_clear();
	nokia_lcd_set_cursor(10,20);
	nokia_lcd_write_string("Please Enter",1);
	nokia_lcd_set_cursor(17,28);
	nokia_lcd_write_string("The Time.",1);
	nokia_lcd_render();
	nokia_lcd_clear();
	_delay_ms(2000);
	cursorPosition = 0;
	int Alarm;
	while(1){
			if(cursorPosition == 2){break;}
			if(cursorPosition == 0){ nokia_lcd_set_cursor(12,0); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(20,0); nokia_lcd_write_char(slash,2);}
			if(cursorPosition == 1){ nokia_lcd_set_cursor(58,0); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(66,0); nokia_lcd_write_char(slash,2);}
			nokia_lcd_set_cursor(5,16);
			if(timeHours < 10) {nokia_lcd_write_string("0",3);}
			nokia_lcd_write_string(itoa(timeHours,buf,10), 3);
			nokia_lcd_write_string(":",3);
			if(timeMinutes < 10) {nokia_lcd_write_string("0",3);}
			nokia_lcd_write_string(itoa(timeMinutes,buf,10), 3);
			nokia_lcd_render();
			if ((PIND & 0x01) && (cursorPosition == 0)){timeHours++; _delay_ms(200);} // left button
			else if ((PIND & 0x01) && (cursorPosition == 1)){timeMinutes++; _delay_ms(200);}
			if (PIND & 0x02){cursorPosition++; _delay_ms(200);}   // right button
			nokia_lcd_clear();
			if (timeMinutes >= 60){timeMinutes = 0;}
			if (timeHours >= 24){timeHours = 0;}
	}

	RTC2_VALUE->seconds = 0;
	RTC2_VALUE->minutes = timeMinutes;
	RTC2_VALUE->hours = timeHours;



	RTC2_VALUE->date = timeDay;
	RTC2_VALUE->month = timeMonth;
	RTC2_VALUE->year = timeYear ;

	RTC2_VALUE->seconds = 0;
	RTC2_VALUE->minutes = timeMinutes;
	RTC2_VALUE->hours = timeHours;

	rtc2_preset(RTC2_VALUE);

	while(1){
	drawImage(img);
	rtc2_update(RTC2_VALUE);
	
	nokia_lcd_set_cursor(6, 6);
	if(RTC2_VALUE->hours < 10){nokia_lcd_write_string("0",1);}
	nokia_lcd_write_string(itoa(RTC2_VALUE->hours,buf,10),1);
	nokia_lcd_write_string(":",1);
	if(RTC2_VALUE->minutes < 10){nokia_lcd_write_string("0",1);}
	nokia_lcd_write_string(itoa(RTC2_VALUE->minutes,buf,10),1);
	nokia_lcd_write_string(":",1);
	if(RTC2_VALUE->seconds < 10){nokia_lcd_write_string("0",1);}
	nokia_lcd_write_string(itoa(RTC2_VALUE->seconds,buf,10),1);
	
	while(PIND & 0x01){
		nokia_lcd_clear();
		drawImage(img);
		PORTC &= ~_BV(DHT11_PIN);    // 1. pull-down i/o pin for 18ms
		_delay_ms(18);
		PORTC |= _BV(DHT11_PIN);     // 2. pull-up i/o pin for 40us
		_delay_us(1);
		DDRC &= ~_BV(DHT11_PIN);     //let analog port 0 be input port
		_delay_us(40);

		dht11_in = PINC & _BV(DHT11_PIN);  // read only the input port 0
		_delay_us(80);
		dht11_in = PINC & _BV(DHT11_PIN); 
		_delay_us(80);// now ready for data reception
		for (i=0; i<5; i++)
		{  dht11_dat[i] = read_dht11_dat();}  //recieved 40 bits data. Details are described in datasheet

		DDRC |= _BV(DHT11_PIN);      //let analog port 0 be output port after all the data have been received
		PORTC |= _BV(DHT11_PIN);     //let the  value of this port be '1' after all the data have been received
		int dht11_check_sum = dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3];// check check_sum
		nokia_lcd_set_cursor(9, 6);
		nokia_lcd_write_string(itoa(dht11_dat[2],buf, 10),1);
		nokia_lcd_write_string("C ",1);
		nokia_lcd_write_string(itoa(dht11_dat[0],buf, 10),1);
		nokia_lcd_write_string("%",1);
		nokia_lcd_render();
		_delay_ms(300);
		
	}
	if (PIND & 0x02){ButtonBTime++;}
	else{ButtonBTime = 0;}
	if(ButtonBTime >= 15) // this time might need to be changed
	{
			nokia_lcd_clear();
			nokia_lcd_set_cursor(10,20);
			nokia_lcd_write_string("Please Enter",1);
			nokia_lcd_set_cursor(4,28);
			nokia_lcd_write_string("Alarm Time.",1);
			nokia_lcd_render();
			nokia_lcd_clear();
			_delay_ms(2000);
			cursorPosition = 0;
			alarmHours = 0;
			alarmMinutes = 0;
		while(1){
			if(cursorPosition == 2){break;}
			if(cursorPosition == 0){ nokia_lcd_set_cursor(12,0); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(20,0); nokia_lcd_write_char(slash,2);}
			if(cursorPosition == 1){ nokia_lcd_set_cursor(58,0); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(66,0); nokia_lcd_write_char(slash,2);}
			nokia_lcd_set_cursor(5,16);
			if(alarmHours < 10) {nokia_lcd_write_string("0",3);}
			nokia_lcd_write_string(itoa(alarmHours,buf,10), 3);
			nokia_lcd_write_string(":",3);
			if(alarmMinutes < 10) {nokia_lcd_write_string("0",3);}
			nokia_lcd_write_string(itoa(alarmMinutes,buf,10), 3);
			nokia_lcd_render();
			if ((PIND & 0x01) && (cursorPosition == 0)){alarmHours++; _delay_ms(200);} // left button
			else if ((PIND & 0x01) && (cursorPosition == 1)){alarmMinutes++; _delay_ms(200);}
			if (PIND & 0x02){cursorPosition++; _delay_ms(200);}   // right button
			nokia_lcd_clear();
			if (alarmMinutes >= 60){alarmMinutes = 0;}
			if (alarmHours >= 24){alarmHours = 0;}
		}
		nokia_lcd_clear();
		nokia_lcd_set_cursor(10,20);
		nokia_lcd_write_string("Alarm Set",1);
		nokia_lcd_set_cursor(4,28);
		nokia_lcd_render();
		_delay_ms(2000);
		ButtonBTime = 0;
	}
	// this is when the alarm must go off.
	if(alarmHours == RTC2_VALUE->hours && alarmMinutes == RTC2_VALUE->minutes){
		Alarm = 0;
		PinTracker = PORTD; // I save it for later so I can keep the pins and have them go back to what they were originally. 
		_delay_ms(1000);
		PORTD ^= 0x80; 
		_delay_ms(100);
		nokia_lcd_clear();
		nokia_lcd_set_cursor(10,20);
		nokia_lcd_write_string("ITS TIME!",1);
		nokia_lcd_render();
		while(1){	
			if(Alarm == 1) {
				PORTD ^= 0x80; 
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;break;} 
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;break;}
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;break;}
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;break;}
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;break;}
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;break;}
				Alarm = 0;}
			if(Alarm == 0) {
				PORTD ^= 0x80; 
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;_delay_ms(100);break;}
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;_delay_ms(100);break;}
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;_delay_ms(100);break;}
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;_delay_ms(100);break;}
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;_delay_ms(100);break;}
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;_delay_ms(100);break;}
				Alarm = 1;
				}
			
			if (PIND & 0x01){_delay_ms(100);PORTD ^= 0x80;_delay_ms(100);break;} 
			else if (PIND & 0x02){_delay_ms(100);PORTD ^= 0x80;_delay_ms(100);break;} 
		}
		_delay_ms(100);
		alarmHours = 25;
		alarmMinutes = 61;
	}
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
int read_dht11_dat()
{
	int i = 0;
	int result=0;
	for(i=0; i< 8; i++)
	{
		while(!(PINC & _BV(DHT11_PIN)));
		_delay_us(30); // wait  forever until anlog input port 0 is '1'   (NOTICE: PINC reads all the analog input ports
		//and  _BV(X) is the macro operation which pull up positon 'X'to '1' and the rest positions to '0'. it is equivalent to 1<    delayMicroseconds(30);
		if(PINC & _BV(DHT11_PIN))  //if analog input port 0 is still '1' after 30 us
		result |=(1<<(7-i));     //this position is 1
		while((PINC & _BV(DHT11_PIN)));  // wait '1' finish
	}
	return result;
}

void temp_setup()
{
	DDRC |= _BV(DHT11_PIN);   //let analog port 0 be output port
	PORTC |= _BV(DHT11_PIN);  //let the initial value of this port be '1'
}