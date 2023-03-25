#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "usart24.h"
#include "usart3.h"
#include "usart5.h"
#include "hmi.h"
#include "esp8266.h"
#include "timer.h"
#include "delay.h"
#include "Motor.h"
#include "motor.h"
#include "control.h"


int main(void)
{
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	Motor_Init();
	  delay_init();		
		INit();
//---------------���ڳ�ʼ��--------------------------
	uart_init(115200);
	uart2_init(115200);
  usart3_init(115200);
	uart4_init(115200);
	uart5_init(9600);
//----------ESP8266��ʼ��--------------------------
//	esp8266_start_trans();  //esp8266���г�ʼ��
//	esp8266_send_data("WIFI���ӳɹ�\r\n",50);
//	esp8266_send_data("TCP���ӳɹ�\r\n",50); 

	while (1)
	{
//		printf("distanceL:%d\r\n",distanceL);
//		printf("distanceR:%d\r\n",distanceR);
//		delay_ms(1000);
			Comtrol_Forward();
//--------------�ƶ�����----------------
//	if( (subtract1<150) &&  (subtract2<150) )
//	{
//		Contrlo_Stop();//ֹͣ
//		Comtrol_Forward();//ǰ������
//	}
//	if( (subtract1>=50) || (subtract2>=50) )
//	{
//		Contrlo_Left();//��ת
//		Contrlo_Right();//��ת
//	}

////------------------��������ʾ--------------------
////	HMI_SendNum(USART1,"n0.val=\r\n",7,6532,4);
//		HMI_SendNum(USART1,"n1.val=\r\n",7,distanceR,4);
//		HMI_SendNum(USART1,"n2.val=\r\n",7,distanceL,4);
//		HMI_SendNum(USART1,"n3.val=\r\n",7,result[0],7);
////	HMI_SendNum(USART1,"n4.val=\r\n",7,3,1);
////	printf("����------:%d\r\n",Res);
////	HMI_SendText(USART1,"t2.txt=",7,"��������ѧԺ\r\n",16);	

//		Res=0;
//		delay_ms(50);
//--------------------------------------------------
	}
}

