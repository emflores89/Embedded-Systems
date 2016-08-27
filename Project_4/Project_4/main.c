/*
 * Project_4.c
 *
 * Created: 5/22/2016 10:04:52 AM
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
#include "voltage.h"
#include "voltage.c"
#include <string.h>
#include <stdio.h>

int main(void)
{
    /* Replace with your application code */
	ini_lcd();
	ini_adc();
	
	char buffer1[50];
	char buffer2[50];
	
	pos_lcd(0,0);
	strcpy(buffer1, "A:Start Sample");
	puts_lcd2(buffer1);
			
	pos_lcd(1,0);
	strcpy(buffer2,"B:Reset Sample");
	puts_lcd2(buffer2);
			
	
    while (1) 
    {
		char key = get_value(get_key());
		
		if(key == 'A')
		{						
			while(key != 'B')
			{
				key =  get_value(get_key());
				clr_lcd();
				take_sample();
			
				float sample_float  = convert_float(sample);
				float minimum_float = convert_float(minimum);
				float maximum_float = convert_float(maximum);
				float average_float = convert_float(average);
			
				unsigned short front_sample = front(sample_float);
				unsigned short back_sample = back(sample_float,front_sample);

				unsigned short front_min = front(minimum_float);
				unsigned short back_min = back(minimum_float,front_min);

				unsigned short front_max = front(maximum_float);
				unsigned short back_max = back(maximum_float,front_max);			

				unsigned short front_avg = front(average_float);
				unsigned short back_avg = back(average_float,front_avg);
						
				pos_lcd(0,0);
				sprintf(buffer1,"CV:%01d.%02d AV:%01d.%02d",front_sample,back_sample,front_avg,back_avg);
				//sprintf(buffer1,"CV:%01.02f AV:%01.02f",sample_float,average_float);
				puts_lcd2(buffer1);
			
				pos_lcd(1, 0);
				sprintf(buffer2,"MN:%01d.%02d MX:%01d.%02d",front_min,back_min,front_max,back_max);
				//sprintf(buffer2,"MN:%01.02f MX:%01.02f",minimum_float,maximum_float);
				puts_lcd2(buffer2);
			
				wait_avr(500);
		
			}
			
			
		}
		
		if (key == 'B')
		{
			maximum = 0;
			minimum = SHRT_MAX;
			average = 0;
			number_of_samples = 0;
			sample = 0;
			total = 0;
			
			clr_lcd();
			
			pos_lcd(0,0);
			sprintf(buffer1,"CV:%01d.%02d AV:%01d.%02d",0,0,0,0);
			puts_lcd2(buffer1);
			
			pos_lcd(1, 0);
			sprintf(buffer2,"MN:%01d.%02d MX:%01d.%02d",0,0,0,0);
			puts_lcd2(buffer2);
			
		}
				
		
    }
}

