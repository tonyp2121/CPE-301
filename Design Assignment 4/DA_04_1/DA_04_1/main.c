/*
	
 */ 

#include <avr/io.h>
#define F_CPU 8000000L


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
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
	TCCR1B = _BV(WGM13) | _BV(WGM12)| _BV(CS11);
	ICR1 = (F_CPU/8)/50 -1;
	while (1) {
		ADCSRA |= (1 << ADSC);				// start conversion
		while ( (ADCSRA&(1<<ADIF)) == 0 ) ; // wait for conversion to finish
		view = ADC/4;
		if (ADC >= 512) //forward
		{
			PORTB = 0x20;
			OCR0A = view;
			
		}
		else //backward
		{
			view = (ADC+512)/512*255;
			PORTB = 0x10;
			OCR0A = 255 - view;
		}
		OCR1B = (ADC) * 1400/1024 + 800; 
	} 
	return 0;
}

