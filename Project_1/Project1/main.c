/*
 * Project1.c
 *
 * Created: 4/11/2016 7:07:36 PM
 * Author : egflo
 */ 

#include <avr/io.h>
#include "avr.c"

void wait()
{
	volatile int n = 32700;
	for(int i=0; i< n; i++)
	{
		/* Do Nothing */
	}
}

int main(void)
{
	DDRB |= 1 << PINB0; // Set for output for pinb 0 by setting a bit
	DDRB &= ~(1 << PINB1); //Set for input for pinb 1 by clearing a bit

	while (1)
	{
		//return non-zero if the bit is clear, and 0 if the bit is set.
		if (bit_is_clear(PINB, 1))
		{	
			PORTB |= 1 << PINB0;
			//wait(); 
			wait_avr(500);
			
        	PORTB &= ~(1 << PINB0);
			//wait();
			wait_avr(500);


		}

	}
}