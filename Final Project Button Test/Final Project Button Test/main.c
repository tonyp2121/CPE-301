/*/*
 * DA5_1.c
 *
 * Created: 2/27/2017 2:06:19 PM
 * Author : pallone
 */

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	char test = 0;
	char test2 = 0;
	//DDRD |= (1<<PD3); //Nakes first pin of PORTC as Output
	// OR DDRC = 0x01;
	DDRD = 0b00001100;
	// OR DDRD = 0x00; //Makes all pins of PORTD input
	while(1) //infinite loop
	{
		test = PIND;
		test2 = (test << 2);
		//test2 = test;
		PORTD = test2;
		_delay_ms(100);
		test = 0;
	}
}