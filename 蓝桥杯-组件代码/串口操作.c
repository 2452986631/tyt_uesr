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
/*
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xE0;			//设置定时初始值
	T2H = 0xFE;			//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时

EA=1;
ES=1;
}
*/
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
//进阶
//通过串口发送数据到PC或PC发送到电脑
	unsigned char Distance[14],shu=0;
	Distance[0]='d';
	Distance[1]='i';
	Distance[2]='s';
	Distance[3]='t';
	Distance[4]='a';
	Distance[5]='n';
	Distance[6]='c';
	Distance[7]='e';
	Distance[8]=':';
	
	Distance[9]='0'+distance/100;
	Distance[10]='0'+(distance/10)%10;
	Distance[11]='0'+distance%10;
	Distance[12]='c';
	Distance[13]='m';
	Distance[14]='\0';
	SendString(Distance);

void LED_Uart()
{
	if( (dat[0]=='r') && (dat[1]=='e') && (dat[2]=='t') && (dat[3]=='u') && (dat[4]=='r') && (dat[5]=='n') )
	{
		m74HC138(4); P0=0xf0; m74HC138(8);
	dat[0]=0;
	dat[1]=0;
	dat[2]=0;
	dat[3]=0;
	dat[4]=0;
	dat[5]=0;
shu=0;
	}
	if( (dat[0]=='o') && (dat[1]=='p') && (dat[2]=='e') && (dat[3]=='n'))
	{
		m74HC138(4); P0=0x0f; m74HC138(8);
	dat[0]=0;
	dat[1]=0;
	dat[2]=0;
	dat[3]=0;
	dat[4]=0;
	dat[5]=0;
shu=0;
	}
}
void Uart() interrupt 4
{
	    if(RI == 1)                //接收到一个完整的字节
    {
        RI = 0;                //清除接收完成标志
        dat[shu] = SBUF;
        Send(dat[shu]);
		shu++;
    }
}
