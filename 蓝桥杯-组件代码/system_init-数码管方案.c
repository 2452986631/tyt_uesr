#include <STC15F2K60S2.H>
#include "intrins.h"

//引脚定义
sbit m74HC138_A=P2^5;
sbit m74HC138_B=P2^6;
sbit m74HC138_C=P2^7;

unsigned char buf[8]={0,1,2,3,4,5,6,7};
unsigned char code SMG_duanma[19]=
{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,//0-9
0x88,0x80,0xc6,0xc0,0x86,0x8e,//A-F
0xbf,0x7f,0xff};//- . 灭灯
//数码管段码 温度 带点
unsigned char code SMG_IsDot[10] = {0x40,0x79,0x24,
	0x30,0x19,0x12,0x02,0x78,0x00,0x10};


void m74HC138(unsigned char value)//74HC138选择74HC573锁存器
{
		switch(value)
	{
		//LED
		case 4: m74HC138_C=1; m74HC138_B=0; m74HC138_A=0;break;
		//ULN2003
		case 5: m74HC138_C=1; m74HC138_B=0; m74HC138_A=1;break;
		//位选
		case 6: m74HC138_C=1; m74HC138_B=1; m74HC138_A=0;break;
    //段选
		case 7: m74HC138_C=1; m74HC138_B=1; m74HC138_A=1;break;
		//关闭74HC138
		case 8: m74HC138_C=0; break;
	}
}
void Delayxms(unsigned char xms)//STC15F系列 1ms延时函数
{
	unsigned char i, j;
	while(xms--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}

void system_init(void)//关闭LED与蜂鸣器
{
	m74HC138(4); P0=P0&0xff;m74HC138(8);
	m74HC138(5); P0=P0&0x00;m74HC138(8);
}

//动态数码管模块,用在定时器中
void DisplaySMG_Bit()
{
  static unsigned char i=0;
	m74HC138(6);//位选  高电平为选中
	P0 = 0x01 << i;
	m74HC138(7);//段码
	P0 = tab[buf[i]];
	if(++i==8){ i=0; }
}
//定时器0模块
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x20;		//设置定时初值
	TH0 = 0xD1;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
 
	EA=1;//总中断
	ET0=1;//定时器0中断
}

void main()
{
	system_init();
	Timer0Init();
	while(1)
	{

	}
}

void timer0_svr() interrupt 1
{
	static unsigned char times=0;
	times++;TF0=0;
	if(times>=2){ //2ms显示一个
		DisplaySMG_Bit();//动态数码管
		times=0;
	}
}

