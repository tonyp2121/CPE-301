/*
 Author : Anthony Pallone
 Sarah Harris
 CPE 301L
 Design Assignment 2_3
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000L
#include <util/delay.h>


volatile int red = 0, blue = 0, green = 0, caseNumber = 0;

int main(void)
{
	DDRB = 0x01;	// sets OC2A
	DDRD = 0x60;	// sets OC0A & OC0B
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00) ; // non inverse phase correct PWM mode
	TCCR0B = (1 << CS00) ;  // no prescaler
	TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20); // non inverse phase correct PWM mode
	TCCR2B =  (1 << CS20) ; // no prescalar
	
while(1)
{
	//OCR0A = red
	//OCR2A = green
	//OCR0B = blue
	if(caseNumber == 0){ // red #FF0000
		red = 0xFF;
		green = 0x00;
		blue = 0x00;
		caseNumber++;
		_delay_ms(500);
	}
	else if (caseNumber == 1){ // blue #0000FF
		red = 0x00;
		green = 0x00;
		blue = 0xFF;
		caseNumber++;
		_delay_ms(500);
	}	
	else if (caseNumber == 2){ // green # 00FF00
		red = 0x00;
		green = 0xFF;
		blue = 0x00;
		caseNumber++;
		_delay_ms(500);
	}
	else if (caseNumber == 3){ // yellow #FFFF00
		red = 0xFF;
		green = 0xFF;
		blue = 0x00;
		caseNumber++;
		_delay_ms(500);
	}
	else if (caseNumber == 4){ // orange #580500
		red = 0x58;
		green  = 0x05;
		blue = 0x00;
		caseNumber++;
		_delay_ms(500);
	}
	else if (caseNumber == 5){ // purple #AD00C4
		red = 0xAD;
		green = 0x00;
		blue = 0xC4;
		caseNumber++;
		_delay_ms(500);
	}
	else if (caseNumber == 6){ // turquoise #00E5EE
		red = 0x00;
		green = 0xE5;
		blue = 0xEE;
		caseNumber++;
		_delay_ms(500);
	}
	else if (caseNumber == 7){ // white #FFFFFF
		red = 0xFF;
		green = 0xFF;
		blue = 0xFF;
		caseNumber++;
		_delay_ms(500);
	}
	else if (caseNumber == 8){ // black #000000
		red = 0x00;
		green = 0x00;
		blue = 0x00;
		caseNumber= 0;
		_delay_ms(500);
	}
	
	OCR0A = red;
	OCR2A = green;
	OCR0B = blue;
}

}