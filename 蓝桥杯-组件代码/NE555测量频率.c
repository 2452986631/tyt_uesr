#include "reg52.h"
#include "absacc.h"



unsigned int count_f = 0;
unsigned char count_t = 0;
unsigned int dat_f = 0;
//定时器1用方式1，定时   16位定时器
//定时器0用方式2，计数   8位自动重装计数器
void Init_Timer()//定时器初始化
{
	TH0 = 0xff;        
	TL0 = 0xff;
	
	TH1 = (65536 - 50000) / 256;        
	TL1 = (65536 - 50000) % 256;
	
	TMOD = 0x16;    
	
	ET0 = 1;
	ET1 = 1;
	EA = 1;
	
	TR0 = 1;
	TR1 = 1;
}
 
void Service_T0() interrupt 1
{
	count_f++;
}
 
void Service_T1() interrupt 3
{
    TH1 = (65536 - 50000) / 256;        
	TL1 = (65536 - 50000) % 256;
	count_t++;
	if(count_t == 20)
	{
		dat_f = count_f;
		count_f = 0;//计数
		count_t = 0;//计时
	}
}
