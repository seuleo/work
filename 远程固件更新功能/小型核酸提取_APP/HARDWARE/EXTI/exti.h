#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
							  
////////////////////////////////////////////////////////////////////////////////// 	 

//sbit X_EN  = P7^2;
//sbit YB_EN  = P7^3;
//sbit YT_EN  = P7^4;
//sbit X_DIR  = P7^5;
//sbit YB_DIR  = P7^6;
//sbit YT_DIR  = P7^7;

//#define X_EN PAout(12)	// DS1	  X ,Y moto  enable io and  direction io 
//#define YB_EN PCout(9)	// DS0
//#define YT_EN PDout(14)	// DS1	 


//#define X_DIR PFout(11)	// DS0


//#define YB_DIR PCout(8)	// DS1	 
//#define YT_DIR PDout(15)	// DS0


//sbit CEX0=P0^2;   //MOTO PWM口 
//sbit CEX1=P0^3;
//sbit CEX2=P0^4;


//sbit BELL  = P3^0;
//sbit  FUN = P3^4;
//sbit  UV = P3^5;
//sbit  BAK = P3^6;

#define XR 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
#define Y0R   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
#define Y1L   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4   //一开始是低电平；
#define DOOR  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) 

//#define Y1L 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) //PE4

#define DL 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) //PE4



//read  

//sbit  DL = P5^0;
//sbit  Y1L = P5^2;
//sbit  Y1R = P5^3;
//sbit  Y0R = P5^5;
//sbit  XR = P5^7;

extern u32 AB_cnt;
extern u16 Current_zcnt;
extern u16 Z_cnt ;


void EXTIX_Init(void);	//外部中断初始化		 		
//void EXTIX_Disable(void);
//void EXTIX_Enable(void);

void InitSwitch();


//#define Switch0 PDout(0)	 //
//#define Switch1 PDout(1)	 //
//#define Switch2 PDout(2)	 //
//#define Switch3 PDout(3)	 //
//#define Switch4 PDout(4)	 //
//#define Switch5 PDout(5)	 //
//#define Switch6 PDout(6)	 //
//#define Switch7 PDout(7)	 //


#define Switch0 PDout(7)	 //
#define Switch1 PDout(4)	 //
#define Switch2 PDout(5)	 //
#define Switch3 PDout(6)	 //
#define Switch4 PDout(3)	 //
#define Switch5 PDout(0)	 //
#define Switch6 PDout(1)	 //
#define Switch7 PDout(2)	 //




#define UV  PDout(9)
#define BAK  PDout(8)
#define FUN   PDout(10)

#define BELL   PEout(0)




#endif

























