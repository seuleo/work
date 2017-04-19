#include "pwm.h"
#include "moto.h"
#include "exti.h"
#include "can.h"
#include "delay.h"
#include "DeviceVibration.h"
#include "usart.h"
#include "exti.h"
#include "delay.h" 
#include "pwm.h"
#include "time.h"
#include "moto.h"
#include "usart.h"
#include "DeviceVibration.h"

//X轴在运行过程中进行了加减速的启动运行；Y2 直接低速运行； Y1在不振荡的情况下低速运行，振荡时分为40个加减速点振荡；

#define XFRE 2000000
#define X2FRE 4000000
#define Y1FRE 2000000
#define Y2FRE 2000000 

#define XXF 3200
#define YXF 1600

#define X_right 1
#define X_left  0


u16 XACC[XACCNUM]={12846,12784,12715,12638,12551,12455,12349,12230,12100,11955,11797,11623,11434,11228,11005,10765,10509,10235,9946,9642,9324,8995,8656,8309,
	7957,7603,7250,6900,6556,6220,5894,5581,5282,4998,4731,4480,4247,4030,3830,3646,3478,3324,3185,3059,2945,2842,2749,2666,2592,2526,2466,2414,2367,2325,2287,
	2254,2225,2199,2176,2155,2137,2121,2107,2095,2084,2074,2065,2057,2051,2045,2039,2035,2031,2027,2024,2021,2018,2016,2014,2012};
 

	
	//X轴加减速速度表格；
 u16 XACCReset[XACCNUM]={7720,7685,7645,7601,7551,7496,7435,7367,7291,7208,7116,7016,6906,6787,6657,6518,6368,6209,6040,5861,5675,5481,5280,5075,4867,4656,
	 4445,4236,4030,3828,3632,3443,3262,3090,2927,2775,2632,2500,2377,2265,2162,2067,1982,1904,1834,1770,1713,1662,1616,1575,1539,1506,1477,1451,1428,1407,
	 1389,1373,1359,1346,1335,1325,1316,1308,1302,1296,1290,1285,1281,1277,1274,1271,1269,1267,1265,1263,1261,1260,1259,1258};  


