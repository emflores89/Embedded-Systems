/*
 * Project_5.c
 *
 * Created: 5/28/2016 6:14:30 PM
 * Author : egflo
 */ 

#include <avr/io.h>
#include "lcd.c"
#include "lcd.h"
#include <string.h>
#include "keypad.h"
#include "keypad.c"
#include "avr.h"
#include "avr.c"
#include <string.h>
#include <stdio.h>
#include "music.h"
#include "music.c"
#include "time.h"
#include "time.c"
#include "avr/interrupt.h"

int main(void)
{
    /* Replace with your application code */
	DDRA =  0xFF;
	
    ini_lcd();
	clr_lcd();
	
	sei();
	
	TCCR1B |= 1<<CS10 | 1<<CS12 | 1<<WGM12;
	TIMSK |= 1<<OCIE1A;
	OCR1A = 7812;
	
	while (1) 
    {
		
		char c = get_value(get_key());
		
		if(c == 'A')
		{
			FLAG = 1;
			if(auth())
			{
				setClock();
			}
			FLAG = 0;
		
		}
		if(c == 'B')
		{
			FLAG = 1;
			if(auth())
			{
				setAlarm();				
			}
			FLAG = 0;
		}
		if(c == 'C')
		{
			FLAG = 1;
			if(auth())
			{
				setPin();						
			}
			FLAG = 0;

		}
		
		if(FLAG_ALARM)
		{
			alarm();
			FLAG_ALARM = 0;
		}

		//time();
		//wait_avr(1000);
    }
}

ISR(TIMER1_COMPA_vect)
{
	time();
}