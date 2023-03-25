#ifndef __MOTOR_H
#define __MOTOR_H

extern int8_t Speeda,Speedb;
extern int8_t Speed1,Speed2,Speed3,Speed4;

void Motor_Init(void);
void Motor_SetSpeed_a(int8_t Speed);
void Motor_SetSpeed_b(int8_t Speed);
void Motor_SetSpeed_c(int8_t Speed);
void Motor_SetSpeed_d(int8_t Speed);


void Stop(void);
void Go_forward(uint16_t Speeda);
void Fall_back(uint16_t Speedb);
void Turn_left(uint16_t Speed1,uint16_t Speed2,uint16_t Speed3,uint16_t Speed4);
void Trun_right(uint16_t Speed1,uint16_t Speed2,uint16_t Speed3,uint16_t Speed4);


#endif
