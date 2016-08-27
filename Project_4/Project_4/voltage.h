#ifndef __voltage__
#define __voltage__



extern unsigned short minimum;
extern unsigned short maximum;
extern unsigned short average;
extern unsigned long total;
extern unsigned short sample;
extern unsigned short number_of_samples;


void ini_adc();
void take_sample();
float convert_float(unsigned short value);
unsigned short front(float value);
unsigned short back(float value, unsigned short front);

#endif