// GY-26 IIC测试程序
// 使用单片机STC89C51 
// 晶振：11.0592M
// 显示：LCD1602
// 编译环境 Keil uVision2
// 程序中把模块当24c04进行通信
// temp_data
#include  <REG51.H>	
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
#include  "signal.h"
#include  "delay.h"
#include  "display.h"
#include "GY-26.h"
#include "bst_car.h"
#include "Infrared.h"
#include  "ultrasonic.h"
#include "beep.h"	
#define   uchar unsigned char
#define   uint unsigned int	
#define   DataPort P0	//LCD1602数据端口
#define	ReadDviceAddress     0xE1     //器件在IIC总线中地址+1
extern BYTE BUF[8];                         //数据缓存区
BYTE code res[6] _at_ 0x23;
sbit    LCM_RS=P1^0;   //LCD1602命令端口		
sbit    LCM_RW=P1^1;   //LCD1602命令端口		
sbit    LCM_EN=P2^5;   //LCD1602命令端口         
/*
sbit    KEY_1 =P3^4;   //按键1
sbit    KEY_2 =P3^5;   //按键2
sbit    KEY_3 =P3^6;   //按键3
sbit    KEY_4 =P3^7;   //按键4		
*/
uchar templ,temph,cnt;
uchar ge,shi,bai,qian;
uint  dis_data,dis_data1;

void delay(unsigned int k);
void InitLcd();
void WriteDataLCM(uchar dataW);
void WriteCommandLCM(uchar CMD,uchar Attribc);
void DisplayOneChar(uchar X,uchar Y,uchar DData);
uchar HEX_TO_ASCII(uchar HEX_data);
void conversion(uint temp_data);

//------------------------------------

void Delay5us();
void Delay5ms();
void AT24C04_Start();
void AT24C04_Stop();
void AT24C04_SendACK(bit ack);
bit  AT24C04_RecvACK();
void AT24C04_SendByte(BYTE dat);
BYTE AT24C04_RecvByte();
void AT24C04_ReadPage();
void AT24C04_WritePage();
void read_cmp(void);
//-----------------------------------
void cal_on();
void cal_off();
void recovery_factory();
void CMP_OFFS();
void IIC_ADDR_Change();
void delay_10ms();


//*********************************************************
uchar HEX_TO_ASCII(uchar HEX_data)
{uchar ASCII_data;
	switch(HEX_data){       
	   case 0x00:ASCII_data=0x30;break;
	   case 0x01:ASCII_data=0x31;break;
       case 0x02:ASCII_data=0x32;break;
       case 0x03:ASCII_data=0x33;break;
	   case 0x04:ASCII_data=0x34;break;
	   case 0x05:ASCII_data=0x35;break;
       case 0x06:ASCII_data=0x36;break;
	   case 0x07:ASCII_data=0x37;break;
	   case 0x08:ASCII_data=0x38;break;
	   case 0x09:ASCII_data=0x39;break;
	   case 0x0a:ASCII_data=0x41;break;
	   case 0x0b:ASCII_data=0x42;break;
	   case 0x0c:ASCII_data=0x43;break;
       case 0x0d:ASCII_data=0x44;break;
	   case 0x0e:ASCII_data=0x45;break;
	   case 0x0f:ASCII_data=0x46;break;
    } 
    return(ASCII_data);  
}
//*********************************************************
void conversion(uint temp_data)  
{   
    uchar ge_data,shi_data,bai_data ,qian_data;
	qian_data=temp_data/1000 ;
    temp_data=temp_data%1000;   //取余运算
    bai_data=temp_data/100 ;
    temp_data=temp_data%100;   //取余运算
    shi_data=temp_data/10 ;
    temp_data=temp_data%10;   //取余运算
    ge_data=temp_data;
    qian= qian_data;
    bai = bai_data;
    shi = shi_data;
    ge  = ge_data ; 	
//	a=temp_data;
}

