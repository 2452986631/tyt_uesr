#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "Motor.h"
#include "usart.h"
#include "hmi.h"
#include "motion.h"
#include "usart3.h"
#include "esp8266.h"
#include "wave.h"
#include "key.h"
#include "timer.h"

uint8_t KeyNum;

int main(void)
{
  uint8_t key;
	OLED_Init();
	Motion_Init();
	delay_init();
  Key_Init();
//---------------串口初始化--------------------------
	uart_init(115200);
  usart3_init(115200);
//----------------超声波初始化-----------------------
	Wave_SRD_Init();
	Timer_SRD_Init(9998,7199); //Tout= ((4999+1)*( 7199+1))/72=500000us=500ms
	//OLED_ShowString(1,1,"Distance=000cm");
//----------ESP8266初始化----------------------------
//	esp8266_start_trans();  //esp8266进行初始化
//	esp8266_send_data("WIFI连接成功\r\n",50);
//	esp8266_send_data("TCP连接成功\r\n",50); 

	while (1)
	{
////--------------超声波测距-------------------------

//		Wave_SRD_Strat();
//    delay_ms(200);
//		OLED_ShowNum(1,10,EXTI9_5_IRQHandler(),3);
////-----------超声波速度控制------------------------
//		if( EXTI9_5_IRQHandler()>30 && EXTI9_5_IRQHandler()<50 )
//				{
//					Motor_SetSpeed_a(40);
//					Motor_SetSpeed_b(40);
//				}
//		else if(EXTI9_5_IRQHandler()>50)
//				{
//					Motor_SetSpeed_a(80);
//					Motor_SetSpeed_b(80);
//				}
//    else if(EXTI9_5_IRQHandler()<=30)
//				{
//					Motor_SetSpeed_a(0);
//					Motor_SetSpeed_b(0);
//				}
//----------前进控速-------------------------------
   if(Res==0x01)
		{ Speeda+=20;
			Speedb=0;
			if(Speeda>=100) { Speeda=100; }
			Go_forward(Speeda); 
		}
   if(Res==0x02)
		{ Speeda-=20;
			Speedb=0;
      if(Speeda<=0) { Speeda=0; }
			Go_forward(Speeda);
		}
//----------------后退控速------------------------
   if(Res==0x03)
		{ Speedb+=20;
			Speeda=0;
      if(Speedb>100) { Speedb=100; }
			Fall_back(Speedb);
		}
   if(Res==0x04)
		{ Speedb-=20;
			Speeda=0;
      if(Speedb<0) { Speedb=0; }
			Fall_back(Speedb);
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
			Speeda=0;
			Speedb=0;
			Stop();
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
