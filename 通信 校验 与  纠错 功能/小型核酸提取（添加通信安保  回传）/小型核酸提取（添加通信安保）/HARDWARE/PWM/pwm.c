#include "pwm.h"
#include "usart.h"
#include "moto.h"

 
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32F407¿ª·¢°å
//¶¨Ê±Æ÷PWM Çý¶¯´úÂë	   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//´´½¨ÈÕÆÚ:2014/5/4
//°æ±¾£ºV1.0
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
////tim3 ch1  tim8 ch2
//PC6 PC7  PA8


u32 PWMX_Num=0;    //3200  4mm;
u32 PWMY1_Num=0;  
u32 PWMY2_Num=0;  // 1600  40.6MM;   40 1mm;


void TIM1_GPIO_Config()
{
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOB, ENABLE); 	//Ê¹ÄÜPORTFÊ±ÖÓ	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); //GPIOF9¸´ÓÃÎª¶¨Ê±Æ÷14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOA,&GPIO_InitStructure);


  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); //GPIOF9¸´ÓÃÎª¶¨Ê±Æ÷8 C 1
 	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOF9¸´ÓÃÎª¶¨Ê±Æ÷3 CH2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOC,&GPIO_InitStructure);


	//³õÊ¼»¯PF9
	
//	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;           //GPIOF9  //DIR AND ENABLE
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //³õÊ¼»¯Pb6 pb7 
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;           //GPIOF9  //DIR AND ENABLE
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //³õÊ¼»¯Pb6 pb7 
	

	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;           //GPIOF9  //DIR AND ENABLE
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //³õÊ¼»¯Pb6 pb7 
	
	
}
void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	//´Ë²¿·ÖÐèÊÖ¶¯ÐÞ¸ÄIO¿ÚÉèÖÃ
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM14Ê±ÖÓÊ¹ÄÜ    

	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	
	TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷14
	
	TIM_OCInitStructure.TIM_Pulse = arr/3;
	//³õÊ¼»¯TIM14 Channel1 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ÐÔ:TIMÊä³ö±È½Ï¼«ÐÔµÍ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //¸ù¾ÝTÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯ÍâÉèTIM1 4OC1

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM1ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
 //	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEÊ¹ÄÜ 
	
#if 1
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE); //?????3????  ceshi	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_TIM10_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	
	TIM_Cmd(TIM1, DISABLE);  //Ê¹ÄÜTIM14

										  
}  


void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//´Ë²¿·ÖÐèÊÖ¶¯ÐÞ¸ÄIO¿ÚÉèÖÃ
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM14Ê±ÖÓÊ¹ÄÜ   
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	
	TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷14
	
	TIM_OCInitStructure.TIM_Pulse = arr/3;
	//³õÊ¼»¯TIM34 Channel1 PWMÄ£Ê½	 
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ÐÔ:TIMÊä³ö±È½Ï¼«ÐÔµÍ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //¸ù¾ÝTÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯ÍâÉèTIM3 4OC1

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
 //	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEÊ¹ÄÜ 

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //?????3????  ceshi	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
//	TIM_Cmd(TIM1, ENABLE);  //Ê¹ÄÜTIM14
  TIM_CtrlPWMOutputs(TIM3,ENABLE);
  TIM_Cmd(TIM3, DISABLE); 									  
} 


void TIM8_PWM_Init(u32 arr,u32 psc)
{		 					 
	//´Ë²¿·ÖÐèÊÖ¶¯ÐÞ¸ÄIO¿ÚÉèÖÃ
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	//TIM14Ê±ÖÓÊ¹ÄÜ    

	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	
	TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷14
	
	TIM_OCInitStructure.TIM_Pulse = arr/3;
	//³õÊ¼»¯TIM14 Channel1 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ÐÔ:TIMÊä³ö±È½Ï¼«ÐÔµÍ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //¸ù¾ÝTÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯ÍâÉèTIM1 4OC1

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM8ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
// //	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
  TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPEÊ¹ÄÜ 

	TIM_ClearFlag(TIM8, TIM_FLAG_Update);

	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE); //?????3????  ceshi	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM8_UP_TIM13_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
//	TIM_Cmd(TIM1, ENABLE);  //Ê¹ÄÜTIM14
  TIM_CtrlPWMOutputs(TIM8,ENABLE);
  TIM_Cmd(TIM8, DISABLE); 
										  
} 



void TIM1_UP_TIM10_IRQHandler(void)
{ 
   if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
   {
			/* Clear TIM2 Capture Compare1 interrupt pending bit*/
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
   }
	 PWMX_Num++;
	 
   switch(srdx.run_state) 
   {			
			case ACCEL:			
				if(PWMX_Num >= srdx.run_start) 
					{         		 
						 srdx.run_state = RUN;				 
					}						
				if(XResetFlag) 
				 srdx.step_delay= XACC[PWMX_Num];		
				else 
				 srdx.step_delay= XACCReset[PWMX_Num];
				TIM1->CCR1=srdx.step_delay/2;
				TIM1->ARR=srdx.step_delay;
				 
				break;
			
			case RUN:
				if(PWMX_Num >= srdx.decel_start)
				{
					srdx.run_state = DECEL;
				}
				break;
					
			case DECEL:				
				if(PWMX_Num >=srdx.accel_count-1)  //   if(PWMX_Num >srdx.accel_count-1)
				{
					srdx.run_state = STOP;
				}
				if(XResetFlag)  
					srdx.step_delay = XACC[srdx.accel_count-PWMX_Num-1];//shao
				else 
					srdx.step_delay = XACCReset[srdx.accel_count-PWMX_Num-1];
				TIM1->CCR1=srdx.step_delay/2;
				TIM1->ARR=srdx.step_delay;
				break;
					
			case LRUN:				
				if(PWMX_Num >=srdx.accel_count-1)
				{
					srdx.run_state = STOP;
				}
				break;
				
			case STOP:
				PWMX_Num = 0;
				XStopFlag =0;
				TIM_Cmd(TIM1, DISABLE);	
				break;
		}
}


void TIM3_IRQHandler(void)
{ 

   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
   {
			/* Clear TIM2 Capture Compare1 interrupt pending bit*/
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
   }
	 
	  PWMY1_Num++;
	 
		if(Vib == 1)
		{			
			switch(srd1y.run_state) 
      {
				case ACCEL:		
					TIM3->CCR2=YACC[Y1SFlag][PWMY1_Num]>>2;
					TIM3->ARR=YACC[Y1SFlag][PWMY1_Num];
					if(PWMY1_Num >= srd1y.run_start) 
					{
						 srd1y.run_state = RUN;			 
					}	 
					break;
			
				case RUN:
					if(PWMY1_Num >= srd1y.decel_start)
					{
					 srd1y.run_state = DECEL;
					}
					break;
				case DECEL:

					if(PWMY1_Num >=srd1y.accel_count-1)  //   if(PWMX_Num >srdx.accel_count-1)
					{
						srd1y.run_state = STOP;		
					}
					else
					{
						TIM3->ARR=YACC[Y1SFlag][srd1y.accel_count-PWMY1_Num-1];
						TIM3->CCR2 = TIM3->ARR>>2;
					}
				  break;	
		  }
		}	 
		
		
}


void TIM8_UP_TIM13_IRQHandler(void)
{ 

   if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)
   {
    /* Clear TIM2 Capture Compare1 interrupt pending bit*/
    TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
   }
	 
	  PWMY2_Num++;
}