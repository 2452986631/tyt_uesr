#ifndef __MOTION_H
#define __MOTION_H



extern int8_t Speeda,Speedb;
extern int8_t Speed1,Speed2,Speed3,Speed4;
//------------------------------------------------------------------
void Motion_Init(void);
void Stop(void);
void Go_forward(uint8_t Speeda);
void Fall_back(uint8_t Speedb);
void Turn_left(int8_t Speed1,int8_t Speed2,int8_t Speed3,int8_t Speed4);
void Trun_right(int8_t Speed1,int8_t Speed2,int8_t Speed3,int8_t Speed4);

void go(void);


#endif
