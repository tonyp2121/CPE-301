/*
 Author : Anthony Pallone
 Sarah Harris
 CPE 301L
 Design Assignment 2_4
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int count = 0, otherCounter = 0, fiveCount= 0, tenCount = 0;

ISR (TIMER0_OVF_vect) {
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


int main(void)
{
	DDRB = 0xFF;
	PORTB = 0;
	DDRC = 0x61;
	PORTC = 0;
	TCCR0A = 0;
	TCCR0B |= (1 << CS02);
	TCNT0 = 0;
	TIMSK0 |= (1 << TOIE0);

	sei();

	while(1);
}
