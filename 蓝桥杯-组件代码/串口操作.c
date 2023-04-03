#include <STC15F2K60S2.H>
//STC—ISP生成的定时器，波特率可以不修改直接使用，不冲突，注意晶振频率和打开中断即可
//--------------------------------------
void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xC7;			//设置定时初始值
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
EA=1;
ES=1;
}

void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x20;				//设置定时初始值
	TH0 = 0xD1;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
EA=1;
ET0=1;
}
//------------------------------------------------
unsigned char tmpRecv;
/*=============发送单个字节函数================*/
void SendByte(unsigned char dat)
{
    SBUF = dat;            //将数据放进SBUF缓冲器
    while(TI == 0);        //等待发送数据完成
    TI = 0;                //清除发送完成标志
}
//=================发送字符函数==================
void SendString(unsigned char *str)
{
	while(*str!='\0')
	{
		SendByte(*str++);
	}
}
/*=============串口中断服务函数================*/
void Sevice_Uart() interrupt 4
{
    if(RI == 1)                //接收到一个完整的字节
    {
        RI = 0;                //清除接收完成标志
        tmpRecv = SBUF;
        SendByte(tmpRecv + 1);
    }
}
