#include <STC15F2K60S2.H>
#include "intrins.h"
/*
使用超声波的时候如果数码管是使用中断扫描，超声波定时会被中断打断，导致测量不准确
*/
sbit TX = P1^0;
sbit RX = P1^1;
unsigned char time_sonic=0;
void Init_Timer()//定时器初始化
{
	TMOD = 0x11;    
	AUXR |= 0x80;

	TH0 =0xd1;        
	TL0 =0x20;	

	TR0=1;
	TF0=0;

	ET0 = 1;
	EA = 1;
}
//============40KHx超声波超声波测距====================
void Delay13us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	_nop_();
	i = 36;
	while (--i);
}

void Send_Wave()                 //产生8个40KHx超声波信号  //T=25us
{
	unsigned char i;
	for(i = 0; i < 8; i++)//26us
	{
		TX = 1;
		Delay13us();	
		TX = 0;
		Delay13us();
	}
}
 
void Measure_Sonic()	        //超声波测距
{					
	TL1 = 0x00;										
	TH1 = 0x00;		
	Send_Wave();		    //发送超声波信号		
	TR1 = 1;            //启动定时器			
	while((RX == 1) && (TF1 == 0));    //等待超声波信号返回或者等到测量超出范围
	TR1 = 0;            //停止定时器				
	if(TF1 == 0)	            //正常测量范围，根据定时器溢出标志位来判断是否有效						
	{
		time=TH1;		
		time = (time << 8) | TL1;		
		distance =(time*17/1000 )  + 3;	
	}
	else          
	{
		TF1 = 0;
		distance = 500;
	}
}
void main()
{
	Init_Timer();
	system_init();
	while(1)
	{
		if(time_sonic==0)Measure_Sonic();
	}
}
void Timer0() interrupt 1
{
	static unsigned char count=0;
	TL0 = 0x20;			
	TH0 = 0xD1;		
    count++;   
	if(count>=2)
	{
		Display_SEGBit();		
		count=0;
	}
	time_sonic++;if(time_sonic>=100)time_sonic=0;
}

void DDD()
{
	buf[0]=18;
	buf[1]=18;
	buf[2]=18;
	buf[3]=18;
	buf[4]=18;
	buf[5]=(distance/100)%10;
	buf[6]=(distance/10)%10;
	buf[7]=distance%10;
}