//u16 YACC[6][YACCNUM]={
//	                   //   {9986,9970,9934,9854,9683,9328,8645,7503,5981,4464,3333,2659,2310,2142,2064,2029,2013,2005,2002,2001},//1000
//	                   //  {9978,9951,9893,9766,9496,8953,7970,6490,4780,3316,2352,1823,1560,1436,1380,1354,1342,1337,1335,1334}, //1500                                                                                                     //1500
//	                    {9431,9100,8606,7912,7008,5942,4824,3785,2923,2273,1818,1514,1319,1196,1120,1073,1044,1027,1016,1009},//2000
//										  {9143,8666,7988,7090,6009,4849,3746,2813,2098,1590,1250,1029,890,803,750,717,697,685,678,673}, //3000 
//                      {8871,8272,7453,6422,5260,4096,3062,2239,1636,1223,952,779,671,604,563,538,523,514,508,505},  //4000
//										//	{9928,9842,9655,9266,8507,7211,5428,3586,2168,1304,851,631,529,482,461,452,447,446,445,444},  //4500
//                      {8616,7913,6984,5870,4676,3545,2590,1859,1341,993,769,627,539,484,451,431,419,411,407,404},   //5000
//											{8374,7583,6572,5405,4209,3125,2243,1589,1136,836,645,524,450,404,376,359,349,343,339,336},  //6000
//											{8146,7280,6205,5008,3827,2793,1979,1388,985,722,555,451,386,347,323,308,299,294,290,288},//7000
////											{8146,7280,6205,5008,3827,2793,1979,1388,985,722,555,451,386,347,323,308,299,294,290,288},//7000
////                      {3548,3309,2981,2569,2104,1638,1225,895,654,489,380,311,268,241,225,215,209,205,203,201},
////											{2471,2442,2387,2284,2103,1819,1444,1045,709,477,338,262,222,202,192,186,184,183,182,182},
//////											{2468,2437,2377,2265,2071,1772,1386,989,663,442,312,241,204,185,176,171,168,167,167,166},
////											{2465,2432,2367,2246,2040,1727,1333,938,622,412,289,223,188,171,162,158,156,154,154,154},
////											{2462,2426,2356,2228,2010,1685,1284,892,586,386,270,207,175,159,151,146,144,143,143,143}
//////                      											
////										};  //7000 -6000  9000 8000

										
u16 YACC[6][YACCNUM]={
//	                   //   {9986,9970,9934,9854,9683,9328,8645,7503,5981,4464,3333,2659,2310,2142,2064,2029,2013,2005,2002,2001},//1000
//	                   //  {9978,9951,9893,9766,9496,8953,7970,6490,4780,3316,2352,1823,1560,1436,1380,1354,1342,1337,1335,1334}, //1500                                                                                                     //1500
	                    {6574,6423,6050,5254,3978,2641,1739,1296,1112,1042,1015,1005},//2000
										  {6521,6287,5737,4672,3216,1949,1212,879,746,696,677,670}, //3000 
                      {6469,6158,5456,4206,2698,1544,930,665,561,522,508,503},  //4000
//										//	{9928,9842,9655,9266,8507,7211,5428,3586,2168,1304,851,631,529,482,461,452,447,446,445,444},  //4500
                      {6418,6033,5201,3824,2324,1278,754,535,450,418,406,402},   //5000
											{6367,5914,4968,3506,2041,1091,634,447,375,349,339,335},  //6000
											{6317,5799,4756,3237,1820,951,547,384,322,299,290,287},//7000
//											{8146,7280,6205,5008,3827,2793,1979,1388,985,722,555,451,386,347,323,308,299,294,290,288},//7000
//                      {3548,3309,2981,2569,2104,1638,1225,895,654,489,380,311,268,241,225,215,209,205,203,201},
//											{2471,2442,2387,2284,2103,1819,1444,1045,709,477,338,262,222,202,192,186,184,183,182,182},
////											{2468,2437,2377,2265,2071,1772,1386,989,663,442,312,241,204,185,176,171,168,167,167,166},
//											{2465,2432,2367,2246,2040,1727,1333,938,622,412,289,223,188,171,162,158,156,154,154,154},
//											{2462,2426,2356,2228,2010,1685,1284,892,586,386,270,207,175,159,151,146,144,143,143,143}
//                      											
										};  //7000 -6000  9000 8000
										
										
										
										
u8 Y1SFlag=0;

u8 XResetFlag =0;		
u8 Y1ResFlag=0;
u8 Y2ResFlag=0;										
 	 
u16 Y1Y2ACC[6]={30,40,50,60,70,80}; 

u16 YACCReset[YACCNUM]={0};

speedRampData srdx,srd1y,srd2y;


u8 Y1RSTOV=0;
u8 Y2RSTOV=0;
u8 X0RSTOV=0;
u8 Y1Y2RSTOV=0;
u8 RSTALARM=0;
u8 door=0;

u8 Vib=0;

