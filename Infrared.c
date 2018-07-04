#include "Infrared.h"
#include "bst_car.h"
void Infrared(void)
{	
   
	    //有信号为0  没有信号为1
        if(Left_2_led==1&&Right_2_led==1)
	    run();   //调用前进函数		  
		if(Left_2_led==1&&Right_2_led==0)	    //右边检测到障碍物
		{
			leftrun();		       //调用小车左转函数
		}			   
		if(Right_2_led==1&&Left_2_led==0)		//左边检测到障碍物
		{	  
			rightrun();		   //调用小车右转函数
		}
			 
	 
}
   



