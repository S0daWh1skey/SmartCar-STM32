#include<reg51.h>
#include "bst_car.h"

unsigned char pwm_val_left  =0;//��������
unsigned char pwm_val_right =0;
unsigned char push_val_left =7;// ����ռ�ձ�N/20 //�ٶȵ��ڱ��� 0-20������0��С��20���
unsigned char push_val_right=7;// �ҵ��ռ�ձ�N/20
bit Right_PWM_ON=1;	           //�ҵ��PWM����
bit Left_PWM_ON =1;			   //����PWM����

//ǰ��
 void run(void)
{
    //push_val_left=5;	 //�ٶȵ��ڱ��� 0-20������0��С��20���
	//push_val_right=5;
	Left_moto_go ;   //������ǰ��
	Right_moto_go ;  //�ҵ����ǰ��
}

void stop()//ֹͣ
{
   Right_moto_Stop;
   Left_moto_Stop;
}

void back()
{
    Left_moto_back;
    Right_moto_back;
}


//��ת
 void leftrun(void)
{	 
     //push_val_left=5;
	 //push_val_right=5;
   Right_PWM_ON=1;
    Left_PWM_ON=0;
	 Right_moto_go ; //�ҵ����ǰ��
     Left_moto_Stop ; 
 //����ֹͣ
}

//��ת
void  rightrun(void)
{ 
	 //push_val_left=5;
	 //push_val_right=5;
Left_PWM_ON=1;
Right_PWM_ON=0 ;
     Left_moto_go  ;   //������ǰ��
	 Right_moto_Stop 
  //�ҵ����ǰ��	
}
/************************************************************************/
//                   PWM���Ƶ��ת��                                   

//                   ��������                                        
/*����push_val_left��ֵ�ı���ת��,ռ�ձ�*/
void pwm_out_left_moto(void)
{  
     if(Left_PWM_ON)	
     {
          if(pwm_val_left<=push_val_left)
	      {
	           EN1=1; 
	      }
	      else 
	      {
	           EN1=0;
          }
          if(pwm_val_left>=20)
	      pwm_val_left=0;
     }
     else    
     {
          EN1=0;   //��δ����PWM��EN1=0 ���� ֹͣ
     }
}
/******************************************************************/
/*                    �ҵ������                                  */  
void pwm_out_right_moto(void)
{ 
    if(Right_PWM_ON)
    { 
        if(pwm_val_right<=push_val_right)	//20ms�ڵ�ƽ�ź� 111 111 0000 0000 0000 00
	    {
	        EN2=1; 							//ռ�ձ�6:20
        }
	    else 
	    {
	        EN2=0;
        }
	    if(pwm_val_right>=20)
	    pwm_val_right=0;
    }
    else    
    {
        EN2=0;	  //��δ����PWM��EN2=0 �ҵ�� ֹͣ
    }
}

//TIMER0�жϷ����Ӻ�������PWM�ź�
void timer0()interrupt 1 using 2
{
     TH0=0XFC;	  //1Ms��ʱ
	 TL0=0X66;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

