#include <STC15F2K60S2.H>
#include "intrins.h"


void init_pcf8591(void)//PCF8591初始化
{
    IIC_Start();
    IIC_WriteByte(0x90);//地址可以改   1/0 read/write
    IIC_WaitAck();

    IIC_WriteByte(0x03);  //ADC通道
    IIC_WaitAck();

    IIC_Stop();
    operate_delay(10);
}

unsigned char adc_pcf8591(void)// 通过I2C总线读取ADC结果  temp - AD转换结果
{
    unsigned char temp;
    IIC_Start();
    IIC_WriteByte(0x91);
    IIC_WaitAck();

    temp = IIC_ReceiveByte();
    IIC_SendAck(1);
    IIC_Stop();

    return temp;
}

void dac_pcf8591(unsigned char dat)//DAC输出   dat - 输入进行数模转换的数据 （写入）
{
    IIC_Start();
    IIC_WriteByte(0x90);
    IIC_WaitAck();
    IIC_WriteByte(0x40);  //DAC输出模式
    IIC_WaitAck();

    IIC_WriteByte(dat);
    IIC_WaitAck();
    IIC_Stop();
}


#define VREF  4850     //PCF8591参考电压
void main(void)
{
    unsigned char key_temp;
    unsigned char dac_value;  //DAC转换数据
    unsigned int Vaout;  //输出电压
    System_Init();
    init_pcf8591();
    AUXR |= 0x80;
    TMOD &= 0xF0;
    TL0 = 0xCD;
    TH0 = 0xD4;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;

    while (1)
    {
        if (key_flag)
        {
            key_flag = 0;
            key_temp = read_key();
        }
        //进入按键处理程序部分
        switch (key_temp)
        {
        case 1://加法
        {
            dac_value = dac_value + 5;
            if (dac_value > 255)dac_value = 255;
            dac_pcf8591(dac_value);
        }
        break;
        case 2://减法
        {
            dac_value = dac_value - 5;
            if (dac_value < 0)dac_value = 0;
            dac_pcf8591(dac_value);
        }
        break;
        }
		
        key_temp = 0;  //完成按键处理程序后，清除键值
        Vaout = VREF / 255 * dac_value; ////电压转换

        dspbuf[0] = 10;
        (Vaout >= 100) ? (dspbuf[1] = dac_value / 100) : (dspbuf[1] = 10);
        (Vaout >= 10) ? (dspbuf[2] = dac_value % 100 / 10) : (dspbuf[2] = 10);
        dspbuf[3] = dac_value % 10;

        //显示数据更新
        (Vaout >= 1000) ? (dspbuf[4] = Vaout / 1000)    : (dspbuf[4] = 10);
        (Vaout >= 100) ? (dspbuf[5] = Vaout % 100 / 10) : (dspbuf[5] = 10);
        (Vaout >= 10) ? (dspbuf[6] = Vaout % 10 / 10)   : (dspbuf[6] = 10);
        dspbuf[7] = Vaout % 10;
    }
}


