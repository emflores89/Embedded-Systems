#include "avr.h"


char get_value(unsigned char key)
{
	if(key < 0xff)
	{
		const char keypad[16] = {
			'1','2','3','A',
			'4','5','6','B',
			'7','8','9','C',
			'*','0','#','D'};
	
		int index = (int) key;
	
		return keypad[index];		
	}
	
	else
	{
		return 0xff;
	}
}


unsigned char get_key()
{
	unsigned char r,c;
	
	for(r = 0; r < 4; r++)
	{
		for(c=0; c < 4; ++c)
		{
			
			if(pressed(r,c))
			{
				
				return r * 4 + c;
			}
		}
		
	}	
	
	return  0xff;
}

unsigned char pressed(unsigned r, unsigned c)
{
	DDRC = 0x0f;
	PORTC = 0xff;
	
	CLR_BIT(PORTC,r);
	
	wait_avr(1);
	
	if(!GET_BIT(PINC,c+4))
	{
		
		return 1;
	}
	
	return 0;
	
}