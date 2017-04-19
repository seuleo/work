#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//********************************************************************************
//修改说明
//V1.1 20140504
//新增TIM14_PWM_Init函数,用于PWM输出
//V1.2 20140504
//新增TIM5_CH1_Cap_Init函数,用于输入捕获
////////////////////////////////////////////////////////////////////////////////// 	

void TIM5_Int_Init(u16 arr,u16 psc);

void ENC_Init(void);
u32 TIM2_Encoder_Read(void);
extern u8 Flag_Hatch;
void Tim2Config(void);

extern u8 tim;

extern u8 ADCFlag;
#endif