u8 XStopFlag=1;
u8 YStopFlag=1;
extern  u8 Flag_run;
 
 void MotorX0Mov(u8 direction,u16 frequency,u32 distance)
 {
	 	
	X_DIR = direction;
	X_EN = 0;
	XResetFlag =1;
//X 轴====0 偏移量；；
	if(distance)
	{
		if(distance >X3ACCNUM)
		{
			srdx.run_start=XACCNUM-1;
			srdx.decel_start=distance-XACCNUM-1;
			srdx.run_state=ACCEL;
			srdx.step_delay = XACC[0];		
		}
		else
		{
			srdx.run_state=LRUN;
			srdx.step_delay = XACC[5];		
		}	

		srdx.dir = direction;
		srdx.accel_count =distance;
		TIM1->CCR1=srdx.step_delay/2;
		TIM1->ARR=srdx.step_delay;
		//ile(Flag_run)
		while(Flag_run == 1);
		TIM_Cmd(TIM1, ENABLE); 
		XStopFlag=1; 
		while(XStopFlag);
 }
}
 
 void MotorY1Mov(u8 direction,u16 frequency,u16 distance)
 {
	 
		YB_DIR = direction;
		YB_EN = 0;
		Y1ResFlag=1;
		 
		TIM3->ARR= XFRE/frequency;  
		TIM3->CCR2= TIM3->ARR/2; 
	  while(Flag_run == 1);
		TIM_Cmd(TIM3, ENABLE);  
		PWMY1_Num=0;
		 
		 
		while(PWMY1_Num<distance);
		PWMY1_Num = 0;
	  
		TIM_Cmd(TIM3, DISABLE);  
 }
 
 void MotorY2Mov(u8 direction,u16 frequency,u16 distance)
 {

		YT_DIR = direction;
		YT_EN = 0;
		Y2ResFlag	 =1;
		 
		TIM8->ARR= XFRE/frequency;  
		TIM8->CCR1= TIM8->ARR/2;
    while(Flag_run == 1);	 
		TIM_Cmd(TIM8, ENABLE);  
		PWMY2_Num=0;
		while(PWMY2_Num<distance);
		PWMY2_Num = 0;
		TIM_Cmd(TIM8, DISABLE);
 }
 
 u8 Y1Y2_state; 
 void MotorY1Y2Mov(u8 direction,u16 frequency,u16 distance)
 {
	 
    
		u8 tFlag =2;
		Y1ResFlag =1;
		Y2ResFlag =1;
	 
	  Y1Y2_state=1;
		switch(frequency)
		{		
			case 1:
				frequency = 50;  //80  90 100 100 110 120 
		 	break;
			case 2:
				frequency = 60;
				break;
			case 3:
				frequency = 70;
				break;
			case 4:
				frequency = 80;
				break;
			case 5:
				frequency = 90;
				break;
			case 6:
				frequency = 100;
				break;
			default:
				frequency = 80;		
				break;		
		}
	

		YB_DIR = direction;
		YT_DIR = direction;
		YB_EN = 0;
		YT_EN = 0;	   		    
		PWMY1_Num = 0;
		PWMY2_Num= 0;
		

		
		TIM3->ARR= XFRE/frequency;  
		TIM3->CCR2= TIM3->ARR/2; 
		while(Flag_run == 1);
		TIM_Cmd(TIM3, ENABLE);
		
		
		
		TIM8->ARR= XFRE/frequency;  
		TIM8->CCR1= TIM8->ARR/2; 
		while(Flag_run == 1);
		TIM_Cmd(TIM8, ENABLE);  
		

		while(tFlag)
		{	
			if(PWMY1_Num>distance-1)	
			{
				PWMY1_Num = 0;
				TIM_Cmd(TIM3, DISABLE);	
				tFlag--;
			}
			if(PWMY2_Num>distance-1)
			{
				PWMY2_Num= 0;
				TIM_Cmd(TIM8, DISABLE);
				tFlag--;
			}			
	 }
	 Y1Y2_state=0;
}
  
extern u8 suspend_vib_command;
extern u8 suspend_vib_door;

