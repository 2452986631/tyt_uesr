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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOE,ENABLE);
	
	
	//
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_Out_PP;   
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_4;                
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture);
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      
	GPIO_InitSture.GPIO_Pin=GPIO_Pin_6;                
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE,&GPIO_InitSture);
	
	//
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
	
	//
	EXTI_InitSture.EXTI_Line=EXTI_Line6;
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
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
		TIM_SetCounter(TIM3,0);
		TIM_Cmd(TIM3,ENABLE);
		
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6));  	
		TIM_Cmd(TIM3,DISABLE);
		
		Distance=(TIM_GetCounter(TIM3)*340)/200.0;//æ‡¿Îº∆À„
//		OLED_ShowNum(1,10,(uint8_t)Distance,3);
	
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	return Distance;
}

void Wave_SRD_Strat(void)//40KHZ∑Ω≤®
{
	GPIO_SetBits(GPIOE,GPIO_Pin_4);   
	delay_us(13);               
	GPIO_ResetBits(GPIOE,GPIO_Pin_4); 
	delay_us(13); 
}

