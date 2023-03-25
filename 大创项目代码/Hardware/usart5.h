#ifndef __USRAT5_H
#define __USRAT5_H 
#include "sys.h"	  	


extern int result;
extern unsigned char flag;
extern int data[100];
extern unsigned char sum;

void uart5_init(u32 bound);
void UART5_IRQHandler(void);


#endif

