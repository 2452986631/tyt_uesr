#include "stm32f10x.h"                  // Device header
#include "usart5.h"

#include "usart.h"
#include "hmi.h"

/**************************************************************************
函数功能：串口5初始化
入口参数： bound:波特率
返回  值：无
**************************************************************************/
void uart5_init(u32 bound)
{
	//GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//使能GPIOC、GPIOD时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//使能USART5时钟
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	 //NVIC
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器


	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART5, &USART_InitStructure);     //初始化串口5
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(UART5, ENABLE);                    //使能串口5
}


/**************************************************************************
函数功能：串口5接收中断
入口参数：无
返回  值：无
**************************************************************************/
u8 result;
unsigned char flag=0;
void UART5_IRQHandler(void)
{
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
		{
			result =USART_ReceiveData(UART5);	//读取接收到的数据
			flag=1;
    }
}
