#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "usart3.h"
#include "esp8266.h"
#include "string.h"
#include "timer.h"
#include "key.h"



/*
项目的主要内容：STM32配合ESP8266模块与服务器数据交互
ESP8266的连接：USART3（PB10、PB11）
如何判断数据接收完全？
1、出现了换行符；
2、如果超过10ms了都没有下一条数据（TIM7来进行10ms的定时）。
*/
 
uint8_t key=0;
 int main(void)
 {		
	delay_init();	    	 			//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 			//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 				//串口初始化为115200
	usart3_init(115200);	 				//串口初始化为115200
	Key_Init();
	esp8266_start_trans();							//esp8266进行初始化
	 
	esp8266_send_data("连接成功\r\n",50);
	esp8266_send_data("加油\r\n",50); 
	//esp8266_quit_trans();
 	while(1)
	{
		key=Key_GetNum();
      if(key==1)                 
      {esp8266_send_data("按键一有效\r\n",50);}
      if(key==2)
      {esp8266_send_data("按键二有效\r\n",50);}
      if(key==3)
      { esp8266_send_data("按键三有效\r\n",50);  printf("666");}
   
	}
 }
