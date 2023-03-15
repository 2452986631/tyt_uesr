#include <STC15F2K60S2.H>
#include "intrins.h"
 
sbit TX = P1^0;
sbit RX = P1^1;

//============40KHx超声波超声波测距====================
void Delay13us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 33;
	while (--i);
}

void Send_Wave()                 //产生8个40KHx超声波信号  //T=25us
{
	unsigned char i;
	for(i = 0; i < 8; i++)//26us
	{
		TX = 1;
		Delay14us();	
		TX = 0;
		Delay14us();
	}
}
 

void Measure_Sonic()	        //超声波测距
{
	unsigned int time = 0;
	
	TMOD &= 0x0f;	    //0000 1111   //定时器1模式0，16位，计数器 最大65535个计数脉冲《stc15系列！！！》								
	TL1 = 0x00;										
	TH1 = 0x00;		
	
	Send_Wave();		//发送超声波信号	
	TR1 = 1;            //启动定时器						
	while((RX == 1) && (TF1 == 0));    //等待超声波信号返回或者等到测量超出范围
	TR1 = 0;            //停止定时器				
	
	if(TF1 == 0)	            //正常测量范围，根据定时器溢出标志位来判断是否有效						
	{
		time=TH1;		
		time = (time << 8) | TL1;		
		distance =(time*17/1000 )  + 3;	//需要根据实际的情况进行微调;(time/2/1000 000 * 340 ) *100 + 3;因为distance为unsigned int型，所以计算机计算时不能超过范围
	}
	else          //超出测量范围：当定时器溢出时，也就是定时器计数了85535次，相当于0.085535秒，得到的距离为29.4米，远远超出测量范围
	{
		TF1 = 0;
		distance = 500;
	}
}
