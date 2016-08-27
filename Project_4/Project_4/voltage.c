#include "voltage.h"
#include <limits.h>

unsigned short int maximum = 0;
unsigned short int minimum = SHRT_MAX;
unsigned short int average = 0;
unsigned short int sample = 0;
unsigned short int number_of_samples = 0;
unsigned long total = 0;

void ini_adc()
{
	SET_BIT(ADMUX,REFS0);
}

void take_sample()
{
	SET_BIT(ADCSRA,7);
	SET_BIT(ADCSRA,6);

	while(!GET_BIT(ADCSRA,ADIF));
	
	sample = ADC;
	
	total+=sample;	
	
	if(sample > maximum)
	{
		maximum = sample;
	}
	
	if(sample < minimum)
	{
		
		minimum = sample;
	}
	
	number_of_samples++;
	average=total/number_of_samples;
	
	CLR_BIT(ADCSRA,ADIF);
}

float convert_float(unsigned short value)
{
	return (value/1023.0) * 5.0;
}


unsigned short front(float value)
{
	return (unsigned short) value;
}

unsigned short back(float value, unsigned short front)
{
	return (unsigned short) ((value - front)*100);
}
