#ifndef __music__
#define __music__


#define XTAL_FRQ 8000000lu
#define SIZE 12
#define SIZE2 44

#define convert(freq) (((1/freq)/2)* 100000)

typedef struct {
	unsigned short freq;
	unsigned short duration;
} Note;

extern Note song1[SIZE];
extern Note song2[SIZE2];

void delay_us(unsigned short count);
void play_note(unsigned short freq, unsigned short duration);
void play_music(Note song[], int length);


#endif