#include  <REG51.H>	
//循迹LED指示灯定义
//sbit Left_1_led=P3^3;	 //左循迹红外传感器       
//sbit Right_1_led=P3^2;	 //右循迹红外传感器  

//避障LED指示灯定义  
sbit Left_2_led= P3^4;	 //左避障红外传感器  
sbit Right_2_led=P3^5;	 //右避障红外传感器  

void Infrared(void);