u16 MotorY1Vib_t = 0;
 void MotorY1Vib(u32 vib_v,u32 amp,u32 t)
 {
		u16 i = 0;
		u8 j = 0;
		static u32 times = 0;
		u32 a = 0;
		Y1ResFlag =1;

		switch(vib_v)
		{
			case 1:
				vib_v = 1000;
				Y1SFlag =0;
				break;
			case 2:
				vib_v = 1500;
				Y1SFlag =1;
				break;
			case 3:
				vib_v = 2000;
				Y1SFlag =2;
				break;
			case 4:
				vib_v = 3000;
				Y1SFlag =3;
				break;
			case 5:
				vib_v = 4000;
				Y1SFlag =4;
				break;
			case 6:
				vib_v = 4500;
				Y1SFlag =5;
				break;
			default:
				vib_v = 3000;		
				Y1SFlag =3;
				break;
		}

		switch(amp)
		{
			case 1:
				amp = 200;   //1/2
				break;
			case 2:
				amp = 250;
				break;
			case 3:
				amp = 300;
				break;
			case 4:
				amp = 350;
				break;
			case 5:
				amp = 400;
				break;
			case 6:
				amp = 450;
				break;
			default:
				amp = 300;		
				break;
		}

		YB_DIR = 1;
		Vib = 1;
	

		srd1y.accel_count = amp;
		srd1y.run_start=YACCNUM-1;
		srd1y.decel_start=amp-YACCNUM-1;
		
		YB_EN = 0;
		
		times = t*2;  //@刘永涛，计算计时t（s）,需要TIM5中断多少次
		
		
		MotorY1Vib_t = 0;   //@刘永涛，初始化MotorY1Vib_t，这个值为振动时间计时，在TIM5的中断处理中，改变，每次加一
		while(MotorY1Vib_t < times)
		{	
			TIM_Cmd(TIM3,DISABLE);
			while((suspend_vib_command==1)||(suspend_vib_door==1));              //判断是否收到暂停命令，如果收到，则等待暂停结束，suspend_vib在usart的暂停功能中改变
		//	TIM_Cmd(TIM3,ENABLE);
			
			
			YB_DIR = 1;  
			PWMY1_Num =0;	
			TIM3->CCR2=YACC[Y1SFlag][0]>>2;
			TIM3->ARR=YACC[Y1SFlag][0];
			srd1y.run_state=ACCEL;
			TIM_Cmd(TIM3, ENABLE);  
			while(srd1y.run_state !=STOP) ; //WAIT FOR MOTO 			
			TIM_Cmd(TIM3, DISABLE);  
			
			
			YB_DIR = 0;
			PWMY1_Num =0;
			TIM3->CCR2=YACC[Y1SFlag][0]>>2;
			TIM3->ARR=YACC[Y1SFlag][0];
			srd1y.run_state=ACCEL;
			TIM_Cmd(TIM3, ENABLE);
			while(srd1y.run_state !=STOP) ; //WAIT FOR MOTO 			
			TIM_Cmd(TIM3, DISABLE);  
			
			PWMY1_Num =0;
		}

		Vib = 0;
 }
 void MotorX0Reset(u8 direction,u16 frequency,u32 distance)
 {
	  u8 Flag_X = 0;
	  EXTI->IMR|=1<<2; 
//	  EXTI->IMR&=0<<2; 
	  X_DIR = direction;
	  X_EN = 0;
	  XResetFlag=0;
	 
	  X0RSTOV = 0;	
	 
	//StepWide0 = (SYSCLK/24/100 - SYSCLK/24/frequency)/160;	   		    //调整加减速级数
 	  srdx.run_start=XACCNUM-1;
	  srdx.decel_start=distance-XACCNUM-1;
		srdx.run_state=ACCEL;
	  srdx.step_delay = XACCReset[0];

		srdx.dir = direction;
		srdx.accel_count =distance;
		TIM1->CCR1=srdx.step_delay/2;
		TIM1->ARR=srdx.step_delay;
		TIM_Cmd(TIM1, ENABLE);     

 }
 
 
 
 void MotorY1Reset(u8 direction,u16 frequency,u16 distance)
 {
	  u8 Flag_Y1=0;
	  
    EXTI->IMR|=1<<3;	  
//	  EXTI->IMR&=0<<3; 
		YB_DIR = direction;
		YB_EN = 0;
		Y1ResFlag =0;
	 
		Y1RSTOV = 0;	
	 
		TIM3->ARR= Y1FRE/frequency;  
		TIM3->CCR2= TIM3->ARR>>2; 
			
//		if(Y0R==0)
//		{
				TIM_Cmd(TIM3, ENABLE);   
//		}
//		else
//		{			                            //如果在初始位置，则离开初始位置，运动一段距离，再返回初始位置
//				MotorY1Mov(0,400,700);	
//				YB_DIR = direction;
//				TIM_Cmd(TIM3,ENABLE);		
//		}	
	
 }
 
 
 void MotorY2Reset(u8 direction,u16 frequency,u16 distance)
 {
	  u8 Flag_Y2 = 0;
//	  u8 i = 200;
	  
	  EXTI->IMR|=1<<4;       //开启中断4
		YT_DIR = direction;
		YT_EN = 0;
		Y2ResFlag =0;
	 
		Y2RSTOV = 0;	
	 
		TIM8->ARR= Y1FRE/frequency;  
		TIM8->CCR1= TIM8->ARR>>2; 
//		while(i-- != 0);
//		if(Y1L==0)
//		{
			 TIM_Cmd(TIM8, ENABLE);
//		}
//		else
//		{			                        //如果在初始位置，则离开初始位置，运动一段距离，再返回初始位置
//				MotorY2Mov(0,400,400);	
//				YT_DIR = direction;
//				TIM_Cmd(TIM8,ENABLE);		
//		}  
		
 }
 
 
 
 void Y1Y2Reset(void)
 {	
    	 
		if((Y0R == 1)&&(Y1L == 1)) 
		{			  
			  MotorY1Mov(0,600,1000);
			  MotorY2Mov(0,600,600);	
			
			  MotorY2Reset(1,800,8000);
			  MotorY1Reset(1,800,8000);
			  	
		}
    else if((Y0R == 0)&&(Y1L == 0))
		{
			  MotorY2Reset(1,800,8000);
			  MotorY1Reset(1,800,8000);
		}
		else if((Y0R == 0)&&(Y1L == 1))  //???
		{ 
			 MotorY1Reset(1,800,8000);
       while(Y1RSTOV==0);
       MotorY1Mov(0,600,1000);			 
			 MotorY2Mov(0,600,600);	
			

			 MotorY2Reset(1,800,8000);	
			 MotorY1Reset(1,800,8000);				 
		}
		else if((Y0R == 1)&&(Y1L ==0))
		{
			 MotorY1Mov(0,600,1000);	
			 MotorY2Mov(0,600,400);	
		 
			 MotorY2Reset(1,800,8000);	
			 MotorY1Reset(1,800,8000);			   
			
		}
		RSTALARM = 1;	
	
	 
 }
 
 extern u8 Flag_run;
 void X0Reset(void)
 {	 
	  static u8 i;

		while(( Y1RSTOV== 0)||(Y2RSTOV == 0)) ;
 
		if(XR==1) 
				MotorX0Mov(X_right,600,6400); //4MM
		
		MotorX0Reset(X_left,600,36000);   //

	
		while(X0RSTOV == 0);
	
		PWMX_Num=0;
		
		X0RSTOV = 1;	
		
		ResetAlarm();				
		Flag_run =2;
			
 }

 void OverAlarm(void)
 {
	 u8 i;
	 for(i=0;i<4;i++)
	 {
	
			BELL=1;
			delay_ms(400);
			BELL=0;
			delay_ms(400);
	 }
	
	
 }
 
 void ResetAlarm(void)
 {	
		BELL=1;
		delay_ms(1000);
		BELL=0;		
 }
 
 void ErrorAlarm(void)
 {
    BELL=1;
		delay_ms(100);
		BELL=0;
		delay_ms(100);
	 
	  BELL=1;
		delay_ms(100);
		BELL=0;
		delay_ms(100);
	 
	  BELL=1;
		delay_ms(100);
		BELL=0;
		delay_ms(100);
 }



