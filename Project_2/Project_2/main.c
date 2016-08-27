/*
 * Project_2.c
 *
 * Created: 4/14/2016 8:02:28 PM
 * Author : egflo
 */ 

#include <avr/io.h>
#include "lcd.c"
#include "lcd.h"
#include "avr.c"
#include "avr.h"
#include "keypad.h"
#include "keypad.c"
#include "time.h"
#include "time.c"
#include <string.h>

int main(void)
{
    /* Replace with your application code */
	int sec = 0;
	int min = 0;
	int hour = 0;
	
	int month = 1;
	int day = 1;
	int year = 2009;
	
	ini_lcd();
	clr_lcd();
	
	while (1)					/* loop forever */
	{
		
		unsigned char key = get_key();
		
		if(key < 0xff)
		{
			char c = 'N';
			do 
			{
				unsigned char key = get_key();
								
				if(key < 0xff)
				{
					c = get_value(key);
					
					if(c == 'A')
					{
						c = setDate(&month,&day,&year);
						
					}
					
					else if(c == 'B')
					{
						c = setClock(&hour,&min,&sec);
					}
					
					wait_avr(400);
				}
			
				
			} while (c != 'C');
			
			
		}
		
		time(&hour, &min, &sec, &month, &day, &year);
		wait_avr(1000);
	}
}

