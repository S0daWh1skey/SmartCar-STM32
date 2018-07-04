#include "display.h"
#include "signal.h"
unsigned char BUF[8]; 
void WaitForEnable(void)	
{					
DataPort=0xff;		
LCM_RS=0;LCM_RW=1;_nop_();
LCM_EN=1;_nop_();_nop_();
while(DataPort&0x80);	
LCM_EN=0;				
}					
/*******************************/
void WriteCommandLCM(uchar CMD,uchar Attribc)
{					
if(Attribc)WaitForEnable();	
LCM_RS=0;LCM_RW=0;_nop_();
DataPort=CMD;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}					
/*******************************/
void WriteDataLCM(uchar dataW)
{					
WaitForEnable();		
LCM_RS=1;LCM_RW=0;_nop_();
DataPort=dataW;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}		
/***********************************/
void InitLcd()				
{			
WriteCommandLCM(0x38,1);	
WriteCommandLCM(0x08,1);	
WriteCommandLCM(0x01,1);	
WriteCommandLCM(0x06,1);	
WriteCommandLCM(0x0c,1);
}			
/***********************************/
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
Y&=1;						
X&=15;						
if(Y)X|=0x40;					
X|=0x80;			
WriteCommandLCM(X,0);		
WriteDataLCM(DData);		
}						
/***********************************/

//*********************************************************
void read_cmp(void)
{   uchar i;

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0x31);                   //����һ�β����Ƕ�
    AT24C04_Stop();                           //ֹͣ�ź�

	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();                               //��ʱ��ʵ��Ӧ���п���ִ����������
	Delay5ms();
	Delay5ms();
	Delay5ms();


    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0x35);                   //����һ�β����¶�
    AT24C04_Stop();                           //ֹͣ�ź�

    Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();                               //��ʱ��ʵ��Ӧ���п���ִ����������

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress+1);   //�����豸��ַ+���ź�
	 for (i=0; i<8; i++)
    {
        BUF[i] = AT24C04_RecvByte();
        if (i == 7)
        {
           AT24C04_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          AT24C04_SendACK(0);                //��ӦACK
       }
   }
    AT24C04_Stop();                          //ֹͣ�ź�

}
