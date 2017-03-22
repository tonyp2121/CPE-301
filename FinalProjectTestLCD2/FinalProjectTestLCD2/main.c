/*
 * FinalProjectTestLCD2.c
 *
 * Created: 3/22/2017 2:10:24 PM
 * Author : Tony
 */ 

#include <avr/io.h>
#include "Drivers/nokia5110.h"
//#include "Drivers/nokia5110_chars.h"

int main(void)
{
    /* Replace with your application code */
	nokia_lcd_init();
	nokia_lcd_power(1);
	nokia_lcd_write_string("hello world", 3);
}

