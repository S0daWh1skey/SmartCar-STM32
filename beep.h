#ifndef _BEEP_H_
#define _BEEP_
#include<reg51.h>
sbit FM=P2^3;
#endif 

void beep_start();
void beep_Stop();
