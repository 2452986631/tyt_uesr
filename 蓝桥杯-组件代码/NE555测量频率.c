#include "reg52.h"
#include "absacc.h"



unsigned int count_f = 0;
unsigned char count_t = 0;
unsigned int dat_f = 0;
//定时器1用方式1，定时   16位定时器
//定时器0用方式2，计数   8位自动重装计数器

//频率显示函数
void NE555_Display()
{
	buf[0]=10;
	(dat_f>=1000000)?(buf[1] = dat_f/1000000%10):(buf[1] = 13);
	(dat_f>=100000)? (buf[2] = dat_f/100000%10): (buf[2] = 13);
	(dat_f>=10000)?  (buf[3] = dat_f/10000%10):  (buf[3] = 13);
	(dat_f>=1000)?   (buf[4] = dat_f/1000%10):   (buf[4] = 13);
	(dat_f>=100)?    (buf[5] = dat_f/100%10):    (buf[5] = 13);
	(dat_f>=10)?     (buf[6] = dat_f/10%10):	 (buf[6] = 13);
	buf[7]=dat_f%10;
}
//周期显示函数
void Period_Dispaly()
{
	Period=(1000000/dat_f);
    buf[0]=14;
	(Period>=1000000)?(buf[1] = Period/1000000%10):(buf[1] = 13);
	(Period>=100000)? (buf[2] = Period/100000%10): (buf[2] = 13);
	(Period>=10000)?  (buf[3] = Period/10000%10):  (buf[3] = 13);
	(Period>=1000)?   (buf[4] = Period/1000%10):   (buf[4] = 13);
	(Period>=100)?    (buf[5] = Period/100%10):    (buf[5] = 13);
	(Period>=10)?     (buf[6] = Period/10%10):	   (buf[6] = 13);
	buf[7]=Period%10;
}
void Init_Timer()//定时器初始化
{
	TMOD = 0x16;    
	AUXR |= 0x40;

	TH0 = 0xff;        
	TL0 = 0xff;
	TH1 =0xD1;        
	TL1 =0x20;

	TR0 = 1;
	TR1 = 1;

	ET0 = 1;
	ET1 = 1;
	EA = 1;
}
 
void Service_T0() interrupt 1
{
	count_f++;
}
 
void Service_T1() interrupt 3
{
    TH1 =0xD1;        
	TL1 =0x20;
	count_t++;
	if(count_t == 20)
	{
		dat_f = count_f;
		count_f = 0;//计数
		count_t = 0;//计时
	}
}
