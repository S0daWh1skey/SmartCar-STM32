#include "GY-26.h"
void cal_on(void)
{                                             //校准
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC0);                   //发送校准命令
    AT24C04_Stop();                           //发送停止信号
}
//*********************************************************
void cal_off(void)                            //关闭校准
{
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC1);                   //发送停止校准命令
    AT24C04_Stop();                           //发送停止信号
}
//*********************************************************
void recovery_factory(void)                   //恢复出厂设置
{
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xA0);                   //发送数据0xA0
    AT24C04_Stop();                           //发送停止信号

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xAA);                   //发送数据0xAA
    AT24C04_Stop();                           //发送停止信号

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xA5);                   //发送数据0xA5
    AT24C04_Stop();                           //发送停止信号

	AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC5);                   //发送0xC5,恢复出厂命令
    AT24C04_Stop();                           //发送停止信号

}
//*********************************************************
void IIC_ADDR_Change(void)                   //iic地址更改
{
    AT24C04_Start();                         //起始信号
    AT24C04_SendByte(WriteDeviceAddress);    //发送设备地址+写信号
    AT24C04_SendByte(0x00);                  //0表示命令 
    AT24C04_SendByte(0xA0);                  //发送数据0xA0
    AT24C04_Stop();                          //发送停止信号

    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x00);                 //0表示命令 
    AT24C04_SendByte(0xAA);                 //发送数据0xAA
    AT24C04_Stop();                         //发送停止信号

    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x00);                 //0表示命令 
    AT24C04_SendByte(0xA5);                 //发送数据0xA5
    AT24C04_Stop();                         //发送停止信号

	AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x00);                 //0表示命令 
    AT24C04_SendByte(0xE8);                 //新的IIC地址E0-FE中偶数(参考PDF文档)
    AT24C04_Stop();                         //发送停止信号

}
//*********************************************************
void CMP_OFFS(void)                         //磁偏角
{
    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x03);                 //0表示命令 
    AT24C04_SendByte(0x00);                 //磁偏角高8位，写入0
    AT24C04_Stop();                         //发送停止信号

    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x04);                 //0表示命令 
    AT24C04_SendByte(0x64);                 //磁偏角低8位，写入100（实际是10.0度）
    AT24C04_Stop();                         //发送停止信号
}
//*********************************************************


