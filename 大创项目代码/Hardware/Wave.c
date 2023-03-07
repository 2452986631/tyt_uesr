#include "wave.h"
#include "sys.h"
#include "delay.h"
#include "OLED.h"



float Distance;

void Wave_SRD_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitSture;
	EXTI_InitTypeDef  EXTI_InitSture;
	NVIC_InitTypeDef  NVIC_InitSture;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE);
	
	
	//
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_Out_PP;   
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_8;           
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOB,&GPIO_InitSture);
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_9;                
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOB,&GPIO_InitSture);
	
	//
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
	
	//
	EXTI_InitSture.EXTI_Line=EXTI9_5_IRQn;
	EXTI_InitSture.EXTI_LineCmd=ENABLE;
	EXTI_InitSture.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitSture);
	
	
	//
	NVIC_InitSture.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitSture);
}

uint8_t EXTI9_5_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET)
	{
		TIM_SetCounter(TIM4,0);
		TIM_Cmd(TIM4,ENABLE);
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9));  	
		TIM_Cmd(TIM4,DISABLE);
		
		Distance=(TIM_GetCounter(TIM4)*340)/200.0;//æ‡¿Îº∆À„
//		OLED_ShowNum(1,10,(uint8_t)Distance,3);
	
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
	return Distance;
}

void Wave_SRD_Strat(void)//40KHZ∑Ω≤®
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);   
	delay_us(13);               
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); 
	delay_us(13); 
}

