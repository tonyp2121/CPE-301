// -------------------------------------------------------------------
// CpE 301
// Spring 2017
// S. Harris
// DA6_UARTexample.c
// -------------------------------------------------------------------
// CpE 301
// Spring 2017
// S. Harris
// DA6_UARTexample.c
// -------------------------------------------------------------------
//
// This code repeatedly writes the alphabet to the serial terminal
//
// --------------------------------------------------------------------

#include <avr/io.h>
#define F_CPU 8000000	// Clock Speed
#include <util/delay.h>

#define BAUD  9600

void initUART();
void writeChar(unsigned char c);
void writeInt(unsigned int i);
void writeString(char str[]); 

int main( void )
{
	//unsigned char ch = 'A';
	unsigned int test = 1;
	float test2;
	DDRC = 0x0; // make Port C an input (for ADC input)
	DIDR0 = 0x1;
	ADMUX = 0x0;
	ADCSRA = 0x87;		// enable ADC, system clock used for A/D conversion
	ADCSRB = 0x0;		// free running mode

	initUART();
	while (1) {
		ADCSRA |= (1 << ADSC);				// start conversion
		while ( (ADCSRA&(1<<ADIF)) == 0 ) ;
		test2 = ADC/1024.0;
		test2 = test2 * 5;
		test = test2;
	
		
		writeInt(test);
		//writeChar(' ');
		writeChar('V');
		writeChar(' ');
		}

	return 0;
}

void initUART() {
	unsigned int baudrate;

	// Set baud rate:  UBRR = [F_CPU/(16*BAUD)] -1
	baudrate = ((F_CPU/16)/BAUD) - 1;
	UBRR0H = (unsigned char) (baudrate >> 8);
	UBRR0L = (unsigned char) baudrate;

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);		// Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);		// Set data frame: 8 data bits, 1 stop bit, no parity
}

void writeChar(unsigned char c) {
	UDR0 = c;									// Display character on serial (i.e., PuTTY) terminal
	_delay_ms(200);
}

void writeInt(unsigned int i) {
	UDR0 = i + 0x30;									// Display character on serial (i.e., PuTTY) terminal
	_delay_ms(200);
}

void writeString(char str[]) {
	int i = 0;
	while (str[i] =! '\0'){
	writeChar(str[i]);	
	i++;
	}							// Display character on serial (i.e., PuTTY) terminal
	//_delay_ms(200);
}