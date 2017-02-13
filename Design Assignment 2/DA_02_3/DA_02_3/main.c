/*
 Author : Anthony Pallone
 Sarah Harris
 CPE 301L
 Design Assignment 2_3
*/

#include <avr/io.h>
int main(void)
{
	unsigned int count = 0, otherCounter = 0, fiveCount= 0, tenCount = 0;	// set up our counters

	DDRB = 0xFF;		// set DDRB to ouput all
	PORTB = 0;			// make sure there are no outputs
	DDRC = 0x61;		// set DDRC to ouput only 0, 4, and 5
	PORTC = 0;			// make sure there are no outputs
	while(1)
	{
		TCCR0A = 0;		// set up Timer0 with prescaler = 256 and normal mode
		TCCR0B |= (1 << CS02);

		TCNT0 = 0;		// initialize counter
		while( (TIFR0 & 0x1) == 0 );	// wait until overflow flag is set
		TCCR0B = 0;		// stop/disable Timer 0
		TIFR0 |= 0x01;		// clear overflow flag
		if (count == 30)
		{
			PORTC ^= 0x01;		//toggle PORTC.0
			count = 0;			// reset counter
			if ((PORTC & 0x01) == 1)	//if PORTC.0 == 1 do the enxt codes
			{
				otherCounter++;			// increment other counter
				PORTB = otherCounter;	// output counter to PortB
				fiveCount++;			// increment 5 counter
				tenCount++;				// increment 10 counter
				if(fiveCount == 5)
				{
					fiveCount = 0;		// reset counter
					PORTC ^= 0x40;		// toggle PortC.5
				}
				if(tenCount == 10)
				{
					tenCount = 0;		// reset counter
					PORTC ^= 0x20;		// toggle PortC.4
				}
			}
		}
		else{
		count++;	// increment count
		}
	}
}
