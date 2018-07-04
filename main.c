// GY-26 IIC���Գ���
// ʹ�õ�Ƭ��STC89C51 
// ����11.0592M
// ��ʾ��LCD1602
// ���뻷�� Keil uVision2
// �����а�ģ�鵱24c04����ͨ��
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
#define   DataPort P0	//LCD1602���ݶ˿�
#define	ReadDviceAddress     0xE1     //������IIC�����е�ַ+1
extern BYTE BUF[8];                         //���ݻ�����
BYTE code res[6] _at_ 0x23;
sbit    LCM_RS=P1^0;   //LCD1602����˿�		
sbit    LCM_RW=P1^1;   //LCD1602����˿�		
sbit    LCM_EN=P2^5;   //LCD1602����˿�         
/*
sbit    KEY_1 =P3^4;   //����1
sbit    KEY_2 =P3^5;   //����2
sbit    KEY_3 =P3^6;   //����3
sbit    KEY_4 =P3^7;   //����4		
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
    temp_data=temp_data%1000;   //ȡ������
    bai_data=temp_data/100 ;
    temp_data=temp_data%100;   //ȡ������
    shi_data=temp_data/10 ;
    temp_data=temp_data%10;   //ȡ������
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
    TH0= 0XFC;  //1ms��ʱ
    TL0= 0X66;
    TR0= 1;
    ET0= 1;
	EA = 1;	    //�����ж�


  while(1)            //ѭ��
  { 
		
	//delay(5000);
    read_cmp();   //��������
//---------��ʾ�Ƕ�
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
//---------��ʾ�¶�
    dis_data=0;
    dis_data=BUF[5];
    dis_data<<=8;
    dis_data|=BUF[6];
    
	if(dis_data>4095){           //���bit-12Ϊ1��������λΪ��
	DisplayOneChar(0,1,'-');     //��ʾ����
	dis_data&=0xefff;            //�����λ
	}
    else DisplayOneChar(0,1,' ');//���bit-12Ϊ0,�ո�,���

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
	DisplayOneChar(6,1,0XDF);    //�¶ȵ�λ
	DisplayOneChar(7,1,'C'); //�¶ȵ�λ

//-------��ʾ��ƫ��
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

//-------��ʾУ׼�ȼ�
    conversion(BUF[7]);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);
    DisplayOneChar(10,1,bai); 
    DisplayOneChar(11,1,shi); 
	DisplayOneChar(12,1,ge); 
/*	
//----------�������

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
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5us();

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5ms();

/**************************************
��ʼ�ź�
**************************************/
void AT24C04_Start();

/**************************************
ֹͣ�ź�
**************************************/
void AT24C04_Stop();

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void AT24C04_SendACK(bit ack);

/**************************************
����Ӧ���ź�
**************************************/
bit AT24C04_RecvACK();

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void AT24C04_SendByte(BYTE dat);

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE AT24C04_RecvByte();

//*********************************************************
void cal_on(void);

//*********************************************************
void cal_off(void) ;                           //�ر�У׼

//*********************************************************
void recovery_factory(void);                   //�ָ���������

//*********************************************************
void IIC_ADDR_Change(void);                   //iic��ַ����

//*********************************************************
void CMP_OFFS(void);                         //��ƫ��

//*********************************************************
void Delay_10ms(void);
//�ο��꾧��վ24c04ͨ�ų���