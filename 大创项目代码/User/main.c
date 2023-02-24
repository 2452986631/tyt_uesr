#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "usart.h"
#include "hmi.h"
#include "motion.h"
#include "usart3.h"
#include "esp8266.h"
#include "key.h"


uint8_t KeyNum;

int main(void)
{
  uint8_t key;
	OLED_Init();
	Motion_Init();
	delay_init();
  Key_Init();
	uart_init(115200);
  usart3_init(115200);

	esp8266_start_trans();//esp8266进行初始化
	esp8266_send_data("连接成功\r\n",50);
	esp8266_send_data("加油\r\n",50); 

	while (1)
	{
//----------前进控速-------------------------------
   if(Res==0x01)
		{ Speeda+=20;
			Speedb=0;
			Go_forward(Speeda);
      if(Speeda>100) { Speeda=100; }
		}
   if(Res==0x02)
		{ Speeda-=20;
			Speedb=0;
			Go_forward(Speeda);
      if(Speeda<0) { Speeda=0; }

		}
//----------------后退控速------------------------
   if(Res==0x03)
		{ Speedb+=20;
			Speeda=0;
			Fall_back(Speedb);
      if(Speedb>100) { Speedb=100; }
		}
   if(Res==0x04)
		{ Speedb-=20;
			Speeda=0;
			Fall_back(Speedb);
      if(Speedb<0) { Speedb=0; }
		}
//------------------左转--------------------------
		if(Res==0x05)
		{
      Speed1=20; Speed2=30; Speed3=25; Speed4=35;
			Turn_left(Speed1,Speed2,Speed3,Speed4);
		}
//------------------右转--------------------------
		if(Res==0x06)
		{
      Speed1=30; Speed2=20; Speed3=35; Speed4=25;
			Trun_right(Speed1,Speed2,Speed3,Speed4);
		}
//--------------------停止运动--------------------
		if(Res==0x07)
		{
			Stop();
			Speeda=0;
			Speedb=0;
		}
//-------------------OLED显示---------------------
		if(Res==0x05||Res==0x06)
		{
        OLED_ShowString(1, 1, "Speed1:");
				OLED_ShowString(2, 1, "Speed2:");
				OLED_ShowString(3, 1, "Speed3:");
				OLED_ShowString(4, 1, "Speed4:");
				OLED_ShowSignedNum(1, 8, Speed1, 3);
				OLED_ShowSignedNum(2, 8, Speed2, 3);
				OLED_ShowSignedNum(3, 8, Speed3, 3);
				OLED_ShowSignedNum(4, 8, Speed4, 3);
		}
//-------------ESP8266连接------------------------
			key=Key_GetNum();
      if(key==1)                 
      {esp8266_send_data("按键一有效\r\n",50);}
      if(key==2)
      {esp8266_send_data("按键二有效\r\n",50);}
      if(key==3)
      { esp8266_send_data("按键三有效\r\n",50);  printf("666");}
//------------------串口屏显示--------------------
//	HMI_SendNum(USART1,"n0.val=\r\n",7,6532,4);
//	HMI_SendNum(USART1,"n1.val=\r\n",7,6,1);
//	HMI_SendNum(USART1,"n2.val=\r\n",7,6,1);
//	HMI_SendNum(USART1,"n3.val=\r\n",7,5,1);
//	HMI_SendNum(USART1,"n4.val=\r\n",7,3,1);
//	printf("接收------:%d\r\n",Res);
//	HMI_SendText(USART1,"t2.txt=",7,"去问问她让我他\r\n",16);	
		Res=0;
		delay_ms(50);
//--------------------------------------------------
	}
}

  