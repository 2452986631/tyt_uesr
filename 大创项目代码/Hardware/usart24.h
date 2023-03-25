#ifndef __USRAT24_H
#define __USRAT24_H 
#include "sys.h"	  	


void uart2_init(u32 bound);
void USART2_IRQHandler(void);

void uart4_init(u32 bound);
void UART4_IRQHandler(void);


extern unsigned char   dat1[3],dat2[3];
extern unsigned char   num1,num2;
extern int             distanceL,distanceR;	

#endif

