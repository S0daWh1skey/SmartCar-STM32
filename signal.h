#ifndef __BSTCAR__
#define __BSTCAR__
#include  <REG51.H>
#include "delay.h"
typedef unsigned char BYTE;
#define	WriteDeviceAddress   0xE0	  //����������IIC�����еĵ�ַ
sbit	SCL=P2^6;      //iicʱ�����Ŷ���
sbit	SDA=P2^7;      //iic�������Ŷ���
void AT24C04_Start();
void AT24C04_Stop();
void AT24C04_SendACK(bit ack);
bit AT24C04_RecvACK();
void AT24C04_SendByte(unsigned char dat);
BYTE AT24C04_RecvByte();
#endif
