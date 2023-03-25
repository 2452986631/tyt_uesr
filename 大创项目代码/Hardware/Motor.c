#include "stm32f10x.h"                  // Device header
#include "PWM.h"

int8_t Speeda=0,Speedb=0;
int8_t Speed1=0,Speed2=0,Speed3=0,Speed4=0;



void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure2);

	PWM_Init();
}


//----------------------------------------------
void Motor_SetSpeed_a(int8_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompare1(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompare1(-Speed);
	}
}

void Motor_SetSpeed_b(int8_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);
		GPIO_ResetBits(GPIOA, GPIO_Pin_12);
		PWM_SetCompare2(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_11);
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		PWM_SetCompare2(-Speed);
	}
}
//---------------------------------------------
void Motor_SetSpeed_c(int8_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare3(-Speed);
	}
}

void Motor_SetSpeed_d(int8_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare4(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare4  (-Speed);
	}
}

//------------------------------
void Stop(void)
{
	Motor_SetSpeed_a(0);
	Motor_SetSpeed_b(0);
	Motor_SetSpeed_c(0);
	Motor_SetSpeed_d(0);
}

void Go_forward(uint16_t Speeda)//Spend大于0
{
	Motor_SetSpeed_a(Speeda);
	Motor_SetSpeed_b(Speeda);
	Motor_SetSpeed_c(Speeda);
	Motor_SetSpeed_d(Speeda);	
}

void Fall_back(uint16_t Speedb)//Spend小于0
{
	Motor_SetSpeed_a(-Speedb);
	Motor_SetSpeed_b(-Speedb);
	Motor_SetSpeed_c(-Speedb);
	Motor_SetSpeed_d(-Speedb);
}


void Turn_left(uint16_t Speed1,uint16_t Speed2,uint16_t Speed3,uint16_t Speed4)//参数大于0
{
	Motor_SetSpeed_a(Speed1);
	Motor_SetSpeed_b(Speed2);
	Motor_SetSpeed_c(Speed3);
	Motor_SetSpeed_d(Speed4);
}

void Trun_right(uint16_t Speed1,uint16_t Speed2,uint16_t Speed3,uint16_t Speed4)//参数大于0
{
	Motor_SetSpeed_a(Speed1);
	Motor_SetSpeed_b(Speed2);
	Motor_SetSpeed_c(Speed3);
	Motor_SetSpeed_d(Speed4);
}
