/*
 Author : Anthony Pallone
 Sarah Harris
 CPE 301L
 Design Assignment 2_4
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int count = 0, otherCounter = 0, fiveCount= 0, tenCount = 0;  // implement counters

ISR (TIMER0_OVF_vect) {
	if (count == 30)           // when count == 30 do the next code
	{
	  	PORTC ^= 0x01;      // toggle PC.0
		count = 0;          // reset counter
		if ((PORTC & 0x01) == 1)// if PC.0 == 1 do next code
		{
			otherCounter++;      // increment counter
			PORTB = otherCounter;    // set portB to be the other Counter
			fiveCount++;         // increment five counter
			tenCount++;          // increment ten counter
			if(fiveCount == 5)
			{
				fiveCount = 0;      // reset five counter
				PORTC ^= 0x40;      // toggle PC.5
			}
			if(tenCount == 10)
			{
				tenCount = 0;       //reset ten counter
				PORTC ^= 0x20;      // toggle PC.4
			}
		}
	}
	else{
		count++;          // else increment count until it gets to 30
	}
}


int main(void)
{
	DDRB = 0xFF;       // set DDRB for all ouputs
	PORTB = 0;         // make sure theres nothing coming out of PortB
	DDRC = 0x61;       // set DDRB to only output at 4,5, and 0 pins
	PORTC = 0;         // make sure theres nothing coming out of PortC
	TCCR0A = 0;        // initialize clock, normal
	TCCR0B |= (1 << CS02);  // clock/256
	TCNT0 = 0;         // initialize counter
	TIMSK0 |= (1 << TOIE0);

	sei();             // enable global interrupts

	while(1);          // infinite loop
}
