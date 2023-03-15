#include <STC15F2K60S2.H>
//--------------------------------------
unsigned char tmpRecv;
void Init_Uart()
{
    TMOD=0x20;        //定时器1工作模式为自动重装
    TH1=0xfd;         //设置波特率为9600
    TL1=0xfd;         //11.0592M或12M的12分频
    AUXR=0x00;        //bit7=1：定时器1不分频，0则12分频
    TR1=1;            //启动定时器1
    SCON = 0x50;      //串口参数为模式1和允许接收
    ES=1;             //使能串口中断
    EA=1;             //使能总中断
}
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



main()
{
    Init_Uart();
    SendByte(0x5a);
    SendByte(0xa5);
    while(1);
}