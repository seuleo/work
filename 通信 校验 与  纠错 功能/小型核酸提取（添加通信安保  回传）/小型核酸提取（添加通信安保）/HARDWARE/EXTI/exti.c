#include "exti.h"
#include "delay.h" 
#include "pwm.h"
#include "time.h"
#include "moto.h"
#include "usart.h"
#include "DeviceVibration.h"
//#include "DeviceMagnetic.h"


u32 AB_cnt=0;
u16 Current_zcnt=0;
u16 Z_cnt =0;
extern u8 Flag_run;
//#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±æ≥Ã–Ú÷ªπ©—ßœ∞ π”√£¨Œ¥æ≠◊˜’ﬂ–Ìø…£¨≤ªµ√”√”⁄∆‰À¸»Œ∫Œ”√Õæ
//ALIENTEK STM32F407ø™∑¢∞Â
//Õ‚≤ø÷–∂œ «˝∂Ø¥˙¬Î	   
//’˝µ„‘≠◊”@ALIENTEK
//ºº ı¬€Ã≥:www.openedv.com
//¥¥Ω®»’∆⁄:2014/5/4
//∞Ê±æ£∫V1.0
//∞Ê»®À˘”–£¨µ¡∞Ê±ÿæø°£
//Copyright(C) π„÷› ––«“ÌµÁ◊”ø∆ºº”–œﬁπ´Àæ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 



//Õ‚≤ø÷–∂œ2∑˛ŒÒ≥Ã–Ú
void EXTI2_IRQHandler(void)
{ 
//	u16 i;
//	for(i=1000; i>0; i--);   //œ˚∂∂
	delay_ms(10);
	if(XR)
	{		
			TIM_Cmd(TIM1, DISABLE);	
      X0RSTOV = 1;					
			EXTI->IMR&=0xfffb; 	
//      if(Flag_run == 4)	
//			{
//					BELL=1;
//				  delay_ms(80);
//				  BELL=0;
//			}				
	}	
	EXTI_ClearITPendingBit(EXTI_Line2);//«Â≥˝LINE2…œµƒ÷–∂œ±Í÷æŒª 
}

//Õ‚≤ø÷–∂œ3∑˛ŒÒ≥Ã–Ú  
extern u8  Flag_run;
void EXTI3_IRQHandler(void)
{	
//  u16 i;
//	for(i=1000; i>0; i--);   //œ˚∂∂
	delay_ms(10);
	if(Y0R)
	{			  
			TIM_Cmd(TIM3, DISABLE);
			Y1RSTOV = 1;			 
			EXTI->IMR&=0xfff7; 
//      if(Flag_run == 4)	
//			{
//					BELL=1;
//				  delay_ms(80);
//				  BELL=0;
//			}		
  }
  EXTI_ClearITPendingBit(EXTI_Line3);  //«Â≥˝LINE3…œµƒ÷–∂œ±Í÷æŒª   	
}

//Õ‚≤ø÷–∂œ4∑˛ŒÒ≥Ã–Ú
void EXTI4_IRQHandler(void)
{
//	u16 i;
//	for(i=1000; i>0; i--);   //œ˚∂∂
	delay_ms(10);
	if(Y1L)
	{	
			TIM_Cmd(TIM8, DISABLE);
			Y2RSTOV = 1;		 
			EXTI->IMR&=0xffef;		
//      if(Flag_run == 4)	
//			{
//					BELL=1;
//				  delay_ms(80);
//				  BELL=0;
//			}		
	} 	
	EXTI_ClearITPendingBit(EXTI_Line4);//«Â≥˝LINE4…œµƒ÷–∂œ±Í÷æŒª  
}


u8 TIM1_enable_door = 0;   //º«¬º£¨πÿ±’À˘”–µƒ∂® ±∆˜«∞£¨À˚√«ø™∆Ù|πÿ±’µƒ◊¥Ã¨
u8 TIM3_enable_door = 0;
u8 TIM8_enable_door = 0;
u8 suspend_vib_door;
extern u8 Flag_run;

