/*
 Author : Anthony Pallone
 Sarah Harris
 CPE 301L
 Design Assignment 2_3
*/

#include <avr/io.h>


int main(void)
{
	unsigned int count = 0, otherCounter = 0, fiveCount= 0, tenCount = 0;

	DDRB = 0xFF;
	PORTB = 0;
	DDRC = 0x61;
	PORTC = 0;
	while(1)
	{
		TCCR0A = 0;
		TCCR0B |= (1 << CS02);

		TCNT0 = 0;
		while( (TIFR0 & 0x1) == 0 );
		TCCR0B = 0;
		TIFR0 |= 0x01;
		if (count == 30)
		{
			PORTC ^= 0x01;
			count = 0;
			if ((PORTC & 0x01) == 0)
			{
				otherCounter++;
				PORTB = otherCounter;
				fiveCount++;
				tenCount++;
				if(fiveCount == 5)
				{
					fiveCount = 0;
					PORTC ^= 0x20;
				}
				if(tenCount == 10)
				{
					tenCount = 0;
					PORTC ^= 0x20;
				}
			}
		}
		else{
		count++;
		}
	}
}
