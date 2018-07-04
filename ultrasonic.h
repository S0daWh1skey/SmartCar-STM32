#ifndef _ULTR_H_
#define _ULTR_H_
#include <reg51.h>
sbit ECHO=P2^0;
sbit TRIG=P2^1;
#endif

void StarModle(void);
void distance(void);
void Timer_Count(void);
unsigned long csbdistance(void);
