#ifndef __time__
#define __time__

typedef int bool;
#define true 1
#define false 0

extern volatile unsigned short hours;
extern volatile unsigned short miniutes;
extern volatile unsigned short seconds;

extern unsigned short alarm_snooze;

extern volatile unsigned short alarm_set;
extern volatile unsigned short FLAG;
extern volatile unsigned short FLAG_ALARM;
extern volatile unsigned short alarm_hours;
extern volatile unsigned short alarm_minutes;
extern volatile unsigned short alarm_seconds;

char 
setClock();

char
setAlarm();

void 
setPin();

void
check_alarm();

void
clock_status();

void
alarm_status();

void
time();

void
alarm();

void
snooze();

void
blink_led();

int
auth();

int
getPin();

#endif