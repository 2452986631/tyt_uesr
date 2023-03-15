#include <STC15F2K60S2.H>
//--------------------------------------
unsigned char tmpRecv;
void Init_Uart()
{
    TMOD=0x20;        //��ʱ��1����ģʽΪ�Զ���װ
    TH1=0xfd;         //���ò�����Ϊ9600
    TL1=0xfd;         //11.0592M��12M��12��Ƶ
    AUXR=0x00;        //bit7=1����ʱ��1����Ƶ��0��12��Ƶ
    TR1=1;            //������ʱ��1
    SCON = 0x50;      //���ڲ���Ϊģʽ1���������
    ES=1;             //ʹ�ܴ����ж�
    EA=1;             //ʹ�����ж�
}
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



main()
{
    Init_Uart();
    SendByte(0x5a);
    SendByte(0xa5);
    while(1);
}