extern u8 TIM1_enable_usart;
extern u8 TIM3_enable_usart;
extern u8 TIM8_enable_usart;
void EXTI9_5_IRQHandler(void)
{
	static u8 door_open=0;           //º«¬ºÕ‚≤ø÷–∂œ«∞µƒ◊¥Ã¨£¨¥Úø™¡À=1£¨ πÿ±’=0	
//	u16 i;
//	for(i=600; i>0; i--);   //œ˚∂∂
	delay_ms(10);
	if(DOOR == 1) 		 
	{
		if(Flag_run == 1)
		{			
			Send_Str(":dialogbox=5\r\n");
//			while(door==1)//…œ¥´∞≤±£
//				Send_Str(":dialogbox=5\r\n");
			//Send_Str(":door=1\r\n");
		}
			
		if((Flag_run == 4))                   //(Run_flag == 4,±Í÷æ“«∆˜’˝‘⁄‘À––)»Áπ˚≥Ã–Ú¥¶”⁄‘À––Ã¨£¨‘Ú∑¢ÀÕ£¨°∞‘À––÷–√≈¥Úø™°±£¨≤¢◊ˆ°∞‘›Õ£°±≤Ÿ◊˜
		{			
			Send_Str(":dialogbox=5\r\n");
		//	Send_Str(":door=1\r\n");
			Flag_run = 1;
    
			if(((TIM1->CR1 & TIM_CR1_CEN) == 1) )                   //≈–∂œπÿ±’À˘”–µƒ∂® ±∆˜«∞£¨TIM1 «∑Òø™∆Ù
				{
					TIM_Cmd(TIM1,DISABLE);											//TIM1_enable_doorœµ¡–±‰¡ø£¨±Íº«£¨ ’µΩ‘›Õ£√¸¡Ó«∞£¨∏˜∏ˆ∂® ±∆˜µƒø™∆Ù°¢πÿ±’◊¥Ã¨
					TIM1_enable_door = 1;
				}
				
			if(((TIM3->CR1 & TIM_CR1_CEN) == 1))
				{
					if(Vib == 1)                                     //≈–∂œ «∑Ò¥¶”⁄’Ò∂Ø◊¥Ã¨£¨»Áπ˚¥¶”⁄’Ò∂Ø◊¥Ã¨£¨‘ÚœÚ’∂Ø∫Ø ˝∑¢ÀÕ‘›Õ£±Íº«
					{
							suspend_vib_door = 1;		
					}	
					else
					{
							TIM_Cmd(TIM3,DISABLE);								
					}			
					TIM3_enable_door = 1;							
				}
				if(((TIM8->CR1 & TIM_CR1_CEN) == 1) )
				{
					TIM_Cmd(TIM8,DISABLE);
					TIM8_enable_door = 1;
				}				
		}		
		
	}			
		
//	if(DOOR == 0)
//	{
//		door_open = 0;
//		Send_Str(":door=0\r\n");
//	}	
	EXTI_ClearITPendingBit(EXTI_Line5);//«Â≥˝LINE5…œµƒ÷–∂œ±Í÷æŒª  
}


	   
//Õ‚≤ø÷–∂œ≥ı ºªØ≥Ã–Ú
//≥ı ºªØPE2~4,PA0Œ™÷–∂œ ‰»Î.

//PD0  PD1


void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	//KEY_Init(); //∞¥º¸∂‘”¶µƒIOø⁄≥ı ºªØ
  
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);// πƒ‹GPIOA,GPIOE ±÷”
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //KEY0 KEY1 KEY2∂‘”¶“˝Ω≈
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//∆’Õ® ‰»Îƒ£ Ω
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//…œ¿≠
  GPIO_Init(GPIOE, &GPIO_InitStructure);//≥ı ºªØGPIOE2,3,4

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);// πƒ‹SYSCFG ±÷”
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 ¡¨Ω”µΩ÷–∂œœﬂ2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 ¡¨Ω”µΩ÷–∂œœﬂ3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 ¡¨Ω”µΩ÷–∂œœﬂ4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);//PE5¡¨Ω”µΩ÷–∂œœﬂ5
	
	/* ≈‰÷√EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line =  EXTI_Line2 | EXTI_Line3|EXTI_Line4|EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//÷–∂œ ¬º˛
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //µ—ÿ¥•∑¢
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//÷–∂œœﬂ πƒ‹
  EXTI_Init(&EXTI_InitStructure);//≈‰÷√
	
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//Õ‚≤ø÷–∂œ2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//«¿’º”≈œ»º∂3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//◊””≈œ»º∂2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// πƒ‹Õ‚≤ø÷–∂œÕ®µ¿
  NVIC_Init(&NVIC_InitStructure);//≈‰÷√
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//Õ‚≤ø÷–∂œ3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//«¿’º”≈œ»º∂2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//◊””≈œ»º∂2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// πƒ‹Õ‚≤ø÷–∂œÕ®µ¿
  NVIC_Init(&NVIC_InitStructure);//≈‰÷√
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//Õ‚≤ø÷–∂œ4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//«¿’º”≈œ»º∂1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//◊””≈œ»º∂2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// πƒ‹Õ‚≤ø÷–∂œÕ®µ¿
  NVIC_Init(&NVIC_InitStructure);//≈‰÷√
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//Õ‚≤ø÷–∂œ5
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//«¿’º”≈œ»º∂1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//◊””≈œ»º∂2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// πƒ‹Õ‚≤ø÷–∂œÕ®µ¿
  NVIC_Init(&NVIC_InitStructure);//≈‰÷√
	   
}


void InitSwitch()
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);//??GPIOF??

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOD, &GPIO_InitStructure);//???
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOE, &GPIO_InitStructure);//???	

	Switch0 =1;
	Switch1 =1;
	Switch2 =1;
	Switch3 =1;
	Switch4 =1;
	Switch5 =1;
	Switch6 =1;
	Switch7 =1;
	
	BELL=0;
	UV =0;
	BAK =1;  
	FUN  =0;	
}









