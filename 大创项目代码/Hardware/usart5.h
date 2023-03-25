#ifndef __USRAT5_H
#define __USRAT5_H 
#include "sys.h"	  	


extern u8 result;
extern unsigned char flag;


void uart5_init(u32 bound);
void UART5_IRQHandler(void);



#endif

