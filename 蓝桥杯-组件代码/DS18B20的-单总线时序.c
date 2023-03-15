#include <STC15F2K60S2.H>
#include "intrins.h"

sbit DQ = P1^4;     //DS18B20数据引脚

//单总线内部延时函数
void Delay_OneWire(unsigned int t)  
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<12;i++);
	}
}

//单总线写操作
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
}

//单总线读操作
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}

//DS18B20初始化
bit init_ds18b20(void)
{
  	bit initflag = 0;
  	
  	DQ = 1;
  	Delay_OneWire(12);
  	DQ = 0;
  	Delay_OneWire(80);
  	DQ = 1;
  	Delay_OneWire(10); 
    initflag = DQ;     
  	Delay_OneWire(5);
  
  	return initflag;
}

void DS18B20_ReadTemperature()//温度读取函数
{
	unsigned char LSB,MSB;
	init_ds18b20();//初始化
	Write_DS18B20(0xcc);//跳过ROM
	Write_DS18B20(0x44);//温度转换
	Delay_OneWire(200);//延时700ms 等待温度转换完成
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);//开始读取暂存器
	LSB=Read_DS18B20();//读取温度
	MSB=Read_DS18B20();
	init_ds18b20();

	T_dat = 0x0000;
	T_dat = MSB;
	T_dat <<= 8;
	T_dat = T_dat | LSB;         //将LSB和MSB整合成为一个16位的整数

	//首先通过温度数据的高5位判断采用结果是正温度还是负温度
	if((T_dat & 0xf800) == 0x0000)    //正温度的处理办法
	{
		T_dat >>= 4;         //取出温度结果的整数部分
		T_dat = T_dat*10;    //放大10倍，然后加上小数部分
		T_dat = T_dat + (LSB&0x0f)*0.625;
	}
}

