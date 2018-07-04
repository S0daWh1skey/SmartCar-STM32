#ifndef __BSTCAR_H__
#define __BSTCAR_H__
/************BST-V51����С��ͷ�ļ�*************/

//����С������ģ������IO�� 
sbit IN1=P1^2;
sbit IN2=P1^3;
sbit IN3=P1^6;
sbit IN4=P1^7;
sbit EN1=P1^4;
sbit EN2=P1^5;


//ѭ��LEDָʾ�ƶ���
//sbit Left_1_led=P3^3;	 //��ѭ�����⴫����       
//sbit Right_1_led=P3^2;	 //��ѭ�����⴫����  

//����LEDָʾ�ƶ���  
//sbit Left_2_led=P3^4;	 //����Ϻ��⴫����  
//sbit Right_2_led=P3^5;	 //�ұ��Ϻ��⴫����  


#define Left_moto_go      {IN1=0,IN2=1;}   //������ǰ��
#define Left_moto_back    {IN1=1,IN2=0;}   //��ߵ�����ת
#define Left_moto_Stop    {EN1=0;}         //��ߵ��ͣת                     
#define Right_moto_go     {IN3=1,IN4=0;}   //�ұߵ����ǰ��
#define Right_moto_back   {IN3=0,IN4=1;}   //�ұߵ�������
#define Right_moto_Stop   {EN2=0;}	       //�ұߵ��ͣת  

void  rightrun(void);
void  leftrun(void);
void  run(void);
void  back(void);
void  stop(void);
void pwm_out_right_moto(void);
void pwm_out_left_moto(void);

#endif