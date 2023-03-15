#include <STC15F2K60S2.H>
#include "intrins.h"
 
sbit SCK = P1^7; //时钟线	
sbit SDA = P2^3; //数据线	
sbit RST = P1^3; //使能线	



//写读寄存器地址
unsigned char code READ_RTC_ADDR[8] =  {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d,0x8f};//0x85  12h制   0x05  24h制
unsigned char code WRITE_RTC_ADDR[8] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c,0x8e};//0x84  12h制   0x04  24h制 
//时间数组，索引0~6分别为秒、分、时、日、月、星期、年
unsigned char TIME[3] = {0x59,0x58,0x23};//16进制   89 89 35  10进制 %16  /16    59  59 23转换为索引

//写字节
void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//向DS1302寄存器写入数据
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
	//初始化
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_(); 
	
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//从DS1302寄存器读出数据
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

// DS1302设置时间，调用之后，TIME数组的数字会被设置到DS1302中
void DS1302_SetTime(void)
{
	unsigned char i;
	DS1302_WriteByte(WRITE_RTC_ADDR[7],0x00);//关闭写保护
	for(i=0;i<3;i++)
	{
		DS1302_WriteByte(WRITE_RTC_ADDR[i],TIME[i]);
	}
	DS1302_WriteByte(WRITE_RTC_ADDR[7],0x80);//打开写保护
}
//DS1302读取时间，调用之后，DS1302中的数据会被读取到TIME数组中
void DS1302_ReadTime(void)
{
	unsigned char Temp,i;
	for(i=0;i<3;i++)
	{
		Temp=DS1302_ReadByte(READ_RTC_ADDR[i]);
		TIME[i]=Temp;
	}
}
