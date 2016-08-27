#include "lcd.h"
#include "keypad.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned short count_down_flag = 0;
unsigned short PORT_NUMBER = 0;
unsigned short pin = 0;

volatile unsigned short hours = 0;
volatile unsigned short miniutes = 0;
volatile unsigned short seconds = 0;


volatile unsigned short alarm_set = 0;
volatile unsigned short pin_set = 0;

unsigned short alarm_snooze = 0;
volatile unsigned short FLAG = 0;
volatile unsigned short FLAG_ALARM = 0;
volatile unsigned short alarm_hours = 100;
volatile unsigned short alarm_minutes = 100;
volatile unsigned short alarm_seconds = 100;



void snooze()
{
	alarm_snooze = 1;
}

void alarm_status()
{
	char buffer[40];
	if(!alarm_set)
	{
		pos_lcd(1,0);
		strcpy(buffer,"Alarm Not Set");
		puts_lcd2(buffer);
	}
	
	else
	{
		pos_lcd(1,0);
		sprintf(buffer, "Alarm: %02d:%02d:%02d", alarm_hours, alarm_minutes, alarm_seconds);	
		puts_lcd2(buffer);
	}
}

void clock_status()
{
	pos_lcd(0,0);
	char clock[40];
	sprintf(clock, "Time: %02d:%02d:%02d", hours, miniutes, seconds);
	puts_lcd2(clock);
}


void led_display()
{
	
	if(seconds > 0 && seconds <= 9 )
	{
		SET_BIT(PORTA,0);
	}
	
	else if(seconds == 0)
	{
		CLR_BIT(PORTA,0);
		CLR_BIT(PORTA,1);
	}
	
	else
	{
		SET_BIT(PORTA,0);
		SET_BIT(PORTA,1);

	}
	
	if(miniutes > 0 && miniutes <= 9 )
	{
		SET_BIT(PORTA,2);
	}
	else if(miniutes == 0)
	{
		CLR_BIT(PORTA,2);
		CLR_BIT(PORTA,3);
	}		
	else
	{
		SET_BIT(PORTA,2);
		SET_BIT(PORTA,3);
		
	}

	if(hours > 0 && hours <= 9 )
	{
		SET_BIT(PORTA,4);
	}

	else if(hours == 0)
	{
		CLR_BIT(PORTA,4);
		CLR_BIT(PORTA,5);
	}
	
	else
	{
		SET_BIT(PORTA,4);
		SET_BIT(PORTA,5);
	}

}

void blink_led()
{
	PORTA = 0x00;
	wait_avr(250);
	PORTA = 0xff;
	wait_avr(250);	
	PORTA = 0x00;	
}


void check_alarm()
{
	if((hours == alarm_hours) && (miniutes == alarm_minutes) & (seconds == alarm_seconds))
	{
		FLAG_ALARM = 1;
	}
}

void alarm()
{
	while(alarm_snooze == 0)
	{
		play_music(song1,SIZE);
	}
			
	alarm_snooze = 0;
}



void
time()
{
	
	if(seconds == 60)
	{
		if((seconds == 60)&&(miniutes == 59))
		{			
			seconds = 0;
			miniutes = 0;
			hours++;
		}
				
		else
		{
			seconds = 0;
			miniutes++;				
		}				
	}
			
	if(hours > 23)
	{
		seconds = 0;
		miniutes = 0;
		hours = 0;		
	}
	
	
	if(!FLAG)
	{	
		alarm_status();
	}
	
	clock_status();
	check_alarm();
	led_display();
	seconds++;
}


int
checkTime(int hour, int minutes, int seconds)
{
	if(hour > 24)
	{
		clr_lcd();
		pos_lcd(1,0);
		char msg[40];
		strcpy(msg, "Invalid Hours");
		puts_lcd2(msg);
		
		wait_avr(1000);
		
		return 0;
	}
	
	else if(minutes > 59)
	{
		clr_lcd();
		pos_lcd(1,0);
		char msg[40];
		strcpy(msg, "Invalid Minutes");
		puts_lcd2(msg);
		
		wait_avr(1000);
		
		return 0;
	}
	
	else if(seconds > 59)
	{

		clr_lcd();
		pos_lcd(1,0);
		char msg[40];
		strcpy(msg, "Invalid Seconds");
		puts_lcd2(msg);
				
		wait_avr(1000);
		
		return 0;
	}
	
	else
	{
		return 1;
	}
}

