#include "iic.h"
#include <STC15F2K60S2.H>

//字节写操作
void Write_24C02(unsigned char addr, unsigned char dat)
{
EA=0;
	IIC_Start();		//IIC总线起始信号					
	IIC_SendByte(0xa0); //24C02的写设备地址
	IIC_WaitAck();		//等待从机应答	

	IIC_SendByte(addr); //内存字节字节
	IIC_WaitAck(); 		//等待从机应答
	
	IIC_SendByte(dat); 	//写入目标数据
	IIC_WaitAck();		//等待从机应答	
	IIC_Stop();		    //IIC总线停止信号		
EA=1;
}

//字节读操作
unsigned char Read_24C02(unsigned char addr)
{
	unsigned char tmp;
EA=0;
	//进行一个伪写操作
	IIC_Start();		//IIC总线起始信号					
	IIC_SendByte(0xa0); //24C02写设备地址
	IIC_WaitAck();		//等待从机应答	

	IIC_SendByte(addr); //内存自己地址
	IIC_WaitAck(); 		//等待从机应答	

	//进行字节读操作
	IIC_Start();		//IIC总线起始信号					
	IIC_SendByte(0xa1); //24C02读设备地址
	IIC_WaitAck();		//等待从机应答	
	tmp = IIC_RecByte();//读取目标数据

	IIC_SendAck(0); 	//产生非应答信号		
	IIC_Stop();		    //IIC总线停止信号		
	EA=1;
	return tmp;
}

