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
	//DDRD |= (1<<PD3); //Nakes first pin of PORTC as Output
	// OR DDRC = 0x01;
	DDRD |= 0b00001111;
	// OR DDRD = 0x00; //Makes all pins of PORTD input
	while(1) //infinite loop
	{	
		if ((PIND && 0x0F) > 0){
			if (PIND & 0x01){PORTD = 0x04;}
			else if (PIND & 0x02){PORTD = 0x08;}
			//PORTD = (PIND << 2);}
			else{PORTD = 0x00;}
		}
	}
}
		