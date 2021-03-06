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
	char PinTracker; // used later on to keep track of pins so we dont turn anything on or off
	nokia_lcd_init(); // start up the lcd
	nokia_lcd_clear(); // clear the lcd
	DDRD |= 0b10000011; // set the DDRD so the pins can be used for the buzzer and the 
	char buf[10] = {0}; // buffer for writing characters to for itoa.
	char ButtonBTime = 0; // how long button B was held down
	char cursorPosition = 0; // where the user is when inputting code
	char timeMinutes = 0; // used for when the user inputs it in the next section
	char timeHours = 0;   
	char timeMonth = 1;   // the month, year, and day arent being used but need to be put in the clock for writing to it.
	char timeDay = 1;
	char timeYear = 2017;
	char slash = 0x5C;   // this is here because I couldnt type / in text without it thinking I was talking about something 
						 // else and saying I was missing something so here it is in the hex code
	char alarmHours = 25; // it has to be at an area that is unreachable because its not initially set
	char alarmMinutes = 61;
	temp_setup(); // set up the temperature sensor
	int avgtemp=0; // keep these variables for comparison lator
	int avghumid=0;
	int thumid=0;
	int ttemper=0;
	int n=0;
	int dht11_dat[5]; // where the data is stored from reading from the sensor
	int dht11_in;
	int i;
	rtc2_init();

	RTC2_VALUE->format = RTC2_FORMAT_24; // prompt the user to input the time.
	rtc2_preset(RTC2_VALUE);
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
			if(cursorPosition == 2){break;} // when the user is in position 2 that means that theyve entered both the hours and minutes and we can leave this otherwise infinite loop
			if(cursorPosition == 0){ nokia_lcd_set_cursor(12,0); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(20,0); nokia_lcd_write_char(slash,2);} // this is where I use slash
			if(cursorPosition == 1){ nokia_lcd_set_cursor(58,0); nokia_lcd_write_string("/",2);  nokia_lcd_set_cursor(66,0); nokia_lcd_write_char(slash,2);}
			nokia_lcd_set_cursor(5,16);
			if(timeHours < 10) {nokia_lcd_write_string("0",3);} // if its less than 10 we want a 0 to be in front of it like 08:04.
			nokia_lcd_write_string(itoa(timeHours,buf,10), 3);
			nokia_lcd_write_string(":",3);
			if(timeMinutes < 10) {nokia_lcd_write_string("0",3);} // same for minutes
			nokia_lcd_write_string(itoa(timeMinutes,buf,10), 3);
			nokia_lcd_render();
			if ((PIND & 0x01) && (cursorPosition == 0)){timeHours++; _delay_ms(200);} // if they hit the left button
			else if ((PIND & 0x01) && (cursorPosition == 1)){timeMinutes++; _delay_ms(200);}
			if (PIND & 0x02){cursorPosition++; _delay_ms(200);}   // if they hit the right button
			nokia_lcd_clear();
			if (timeMinutes >= 60){timeMinutes = 0;} // then reset it in in case its ever above 60 or 24
			if (timeHours >= 24){timeHours = 0;}
	}

	RTC2_VALUE->seconds = 0; // we set seconds at 0 then set the minutes as the user entered minutes and hours
	RTC2_VALUE->minutes = timeMinutes;
	RTC2_VALUE->hours = timeHours; 
	RTC2_VALUE->date = timeDay;
	RTC2_VALUE->month = timeMonth;
	RTC2_VALUE->year = timeYear ;

	rtc2_preset(RTC2_VALUE); // then we write to the clock sensor so it uses what we give them from now on

	while(1){
	drawImage(img); // this calls the draw image function to set the image
	rtc2_update(RTC2_VALUE); // update the time from the clock.
	
	nokia_lcd_set_cursor(6, 6);
	if(RTC2_VALUE->hours < 10){nokia_lcd_write_string("0",1);} // if the time is below 10 we want to add a 0 before it so everything fits nice and flush
	nokia_lcd_write_string(itoa(RTC2_VALUE->hours,buf,10),1);  // write the time to the LCD
	nokia_lcd_write_string(":",1);
	if(RTC2_VALUE->minutes < 10){nokia_lcd_write_string("0",1);}
	nokia_lcd_write_string(itoa(RTC2_VALUE->minutes,buf,10),1);
	nokia_lcd_write_string(":",1);
	if(RTC2_VALUE->seconds < 10){nokia_lcd_write_string("0",1);}
	nokia_lcd_write_string(itoa(RTC2_VALUE->seconds,buf,10),1);
	
	// this is for checking the temperature from the sensor
	
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
	
	if(PIND & 0x01){ // if someone is holding down button 1 show the temperature instead of time.
		nokia_lcd_clear();
		drawImage(img);
		
		nokia_lcd_set_cursor(9, 6);
		nokia_lcd_write_string(itoa(dht11_dat[2],buf, 10),1);
		nokia_lcd_write_string("C ",1);
		nokia_lcd_write_string(itoa(dht11_dat[0],buf, 10),1);
		nokia_lcd_write_string("%",1);
		nokia_lcd_render();
		_delay_ms(300);
		
	}
	if (PIND & 0x02){ButtonBTime++;} // if someones holding down the right button add to the counter otherwise set it to 0
	else{ButtonBTime = 0;}
	if(ButtonBTime >= 15) // if its been held for 15 consecutive cycles have the user input the time
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
			alarmHours = 0;	// set alarm time to be 0 so it starts over
			alarmMinutes = 0; 
		while(1){
			if(cursorPosition == 2){break;} // exact same setup as entering the time just with the Alarm Instead
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
		nokia_lcd_write_string("Alarm Set",1); // then we tell the user the alarm is set and exit
		nokia_lcd_render();
		_delay_ms(2000);
		ButtonBTime = 0;
	}
	// this is when the alarm must go off.
	if(alarmHours == RTC2_VALUE->hours && alarmMinutes == RTC2_VALUE->minutes){ // if its time for the alarm to go off we enter this if statement
		
		PinTracker = PORTD; // I save it for later so I can keep the pins and have them go back to what they were originally. 
		_delay_ms(1000);
		PORTD ^= 0x80; 
		_delay_ms(100);
		nokia_lcd_clear();
		nokia_lcd_set_cursor(10,20);
		nokia_lcd_write_string("ITS TIME!",1);
		nokia_lcd_render();
		while(1){	
				PORTD ^= 0x80;  // this turns the alarm on and off forever until a button is pressed.
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;break;} 
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;break;}
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;break;}
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;break;}
				_delay_ms(100);
				if (PIND & 0x01){_delay_ms(100);PORTD = PinTracker;break;}
				else if (PIND & 0x02){_delay_ms(100);PORTD = PinTracker;break;}
				Alarm = 0;
				}
		
		_delay_ms(100);
		alarmHours = 25; // then we say the alarm is done and it will not go off again until it is set again by the user.
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
	while(y != 48){ // these numbers are limited here because it is a 48 x 84 lcd screen
		while(i <= 79){
			if(img[counter] & 0x80){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(img[counter] & 0x40){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(img[counter] & 0x20){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
			if(img[counter] & 0x10){nokia_lcd_set_pixel(i, y, 1); i++;}
			else {i++;}
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
		
		i = 0;
		y++; // now we move onto the next row

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