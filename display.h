#ifndef __BSTCAR__
#define __BSTCAR__
#include  <INTRINS.H>
#include  "signal.h"
#include  "delay.h"
#define   DataPort P0	//LCD1602���ݶ˿�
#define   uchar unsigned char
typedef unsigned char BYTE;
//unsigned char BUF[8];                         //���ݻ�����
sbit    LCM_RS=P1^0;   //LCD1602����˿�		
sbit    LCM_RW=P1^1;   //LCD1602����˿�
sbit    LCM_EN=P2^5;   //LCD1602����˿�  	
void WaitForEnable(void);
#define	WriteDeviceAddress   0xE0	  //����������IIC�����еĵ�ַ
void WriteCommandLCM(uchar CMD,uchar Attribc);
void WriteDataLCM(uchar dataW);
void InitLcd();	
void DisplayOneChar(uchar X,uchar Y,uchar DData);
void read_cmp(void);
void AT24C04_Start();
void AT24C04_Stop();
void AT24C04_SendACK(bit ack);
bit AT24C04_RecvACK();
void AT24C04_SendByte(unsigned char dat);
BYTE AT24C04_RecvByte();
#endif
