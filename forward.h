//��������С������ģ������IO��
sbit IN1=P1^2; // �ߵ�ƽ1 ���ˣ���ת��
sbit IN2=P1^3; // �ߵ�ƽ1 ǰ������ת��

sbit IN3=P1^6; // �ߵ�ƽ1 ǰ������ת��	
sbit IN4=P1^7; // �ߵ�ƽ1 ���ˣ���ת��

sbit EN1=P1^4; // �ߵ�ƽʹ�� 
sbit EN2=P1^5; // �ߵ�ƽʹ�� 

void run(void);
void left(void);
void right(void);

unsigned char pwm_val_left  =0;//��������
unsigned char pwm_val_right =0;
unsigned char push_val_left =9;// ����ռ�ձ�N/20 //�ٶȵ��ڱ��� 0-20������0��С��20���
unsigned char push_val_right=9;// �ҵ��ռ�ձ�N/20
bit Right_PWM_ON=1;	           //�ҵ��PWM����
bit Left_PWM_ON =1;			   //����PWM����

