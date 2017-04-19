#include "timer.h"
#include "usart.h"
#include "delay.h"
#include "moto.h"
#include "DeviceVibration.h"
#include "exti.h"
#include "128S085.h"
#include "adc.h"

//tim3 ch1  tim8 ch2
//PC6 PC7  PA8



//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define COUNTER_RESET   (u16)0

u8 Flag_Hatch =0;
 u32 Count_TIMER3_Interupter =0;
 
u8 ADCFlag=0;

u8 tim = 0;


//void ENC_Init(void)
//{
//  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
//  TIM_ICInitTypeDef TIM_ICInitStructure; 
//  GPIO_InitTypeDef GPIO_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//  

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
// 

//  
//  //GPIO_StructInit(&GPIO_InitStructure);
//  /* Configure PC.06,07 as encoder input */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);



//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  GPIO_PinAFConfig(GPIOA,GPIO_PinSource15,GPIO_AF_TIM2);
//  GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);
//  
//  /* Enable the TIM3 Update Interrupt */
////  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
////  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
////  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
////  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////  NVIC_Init(&NVIC_InitStructure);
//  
//  /* Timer configuration in Encoder mode */
//  TIM_DeInit(TIM2);
//  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//  
//  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling
//  TIM_TimeBaseStructure.TIM_Period = 160000;//0-600000计数自动翻转
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
//  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//  
//  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); //2倍计数  4倍计数
//  TIM_ICStructInit(&TIM_ICInitStructure);
//  TIM_ICInitStructure.TIM_ICFilter = 0;
//  TIM_ICInit(TIM2, &TIM_ICInitStructure);
//  
//  // Clear all pending interrupts
//  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
// // TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//	
//	
//	
//  //Reset counter
//  TIM2->CNT = COUNTER_RESET;
//  
//  // ENC_Clear_Speed_Buffer();
////  	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
////	/* TIM IT enable */
////	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//  TIM_Cmd(TIM2, ENABLE);
//}

void Tim2Config(void)
{
    
    TIM_TimeBaseInitTypeDef         TIM_TimeBaseInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
   
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    
    TIM_TimeBaseInitStructure.TIM_Prescaler=42-1; //2M;
    
    TIM_TimeBaseInitStructure.TIM_Period=199;   //10us; 44
    
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
   
    TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
}


unsigned char DialogBoxT1[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x31,0x64,0x35,0x0D,0x0A,'\0'};  //加热模块1 超温
unsigned char DialogBoxT2[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x32,0x64,0x34,0x0D,0x0A,'\0'};
unsigned char DialogBoxT3[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x33,0x64,0x33,0x0D,0x0A,'\0'};
unsigned char DialogBoxT4[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x34,0x64,0x32,0x0D,0x0A,'\0'};
unsigned char DialogBoxT5[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x35,0x64,0x31,0x0D,0x0A,'\0'};
unsigned char DialogBoxT6[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x36,0x64,0x30,0x0D,0x0A,'\0'};
unsigned char DialogBoxT7[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x37,0x64,0x2f,0x0D,0x0A,'\0'};
unsigned char DialogBoxT8[17] = {0x3A,0x64,0x69,0x61,0x6C,0x6F,0x67,0x62,0x6F,0x78,0x3D,0x38,0x64,0x2e,0x0D,0x0A,'\0'};
	
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///??TIM3??
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//???TIM5
	
  TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
	//TIM_ClearITPendingBit(TIM5,TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //?????3????
	TIM_Cmd(TIM5,ENABLE); //?????3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x1; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


//u32 FilterValue[8];
extern u16 MotorY1Vib_t;
extern u8 uart_lock_tim5;
extern u16 fun_tim;
extern u8 Flag_run;
extern char SendBackBuff[20];
void TIM5_IRQHandler(void)
{	
	static u8 sk;
	
	static u8 timcunt=0;
	unsigned char s[5]={0};
	float temp;
	u8 j;	
	
	
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //????
	{
		
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //???????  
		 if((TIM3->CR1 & TIM_CR1_CEN) == 1)
				MotorY1Vib_t++;  //@刘永涛 ，为MotorY1Vib函数 计时
		 
		 
		  timcunt ++;
		 if(Flag_run == 4)
		   fun_tim++;
		 if(JRFlag)
		 {
		  JRTime++;
		 }
		
//		 if(timcunt ==1)
//		 {
		   if(FlagDMA)		
		   {
				 // 
				 if(uart_lock_tim5==0)
				 {
				 
					 switch(timcunt%9)
					 {
						 
							 case 0:
							 if(w0r==0)
							 {
								 sprintf(s,"%.1f",  28.0);
								 Package("t0k",s,SendBackBuff);
								 Send_Str(SendBackBuff);
								 break;
							 }
							 ad[7] = TableSearchTemperatures(filters(7),7);
//							 printf(":t0k=%.1f!\r\n", ad[7]);
							  sprintf(s,"%.1f", ad[7]);
								Package("t0k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break;
						 
						 case 1:
							 
							 if(w1r==0)
							 {
//								 printf(":t1k=%.1f!\r\n", 28.0);
								sprintf(s,"%.1f",  28.0);
								Package("t1k",s,SendBackBuff);
								Send_Str(SendBackBuff);
								 break;
							 }
							 ad[4] = TableSearchTemperatures(filters(4),4);
//							 printf(":t1k=%.1f!\r\n",ad[4]);
							 sprintf(s,"%.1f", ad[4]);
							  Package("t1k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break;
						 
						 case 2:
							 
							if(w2r==0)
							 {
//								 printf(":t2k=%.1f!\r\n", 28.0);
								sprintf(s,"%.1f",  28.0);
								Package("t2k",s,SendBackBuff);
								Send_Str(SendBackBuff);
								 break;
							 }
							ad[5] = TableSearchTemperatures(filters(5),5);
//							printf(":t2k=%.1f!\r\n",ad[5]);
							 sprintf(s,"%.1f", ad[5]);
								Package("t2k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break;
						 
						 case 3:
							 
							if(w3r==0)
							 {
//								 printf(":t3k=%.1f!\r\n", 28.0);
								 sprintf(s,"%.1f",  28.0);
								Package("t3k",s,SendBackBuff);
								Send_Str(SendBackBuff);
								 break;
							 }
							ad[6] = TableSearchTemperatures(filters(6),6);
//							printf(":t3k=%.1f!\r\n",ad[6]);
							 sprintf(s,"%.1f", ad[6]);
								Package("t3k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break;
						 
							case 4:
								
							 if(w4r==0)
							 {
//								 printf(":t4k=%.1f!\r\n", 28.0);
								 sprintf(s,"%.1f",  28.0);
								Package("t4k",s,SendBackBuff);
								Send_Str(SendBackBuff);
								 break;
							 }
							
							ad[3] = TableSearchTemperatures(filters(3),3);						
//							printf(":t4k=%.1f!\r\n",ad[3]);
							 sprintf(s,"%.1f", ad[3]);
								Package("t4k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break; 
							
							 case 5:
									
							 if(w5r==0)
							 {
//								 printf(":t5k=%.1f!\r\n", 28.0);
								 sprintf(s,"%.1f",  28.0);
								Package("t5k",s,SendBackBuff);
								Send_Str(SendBackBuff);
								 break;
							 }
							 ad[0] =TableSearchTemperatures(filters(0),0);
//							 printf(":t5k=%.1f!\r\n",ad[0]);
							 sprintf(s,"%.1f", ad[0]);
								Package("t5k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break;
						 
						 case 6:
								
							 if(w6r==0)
							 {
//								 printf(":t6k=%.1f!\r\n", 28.0);
								 sprintf(s,"%.1f", 28.0);
								Package("t6k",s,SendBackBuff);
								Send_Str(SendBackBuff);
								 break;
							 }
							 ad[1] = TableSearchTemperatures(filters(1),1);
//							 printf(":t6k=%.1f!\r\n", ad[1]);
							 sprintf(s,"%.1f", ad[1]);
								Package("t6k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break;
						 
						 case 7:
								
							 if(w7r==0)
							 {
//								 printf(":t7k=%.1f!\r\n", 28.0);
								 sprintf(s,"%.1f", 28.0);
								Package("t7k",s,SendBackBuff);
								Send_Str(SendBackBuff);
								 break;
							 }
							 ad[2] = TableSearchTemperatures(filters(2),2);
//							 printf(":t7k=%.1f!\r\n",ad[2]);
							 sprintf(s,"%.1f", ad[2]);
								Package("t7k",s,SendBackBuff);
								Send_Str(SendBackBuff);
							 break;
						 
						 case 8:

							 FlagDMA =0;
							 TIM_Cmd(TIM2, ENABLE);
							 break;

					 }
				 }
				 
//			  
//				filter();
//			 
//		    for(j=0;j<8;j++)
//			  {			
// 
//          ad[j]= TableSearchTemperatures(BDAdc[j],j);	
//          //printf(":t%dk=%.1f\r\n",j,ad[j]);  //{{{{{{{{{{{{{{{{{{{{{{{{
//				 
//			 }
//				
//		 }
	 }
	
//		 if(timcunt ==2)
//		 {
//			 
//			  printf(":t1k=%.1f\r\n:t2k=%.1f\r\n:t3k=%.1f\r\n:t4k=%.1f\r\n",ad[0],ad[1],ad[2],ad[3]);
//		 }
//		 
//		 if(timcunt ==3)
//		 {
//			 timcunt =0;
//		  printf(":t5k=%.1f\r\n:t6k=%.1f\r\n:t7k=%.1f\r\n:t0k=%.1f\r\n",ad[4],ad[5],ad[6],ad[7]);
//			 
//		//  printf(":t1k=%.1f\r\n:t2k=%.1f\r\n:t3k=%.1f\r\n:t4k=%.1f\r\n:t5k=%.1f\r\n:t6k=%.1f\r\n:t7k=%.1f\r\n:t0k=%.1f\r\n",50.0,51.0,52.0,53.0,54.0,60.1,61.1,62.1);  //{{{{{{{{{{{{{{{{{{{{{{{{
//		//	printf("%.1f ,%.1f ,%.1f ,%.1f ,\r\n",ad[0], ad[1],ad[2],ad[3]);
//			 
//			 TIM_Cmd(TIM2, ENABLE);
//		 }
		 
		 
//			 ad[0]= TableSearchTemperatures(BDAdc[0],0);
//			 ad[1]= TableSearchTemperatures(BDAdc[1],1);
//			 ad[2]= TableSearchTemperatures(BDAdc[2],2);
//			 ad[3]= TableSearchTemperatures(BDAdc[3],3);
//			
//			 ad[4]= TableSearchTemperatures(BDAdc[4],4);
//			 ad[5]= TableSearchTemperatures(BDAdc[5],5);
//			 ad[6]= TableSearchTemperatures(BDAdc[6],6);
//			 ad[7]= TableSearchTemperatures(BDAdc[7],7);
			
		 
		 
//	 }
		 
//		 else
//		 {
//			 
////		 if(w1r|w2r|w3r|w4r|w5r|w6r|w7r|w0r)
////		 {
//			   for(j=0;j<8;j++)
//			 {			

//          ad[j]= TableSearchTemperatures(BDAdc[j],j);	
//          printf(":t%dk=%.1f\r\n",j,ad[j]);  //{{{{{{{{{{{{{{{{{{{{{{{{
//				 
//			 }
//			 
//			// printf(":t%dk=%.1f\r\n",j,ad[j]);  //{{{{{{{{{{{{{{{{{{{{{{{{
//			 
//			 
//			 
//			 TIM_Cmd(TIM2, ENABLE);
//		 }

	//				TempNow[j]= TableSearchTemperature(j,FilterValue[j]);
				 
//					if((TempNow[j] >= 120) )                        //@刘永涛，高位报警，复位
//					{
//							switch (j)
//							{
//								case 0:
//									Send_Str(":dialogbox=1\n\r");
//									break;
//								case 1:
//									Send_Str(":dialogbox=2\n\r");
//									break;
//								case 2:
//									Send_Str(":dialogbox=3\n\r");
//									break;
//								case 3:
//									Send_Str(":dialogbox=4\n\r");
//									break;
//								case 4:
//									Send_Str(":dialogbox=5\n\r");
//									break;
//								case 5:
//									Send_Str(":dialogbox=6\n\r");
//									break;
//								case 6:
//									Send_Str(":dialogbox=7\n\r");
//									break;
//								case 7:
//									Send_Str(":dialogbox=8\n\r");
//									break;
//							}
////							EXTI->IMR|=1<<2;                       //需要复位了，打开中断
////							EXTI->IMR|=1<<3;
////							EXTI->IMR|=1<<4;
//							RunFlag =0;
//							Y1Y2Reset();
//							Switch0 =1;
//							Switch1 =1;
//							Switch2 =1;
//							Switch3 =1;
//							Switch4 =1;
//							Switch5 =1;
//							Switch6 =1;
//							Switch7 =1;
//              ErrorAlarm;
//							delay_ms(5000);
//							FUN=0;	
//							__set_FAULTMASK(1);
//							NVIC_SystemReset();

//					}					
//					if((TempNow[j]>=27)) //
//					{		
       //      printf(":t%dk=%.1f\r\n",j,ad[j]);  //{{{{{{{{{{{{{{{{{{{{{{{{
//						 if(abs(TempNow[j]-TempLast[j])>2)   //温度处理函数在阈值 
//						 {
//							 TempLast[j] = TempNow[j];
				//			 printf(":t%dk=%.1f\r\n",j,TempLast[j]);
//   					 }
//			
//					}      			 
	//			} 
			 
				
				
				
				
			 

		 
		
		 
		 
	 }
	 
}


