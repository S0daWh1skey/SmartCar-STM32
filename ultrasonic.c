#include "ultrasonic.h"
#include "delay.h"
unsigned int time=0;
unsigned long S=0;
unsigned int valA;
void StarModle(void)
{
TRIG=1;
delay(1);
TRIG=0;
}
void distance(void)
{
time=TH1*256+TL1;
TH1=0;
TL1=0; 
S=(time*0.17)/10+10;
}

void Timer_Count(void)
{
while(!ECHO);
TR1=1;
while(ECHO);
TR1=0;
distance();

}
unsigned long csbdistance(void)
{
ECHO=1;
StarModle();
for(valA=7510;valA>0;valA--)
{
if(ECHO==1)
{
Timer_Count();
return S;
}
}
}