//*********************************************************
void main()
{
//	uint temp_data;
  unsigned int i;
  unsigned long s;
   delay(500);			
   InitLcd();
   	//EA=0;
   	cnt=0;
//	unsigned int valA;
	TMOD=0X01;
    TH0= 0XFC;  //1ms定时
    TL0= 0X66;
    TR0= 1;
    ET0= 1;
	EA = 1;	    //开总中断


  while(1)            //循环
  { 
		
	//delay(5000);
    read_cmp();   //读出数据
//---------显示角度
    dis_data=0;
    dis_data=BUF[1];
    dis_data<<=8;
    dis_data|=BUF[2];

    conversion(dis_data);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);

    DisplayOneChar(0,0,qian); 
    DisplayOneChar(1,0,bai); 
    DisplayOneChar(2,0,shi); 
    DisplayOneChar(3,0,'.'); 
	DisplayOneChar(4,0,ge); 
	
	//Infrared();
    s = csbdistance();
	if(s<40)
	{
		beep_start();
        delay(60);
        beep_Stop();
        stop();
        delay(500);
        back();
        delay(400);
        rightrun();
        delay(500);
    }
	else{
	if(Left_2_led==1&&Right_2_led==1)
	{
		/*if(dis_data>=800&&dis_data<=1200)    
			run();
		*/
		if(dis_data>1800)
		   leftrun();
		if(dis_data<1800)
		   rightrun();
	}
	if(Left_2_led==1&&Right_2_led==0){
//        stop();
//        delay(100);
//        back();
//        delay(100);
		leftrun();
		delay(500);
}
	if(Right_2_led==1&&Left_2_led==0){
//        stop();
//        delay(100);
//        back();
//        delay(100);
	    rightrun();
		delay(1000);
}
    if(Right_2_led==0&&Left_2_led==0){
        stop();
        delay(500);
        back();
        delay(500);
	    rightrun();
		delay(1000);
}
}
//---------显示温度
    dis_data=0;
    dis_data=BUF[5];
    dis_data<<=8;
    dis_data|=BUF[6];
    
	if(dis_data>4095){           //如果bit-12为1，即符号位为负
	DisplayOneChar(0,1,'-');     //显示负号
	dis_data&=0xefff;            //清符号位
	}
    else DisplayOneChar(0,1,' ');//如果bit-12为0,空格,清空

    conversion(dis_data);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);

    DisplayOneChar(1,1,qian); 
    DisplayOneChar(2,1,bai); 
    DisplayOneChar(3,1,shi); 
    DisplayOneChar(4,1,'.'); 
	DisplayOneChar(5,1,ge); 
	DisplayOneChar(6,1,0XDF);    //温度单位
	DisplayOneChar(7,1,'C'); //温度单位

//-------显示磁偏量
	dis_data1=0;
    dis_data1=BUF[3];
    dis_data1<<=8;
    dis_data1|=BUF[4];

    conversion(dis_data1);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);

    DisplayOneChar(7,0,qian); 
    DisplayOneChar(8,0,bai); 
    DisplayOneChar(9,0,shi); 
    DisplayOneChar(10,0,'.'); 
	DisplayOneChar(11,0,ge); 

//-------显示校准等级
    conversion(BUF[7]);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);
    DisplayOneChar(10,1,bai); 
    DisplayOneChar(11,1,shi); 
	DisplayOneChar(12,1,ge); 
/*	
//----------按键检测

    if(KEY_1==0){
	    delay_10ms();
	    if(KEY_1==0){
 	    cal_on(); 
   	    while(KEY_1==0)delay_10ms();
	    }
    }	  
    if(KEY_2==0){
	  delay_10ms();
	  if(KEY_2==0){
	  cal_off();  
      while(KEY_2==0)delay_10ms();
	  }
	}
    if(KEY_3==0){
	  delay_10ms();
	  if(KEY_3==0){
	  recovery_factory();  
      while(KEY_3==0)delay_10ms();
	  }
	}
    if(KEY_4==0){
     delay_10ms();
 	 if(KEY_4==0){
	// CMP_OFFS();  
	 IIC_ADDR_Change();
     while(KEY_4==0)delay_10ms();
     }
    }
*/
    for (i=0;i<4000;i++);               
  }
    	
} 


/*******************************/
void delay(unsigned int k);
/*******************************/
void WaitForEnable(void);					
/*******************************/
void WriteCommandLCM(uchar CMD,uchar Attribc);					
/*******************************/
void WriteDataLCM(uchar dataW);	
/***********************************/
void InitLcd();			
/***********************************/
void DisplayOneChar(uchar X,uchar Y,uchar DData);						
/***********************************/
//*********************************************************
void read_cmp(void);
//--------------------------------------------------

/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us();

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms();

/**************************************
起始信号
**************************************/
void AT24C04_Start();

/**************************************
停止信号
**************************************/
void AT24C04_Stop();

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void AT24C04_SendACK(bit ack);

/**************************************
接收应答信号
**************************************/
bit AT24C04_RecvACK();

/**************************************
向IIC总线发送一个字节数据
**************************************/
void AT24C04_SendByte(BYTE dat);

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE AT24C04_RecvByte();

//*********************************************************
void cal_on(void);

//*********************************************************
void cal_off(void) ;                           //关闭校准

//*********************************************************
void recovery_factory(void);                   //恢复出厂设置

//*********************************************************
void IIC_ADDR_Change(void);                   //iic地址更改

//*********************************************************
void CMP_OFFS(void);                         //磁偏角

//*********************************************************
void Delay_10ms(void);
//参考宏晶网站24c04通信程序