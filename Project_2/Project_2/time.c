#include "lcd.h"
#include "keypad.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char
setDate(int *month, int *day, int *year)
{
	char buffer[16];
	pos_lcd(0,0);
	sprintf(buffer, "%2s/%2s/%4s", "MM", "DD", "YYYY");
	puts_lcd2(buffer);
	
	
	pos_lcd(0,0);
	
	char c;
	
	char newMonth[16];
	char newDay[16];
	char newYear[16];
	
	int counter = 0;

	while (c != 'C')
	{
		c = get_value(get_key());	
			
		if(c >= '0' && c <= '9')
		{
					
			if((counter == 2 )|| (counter == 5))
			{
				put_lcd('/');
			}
			
			else if(counter > 9)
			{
				c = 'C';
			}
			
			else if(counter < 2)
			{
				put_lcd(c);
				int i = strlen(newMonth);
				newMonth[i] = c;			
			}
			
			else if(counter > 2 && counter < 5)
			{
				put_lcd(c);
				int i = strlen(newDay);
				newDay[i] = c;
						
			}
			
			else 
			{
				put_lcd(c);
				int i = strlen(newYear);
				newYear[i] = c;

			}
			
			counter++;
			wait_avr(400);	
		
		}
	}
	
	int m = atoi(newMonth);
	int d = atoi(newDay);
	int y = atoi(newYear);
		
	if(m != 0 && d != 0 && y != 0)
	{
	
		*month = m;
		*day = d;
		*year = y;
	}

	
	return c;
}

	
char 
setClock(int *hour, int *min, int *sec)
{		
	char buffer[16];
	pos_lcd(1, 0);
	sprintf(buffer, "%2s:%2s:%2s", "HH", "MM", "SS");
	puts_lcd2(buffer);	
	

	pos_lcd(1,0);
	
	char newHour[8];
	char newMin[8];
	char newSec[8];
	
	char c;
	int counter = 0;
	do
	{
		c = get_value(get_key());
		
		if(c >= '0' && c <= '9')
		{
			
			if((counter == 2 )|| (counter == 5))
			{
				put_lcd(':');
			}
			
			else if(counter > 7)
			{
				return 'C';
			}
			
			else if(counter < 2)
			{
				put_lcd(c);
				
				int i = strlen(newHour);
				newHour[i] = c;
				
			}
			
			else if(counter > 2 && counter < 5)
			{
				put_lcd(c);
				int i = strlen(newMin);
				newMin[i] = c;
			}
			
			else
			{
				put_lcd(c);

				int i = strlen(newSec);
				newSec[i] = c;
			}
			
			
			counter++;
			wait_avr(400);
		}
		
	} while (c != 'C');
	
	

	int h = atoi(newHour);
	int m = atoi(newMin);
	int s = atoi(newSec);
	
	*hour = h;
	*min = m;
	*sec = s;

	
	return c;
}


void
time(int *hour, int *min, int *sec, int *month, int *day, int *year)
{
	int DATE[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	if(*sec == 60)
	{
		if((*sec == 60)&& (*min == 59))
		{			
			*sec = 0;
			*min = 0;
			(*hour)++;
		}
				
		else
		{
			*sec = 0;
			(*min)++;				
		}				
	}
			
	if(*hour > 23)
	{
		*sec = 0;
		*min = 0;
		*hour = 0;
		(*day)++;			
	}
			
			
	if(*day > DATE[*month-1])
	{
			(*month)++;
			
			if(*month == 2 && *year%400 == 0 && *year%4 == 0 && *year%100)
			{
				(*day)++;
			}
	}
			
	if(*month > 12)
	{
		(*year)++;
		*month  = 1;
		*day = 1;
	}
		
	clr_lcd();
		
	pos_lcd(0,0);
	char date[40];
	sprintf(date, "%02d/%02d/%04d", *month, *day, *year);
	puts_lcd2(date);
	
	pos_lcd(1,0);
	char clock[40];
	sprintf(clock, "%02d:%02d:%02d", *hour, *min, *sec);
	puts_lcd2(clock);
	
	(*sec)++;
}