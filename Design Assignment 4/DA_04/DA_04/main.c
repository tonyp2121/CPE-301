/*
	
 */ 

#include <avr/io.h>


int main(void)
{
	/*
		Pseudocode Steps:
		Initialize Registers we use (DDRD, DDRB for output And DDRD for input)
		
		
	*/
	DDRB = 0xFF;		// make Port B an output
	DDRD = 0xFF;		// make Port D an output
	DDRC = 0x0;			// make Port C an input (for ADC input)
	DIDR0 = 0x1;		// disable digital input on ADC0 pin
	ADMUX = 0x0;		// Reference = Aref, ADC0 (PC.0) used as analog input
						// data is right-justified
	ADCSRA = 0x87;		// enable ADC, system clock used for A/D conversion
	ADCSRB = 0x0;		// free running mode
	while (1) {
		ADCSRA |= (1 << ADSC);				// start conversion
		while ( (ADCSRA&(1<<ADIF)) == 0 ) ; // wait for conversion to finish
		PORTD = ADCL;						// send low byte to PORTD
		PORTB = ADCH;						// send high byte to PORTB
	}
	return 0;
}

