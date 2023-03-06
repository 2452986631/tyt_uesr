#include "stm32f10x.h"                  // Device header
#include "motor.h"
#include "OLED.h"
#include "hmi.h"
uint8_t Speeda=0,Speedb=0;
uint8_t Speed1=0,Speed2=0,Speed3=0,Speed4=0;

void Motion_Init(void)
{
	Motor_Init();
}

void Stop(void)
{
	Motor_SetSpeed_a(0);
	Motor_SetSpeed_b(0);
  Motor_SetSpeed_c(0);
	Motor_SetSpeed_d(0);
	OLED_Clear();
  OLED_ShowString(1, 1, "Speeda:");
  OLED_ShowString(2, 1, "Speedb:");
	OLED_ShowSignedNum(1, 8, Speeda, 3);
	OLED_ShowSignedNum(2, 8, Speedb, 3);
}

void Go_forward(uint8_t Speeda)//Spend大于0
{
	Motor_SetSpeed_a(Speeda);
	Motor_SetSpeed_b(Speeda);
  Motor_SetSpeed_c(Speeda);
	Motor_SetSpeed_d(Speeda);	
	OLED_Clear();
  OLED_ShowString(1, 1, "Speeda:");
	OLED_ShowSignedNum(1, 8, Speeda, 3);	
}

void Fall_back(uint8_t Speedb)//Spend小于0
{
	Motor_SetSpeed_a(-Speedb);
	Motor_SetSpeed_b(-Speedb);
  Motor_SetSpeed_c(-Speedb);
	Motor_SetSpeed_d(-Speedb);
  OLED_Clear();
  OLED_ShowString(1, 1, "Speedb:");
	OLED_ShowSignedNum(1, 8, Speedb, 3);

}


void Turn_left(uint8_t Speed1,uint8_t Speed2,uint8_t Speed3,uint8_t Speed4)//参数大于0
{
	Motor_SetSpeed_a(Speed1);
	Motor_SetSpeed_b(Speed2);
  Motor_SetSpeed_c(Speed3);
	Motor_SetSpeed_d(Speed4);
}

void Trun_right(uint8_t Speed1,uint8_t Speed2,uint8_t Speed3,uint8_t Speed4)//参数大于0
{
	Motor_SetSpeed_a(Speed1);
	Motor_SetSpeed_b(Speed2);
  Motor_SetSpeed_c(Speed3);
	Motor_SetSpeed_d(Speed4);
}


