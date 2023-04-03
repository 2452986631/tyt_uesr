#include <STC15F2K60S2.H>
#include "intrins.h"
#define VREF  4850     //PCF8591参考电压
/*Vaout = VREF / 255*dac_value; //电压转换
Voin=temp*1.96+0.5;
IIC时序在读取/写入可以关闭中断，EA=0/EA=1防止中断时序
读取电压值需要使用整形*/
unsigned int voin,temp;
void adc_pcf8591()
{
	IIC_Start();				
	IIC_SendByte(0x90); //器件地址		
	IIC_WaitAck(); 
 	
	IIC_SendByte(0x01); 	
	IIC_WaitAck();  						
	IIC_Stop(); 						
	 
	IIC_Start();								
	IIC_SendByte(0x91); 	
	IIC_WaitAck(); 		
	temp = IIC_ReceiveByte();	//读取PCF8591通道1的数据 			
	IIC_SendAck(1); 			
	IIC_Stop(); 
		
	Voin=temp*1.96+0.5;
}

void dac_pcf8591(unsigned char dat)//DAC输出   dat - 输入进行数模转换的数据 （写入）
{
    IIC_Start();
    IIC_SendByte(0x90);  //PCF8591的写设备地址 
    IIC_WaitAck();
    IIC_SendByte(0x43);  //DAC输出模式 
    IIC_WaitAck();

    IIC_SendByte(dat);
    IIC_WaitAck();
    IIC_Stop();
	
	operate_delay(10);      //等待电压转换完成
}
void Display_AD()
{
	AD();
	buf[0]=11;
	buf[1]=13;
	buf[2]=(Vaout/100)%10;
	buf[3]=(Vaout/10)%10;
	buf[4]=Vaout%10;
	buf[5]=13;
	buf[6]=13;
	buf[7]=1;
}