#include "Infrared.h"
#include "bst_car.h"
void Infrared(void)
{	
   
	    //���ź�Ϊ0  û���ź�Ϊ1
        if(Left_2_led==1&&Right_2_led==1)
	    run();   //����ǰ������		  
		if(Left_2_led==1&&Right_2_led==0)	    //�ұ߼�⵽�ϰ���
		{
			leftrun();		       //����С����ת����
		}			   
		if(Right_2_led==1&&Left_2_led==0)		//��߼�⵽�ϰ���
		{	  
			rightrun();		   //����С����ת����
		}
			 
	 
}
   



