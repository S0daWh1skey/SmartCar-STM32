#include "GY-26.h"
void cal_on(void)
{                                             //У׼
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC0);                   //����У׼����
    AT24C04_Stop();                           //����ֹͣ�ź�
}
//*********************************************************
void cal_off(void)                            //�ر�У׼
{
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC1);                   //����ֹͣУ׼����
    AT24C04_Stop();                           //����ֹͣ�ź�
}
//*********************************************************
void recovery_factory(void)                   //�ָ���������
{
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xA0);                   //��������0xA0
    AT24C04_Stop();                           //����ֹͣ�ź�

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xAA);                   //��������0xAA
    AT24C04_Stop();                           //����ֹͣ�ź�

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xA5);                   //��������0xA5
    AT24C04_Stop();                           //����ֹͣ�ź�

	AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC5);                   //����0xC5,�ָ���������
    AT24C04_Stop();                           //����ֹͣ�ź�

}
//*********************************************************
void IIC_ADDR_Change(void)                   //iic��ַ����
{
    AT24C04_Start();                         //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);    //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                  //0��ʾ���� 
    AT24C04_SendByte(0xA0);                  //��������0xA0
    AT24C04_Stop();                          //����ֹͣ�ź�

    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                 //0��ʾ���� 
    AT24C04_SendByte(0xAA);                 //��������0xAA
    AT24C04_Stop();                         //����ֹͣ�ź�

    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                 //0��ʾ���� 
    AT24C04_SendByte(0xA5);                 //��������0xA5
    AT24C04_Stop();                         //����ֹͣ�ź�

	AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                 //0��ʾ���� 
    AT24C04_SendByte(0xE8);                 //�µ�IIC��ַE0-FE��ż��(�ο�PDF�ĵ�)
    AT24C04_Stop();                         //����ֹͣ�ź�

}
//*********************************************************
void CMP_OFFS(void)                         //��ƫ��
{
    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x03);                 //0��ʾ���� 
    AT24C04_SendByte(0x00);                 //��ƫ�Ǹ�8λ��д��0
    AT24C04_Stop();                         //����ֹͣ�ź�

    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x04);                 //0��ʾ���� 
    AT24C04_SendByte(0x64);                 //��ƫ�ǵ�8λ��д��100��ʵ����10.0�ȣ�
    AT24C04_Stop();                         //����ֹͣ�ź�
}
//*********************************************************


