#ifndef _PWM_H
#define _PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
						  
////////////////////////////////////////////////////////////////////////////////// 	


//#define MEN PBout(6)	// DS0
//#define MDIR PBout(7)	// DS1	




extern u32 PWMX_Num;
extern u32 PWMY1_Num;
extern u32 PWMY2_Num;

void TIM1_GPIO_Config(void);
void TIM1_PWM_Init(u32 arr,u32 psc);

void TIM3_PWM_Init(u32 arr,u32 psc);	
	
void TIM8_PWM_Init(u32 arr,u32 psc);	
	
	
#endif
