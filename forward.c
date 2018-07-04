#include<reg51.h>
#include "bst_car.h"

unsigned char pwm_val_left  =0;//变量定义
unsigned char pwm_val_right =0;
unsigned char push_val_left =7;// 左电机占空比N/20 //速度调节变量 0-20。。。0最小，20最大
unsigned char push_val_right=7;// 右电机占空比N/20
bit Right_PWM_ON=1;	           //右电机PWM开关
bit Left_PWM_ON =1;			   //左电机PWM开关

//前进
 void run(void)
{
    //push_val_left=5;	 //速度调节变量 0-20。。。0最小，20最大
	//push_val_right=5;
	Left_moto_go ;   //左电机往前走
	Right_moto_go ;  //右电机往前走
}

void stop()//停止
{
   Right_moto_Stop;
   Left_moto_Stop;
}

void back()
{
    Left_moto_back;
    Right_moto_back;
}


//左转
 void leftrun(void)
{	 
     //push_val_left=5;
	 //push_val_right=5;
   Right_PWM_ON=1;
    Left_PWM_ON=0;
	 Right_moto_go ; //右电机往前走
     Left_moto_Stop ; 
 //左电机停止
}

//右转
void  rightrun(void)
{ 
	 //push_val_left=5;
	 //push_val_right=5;
Left_PWM_ON=1;
Right_PWM_ON=0 ;
     Left_moto_go  ;   //左电机往前走
	 Right_moto_Stop 
  //右电机往前走	
}
/************************************************************************/
//                   PWM调制电机转速                                   

//                   左电机调速                                        
/*调节push_val_left的值改变电机转速,占空比*/
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
          EN1=0;   //若未开启PWM则EN1=0 左电机 停止
     }
}
/******************************************************************/
/*                    右电机调速                                  */  
void pwm_out_right_moto(void)
{ 
    if(Right_PWM_ON)
    { 
        if(pwm_val_right<=push_val_right)	//20ms内电平信号 111 111 0000 0000 0000 00
	    {
	        EN2=1; 							//占空比6:20
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
        EN2=0;	  //若未开启PWM则EN2=0 右电机 停止
    }
}

//TIMER0中断服务子函数产生PWM信号
void timer0()interrupt 1 using 2
{
     TH0=0XFC;	  //1Ms定时
	 TL0=0X66;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

