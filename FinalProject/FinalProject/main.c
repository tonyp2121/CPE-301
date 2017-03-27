/*
 * FinalProjectTestLCD2.c
 *
 * Created: 3/22/2017 2:10:24 PM
 * Author : Tony
 */ 

#define F_CPU 8000000	// Clock Speed
#include <util/delay.h>
#include <avr/io.h>
#include "Drivers/nokia5110.h"



int main(void)
{
	nokia_lcd_init();
	nokia_lcd_clear();
	nokia_lcd_write_string("testing testing testing testing does it go over huh or does it automatically curve around.",1);
	nokia_lcd_render();

	for (;;) {
		_delay_ms(1000);
	}
}
