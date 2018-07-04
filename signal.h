#ifndef __BSTCAR__
#define __BSTCAR__
#include  <REG51.H>
#include "delay.h"
typedef unsigned char BYTE;
#define	WriteDeviceAddress   0xE0	  //定义器件在IIC总线中的地址
sbit	SCL=P2^6;      //iic时钟引脚定义
sbit	SDA=P2^7;      //iic数据引脚定义
void AT24C04_Start();
void AT24C04_Stop();
void AT24C04_SendACK(bit ack);
bit AT24C04_RecvACK();
void AT24C04_SendByte(unsigned char dat);
BYTE AT24C04_RecvByte();
#endif
