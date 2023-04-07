#include <STC15F2K60S2.H>
//STC��ISP���ɵĶ�ʱ���������ʿ��Բ��޸�ֱ��ʹ�ã�����ͻ��ע�⾧��Ƶ�ʺʹ��жϼ���
//--------------------------------------
void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xC7;			//���ö�ʱ��ʼֵ
	TH1 = 0xFE;			//���ö�ʱ��ʼֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
EA=1;
ES=1;
}

void Timer0_Init(void)		//1����@12.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x20;				//���ö�ʱ��ʼֵ
	TH0 = 0xD1;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
EA=1;
ET0=1;
}
/*
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = 0xE0;			//���ö�ʱ��ʼֵ
	T2H = 0xFE;			//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ

EA=1;
ES=1;
}
*/
//------------------------------------------------
unsigned char tmpRecv;
/*=============���͵����ֽں���================*/
void SendByte(unsigned char dat)
{
    SBUF = dat;            //�����ݷŽ�SBUF������
    while(TI == 0);        //�ȴ������������
    TI = 0;                //���������ɱ�־
} 
//=================�����ַ�����==================
void SendString(unsigned char *str)
{
	while(*str!='\0')
	{
		SendByte(*str++);
	}
}
/*=============�����жϷ�����================*/
void Sevice_Uart() interrupt 4
{
    if(RI == 1)                //���յ�һ���������ֽ�
    {
        RI = 0;                //���������ɱ�־
        tmpRecv = SBUF;
        SendByte(tmpRecv + 1);
    }
}
//����
//ͨ�����ڷ������ݵ�PC��PC���͵�����
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
	    if(RI == 1)                //���յ�һ���������ֽ�
    {
        RI = 0;                //���������ɱ�־
        dat[shu] = SBUF;
        Send(dat[shu]);
		shu++;
    }
}