char
setClock()
{
	PORTA = 0x00;
	
	cli();

	char buffer[16];
	pos_lcd(0, 0);
	sprintf(buffer, "Time: %2s:%2s:%2s", "HH", "MM", "SS");
	puts_lcd2(buffer);
	pos_lcd(0, 0);
	alarm_status();

	pos_lcd(0,6);
	
	char newTime[10];
	
	volatile int counter = 0;
	
	volatile int CURRENT_PORT = 5;
	volatile char c;
	while(c != '#')
	{
		c = get_value(get_key());
		
		if( c >= '0' && c <= '9' )
		{
			if(counter > 5)
			{
				break;
			}
				
			if(counter == 2)
			{
				
				put_lcd(':');
			}
			
			if(counter == 4)
			{
				put_lcd(':');
			}
			
		
			put_lcd(c);
			newTime[counter++] = c;
			
			SET_BIT(PORTA,CURRENT_PORT--);
		
		}
		
		wait_avr(250);
	}
	
	newTime[counter] = 0;
	
	if(counter < 5)
	{
		sei();
		clr_lcd();
		pos_lcd(0,0);
		strcpy(buffer,"Clock Invalid");
		puts_lcd2(buffer);
		wait_avr(1000);
		PORTA = 0x00;
		return c;
	}

	char newHour[8];
	char newMin[8];
	char newSec[8];
	
	newHour[0] = newTime[0];
	newHour[1] = newTime[1];
	newHour[2] = 0;
	
	newMin[0] = newTime[2];
	newMin[1] = newTime[3];
	newMin[2] = 0;
	
	newSec[0] = newTime[4];
	newSec[1] = newTime[5];
	newSec[2] = 0;
	
	int h = atoi(newHour);
	int m = atoi(newMin);
	int s = atoi(newSec);
	
	
	if(checkTime(h,m,s))
	{
		hours = h;
		miniutes = m;
		seconds = s;
	}
	
	PORTA = 0x00;
	sei();
	return c;
}

int auth()
{
	if(pin_set)
	{
		int entered_pin = getPin();
		if(entered_pin > -1)
		{
			if(pin == entered_pin)
			{
				return 1;
			}
			
			else
			{
				clr_lcd();
					
				char buffer[18];
				pos_lcd(0, 0);
				clock_status();
					
				pos_lcd(1,0);
				strcpy(buffer,"Incorrect Pin");
				puts_lcd2(buffer);
				wait_avr(1500);
				
				return 0;
			}
		}
		
	}
	
	return 1;
}

char
setAlarm()
{	
	clr_lcd();
	
	char buffer[18];
	pos_lcd(0, 0);
	clock_status();
	
	pos_lcd(1, 0);
	sprintf(buffer, "Alarm: %2s:%2s:%2s", "HH", "MM", "SS");
	puts_lcd2(buffer);

	char newTime[10];
	
	int counter = 0;
	int pos = 0;
	
	int CURRENT_PORT = 5;
	
	char c;
	while(c != '#')
	{	
		c = get_value(get_key());		
		pos_lcd(1,7 + pos);
		
		if( c >= '0' && c <= '9' )
		{
			if(counter > 5)
			{
				break;
			}
			
			if(counter == 2)
			{
				
				put_lcd(':');
				pos++;
			}
			
			if(counter == 4)
			{
				put_lcd(':');
				pos++;
			}
			
			
			put_lcd(c);
			newTime[counter++] = c;
			pos++;
		
			SET_BIT(PORTA,CURRENT_PORT--);
			
		}
		
		wait_avr(250);
	}
	
	newTime[counter] = 0;

	if(counter < 5)
	{
		clr_lcd();
		pos_lcd(1,0);
		strcpy(buffer,"Alarm Invalid");
		puts_lcd2(buffer);
		wait_avr(1500);
		
	
		
		PORTA = 0x00;
	}

	else 
	{
		char newHour[8];
		char newMin[8];
		char newSec[8];
		
		newHour[0] = newTime[0];
		newHour[1] = newTime[1];
		newHour[2] = 0;
		
		newMin[0] = newTime[2];
		newMin[1] = newTime[3];
		newMin[2] = 0;
		
		newSec[0] = newTime[4];
		newSec[1] = newTime[5];
		newSec[2] = 0;
		
		int h = atoi(newHour);
		int m = atoi(newMin);
		int s = atoi(newSec);
		
		
		if(checkTime(h,m,s))
		{
			alarm_hours = h;
			alarm_minutes = m;
			alarm_seconds = s;
			
			alarm_set = 1;
		}
		
		PORTA = 0x00;
	}
	
	return c;
}

int
getPin()
{
	clr_lcd();
	char buffer[18];
	pos_lcd(0, 0);
	clock_status();
	
	pos_lcd(1, 0);
	sprintf(buffer, "Pin: %4s", "####");
	puts_lcd2(buffer);

	char newPin[10];
	
	int p = -1;
	int counter = 0;
	int CURRENT_PORT = 3;
	char c;
	while(c != '*')
	{
		c = get_value(get_key());
		pos_lcd(1,5 + counter);
		
		if( c >= '0' && c <= '9' )
		{
			if(counter > 3)
			{
				break;
			}
			
			put_lcd(c);
			newPin[counter++] = c;
			
			SET_BIT(PORTA,CURRENT_PORT--);		
		}
		wait_avr(250);
	}

	if(counter < 3)
	{
		pos_lcd(1,0);
		strcpy(buffer,"Pin is Invalid");
		puts_lcd2(buffer);
		wait_avr(1000);
		
	}
	
	else
	{
		newPin[counter] = 0;
		p = atoi(newPin);
	}

	PORTA = 0x00;
	
	return p;
}


void setPin()
{
	int newPin = getPin();
	
	if(newPin > -1)
	{
		pin = newPin;
		pin_set = 1;
	}
}