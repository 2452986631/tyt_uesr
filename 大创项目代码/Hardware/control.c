#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "usart24.h"

uint8_t subtract1;
uint8_t subtract2;

void INit(void)
{
	Motor_Init();
}

void Contrlo_Stop(void)//停止  40cm~50cm
{
	if( (distanceL<=500) && (distanceR<=500) && (distanceL>400) && (distanceR>400) )
	{ Stop(); }
}

void Comtrol_Forward(void)//前进控速
{

//----------distance 50cm~75cm
	if((distanceL<=750) && (distanceR<=750) && (distanceL>500) && (distanceR>500))
	{
		Go_forward(20);
	}
//----------distance 75cm~100cm
	if((distanceL<=1000) && (distanceR<=1000) && (distanceL>750) && (distanceR>750))
	{
		Go_forward(30);
	}
//-------大于100cm
	if( (distanceL>1000) && (distanceR>1000) )
	{
		Go_forward(40);
	} 
}

void Contrlo_Left(void)//左转
{
	subtract1=distanceR-distanceL;
	if( subtract1 >=50)
	{
		Turn_left(8,24,16,32);
	}
}

void Contrlo_Right(void)//右转
{
  subtract2=distanceL-distanceR;
	if( subtract2 >=50)
	{
		Trun_right(24,8,32,16);
	}
}

//oid Contrlo_Back()//后退
//{
////----------distance <=30cm
//	if((distanceL<=300) && (distanceR<=300) )
//	{
//		Fall_back(10);
//	}
//}
