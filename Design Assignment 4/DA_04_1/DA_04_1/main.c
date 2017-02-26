/*
	
 */ 

#include <avr/io.h>


int main(void)
{
	/*
		Pseudocode Steps:
		Initialize Registers we use (DDRD, DDRB for output And DDRD for input)
		
		
	*/
	float view = 0;
	DDRB = 0xFF;		// make Port B an output
	DDRD = 0xFF;		// make Port D an output
	DDRC = 0x0;			// make Port C an input (for ADC input)
	DIDR0 = 0x1;		// disable digital input on ADC0 pin
	ADMUX = 0x0;		// Reference = Aref, ADC0 (PC.0) used as analog input
						// data is right-justified
	ADCSRA = 0x87;		// enable ADC, system clock used for A/D conversion
	ADCSRB = 0x0;		// free running mode
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00) ; // non inverse phase correct PWM mode
	TCCR0B = (1 << CS00) ;  // no prescaler
	while (1) {
		ADCSRA |= (1 << ADSC);				// start conversion
		while ( (ADCSRA&(1<<ADIF)) == 0 ) ; // wait for conversion to finish
		if (ADC >= 512) //forward
		{
			view = ADC/512*255;
			PORTB = 0x02;
			OCR0A = 255-ADC/4;
			
		}
		else //backward
		{
			view = (ADC+512)/512*255;
			PORTB = 0x01;
			OCR0A = 255-ADC/4;
		}
	} 
	return 0;
}

