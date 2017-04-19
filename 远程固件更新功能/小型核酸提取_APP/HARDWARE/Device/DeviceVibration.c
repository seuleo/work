#include "DeviceVibration.h"
//振荡


#include "string_deal.h" 
//#include "can.h"
////#include "DataDeal.h"
#include "moto.h"
//机械轴
#include "math.h"
#include "usart.h"
#include "stdio.h"
#include "delay.h" 
#include "exti.h"
#include "adc.h"
#include "128S085.h"


DeviceVibration VibrationX;	

 u8 RunFlag =0;
	
#define	DISTANCE_Y1_UP 1600  //3250
#define	V_Y1_UP 800
#define	DISTANCE_Y2_UP 1600

#define	V_Y2_UP 3800

#define V_Y2_D 800

#define	DISTANCE_Y1_DOWN 1600
#define	V_Y1_DOWN 800
#define	DISTANCE_Y1Y2 1600

#define SEPARATE_POS 0   //磁套和磁棒分离的位置   升到底部 磁棒快速分离  350

#define Y1_up 1
#define Y1_down 0
#define Y2_up 1
#define Y2_down 0
#define Y2Y1_up 1
#define Y2Y1_down 0
#define X_forward 1
#define X_backward  0


#define DistanceXY 500


//#define	DISTANCE_X0 3040

#define	DISTANCE_X0 7200    //9mm  
#define	V_X0 600
extern u8 Flag_run;

void MovProcess(void)
{
  u16 i;
	u16 Vibbottom0= (u16)vibbottom0*39.3;
	u16 Vibbottom1= (u16)vibbottom1*39.3;
  u16	Vibbottom2= (u16)vibbottom2*39.3;
	u16 Vibbottom3= (u16)vibbottom3*39.3;
	u16 Vibbottom4= (u16)vibbottom4*39.3;
	u16 Vibbottom5= (u16)vibbottom5*39.3;
	u16 Vibbottom6= (u16)vibbottom6*39.3;
	u16 Vibbottom7= (u16)vibbottom7*39.3;
	
	
	
	
	Send_Str(":s=1\r\n");
	
	RunFlag=1;
	
	// 风扇；
	// 风开；
	FUN  =1;
//	BAK  =1;

	Switch0=!w0r;
	Switch1=!w1r;
	Switch2=!w2r;
	Switch3=!w3r;
	Switch4=!w4r;
	Switch5=!w5r;
	Switch6=!w6r;
	Switch7=!w7r;
	
	
	
	
	
if(t0k&&t1k&&t2k&&t3k&&t4k&&t5k&&t6k&&t7k)
{

		Dac128S085_Vol(GetVoltageDACS(t0k,7),7);
		////Switch0=!w0r;
		Dac128S085_Vol(GetVoltageDACS(t1k,5),5);	

		Dac128S085_Vol(GetVoltageDACS(t2k,3),3);//		Dac128S085_Vol(1200,2);  
		//Switch2=!w2r;

		Dac128S085_Vol(GetVoltageDACS(t3k,1),1);

		//Switch3=!w3r;
		Dac128S085_Vol(GetVoltageDACS(t4k,4),4);//	Dac128S085_Vol(1200,4); 

		//Switch4=!w4r;
		Dac128S085_Vol(GetVoltageDACS(t5k,6),6);//	Dac128S085_Vol(1200,5); 
		//Switch5=!w5r;
		Dac128S085_Vol(GetVoltageDACS(t6k,0),0);

		//Switch6=!w6r;
		Dac128S085_Vol(GetVoltageDACS(t7k,2),2); 
	
	  delay_ms(2000);

//		while(
//					((abs(t0k - ad[7])>1)&&w0r)||
//					((abs(t4k - ad[4])>1)&&w1r)||
//					((abs(t1k - ad[5])>1)&&w2r)||
//					((abs(t5k - ad[6])>1)&&w3r)||
//					((abs(t2k - ad[3])>1)&&w4r)||
//					((abs(t6k - ad[0])>1)&&w5r)||
//					((abs(t3k - ad[1])>1)&&w6r)||
//					((abs(t7k - ad[2])>1)&&w7r)
//				 );
	
//	if(w0r == 1)
//	{
//		while(ad[7]+1 < t0k);
//	}
//  	if(w1r == 1)
//	{
//		while(ad[4]+1 < t4k);
//	}
//		if(w2r == 1)
//	{
//		while(ad[5]+1 < t1k);
//	}
//	
//		if(w3r == 1)
//	{
//		while(ad[6]+1 < t5k);
//	}
//	
//		if(w4r == 1)
//	{
//		while(ad[3]+1 < t2k);
//	}
//	
//		if(w5r == 1)
//	{
//		while(ad[0]+1 < t6k);
//	}
//		if(w6r == 1)
//	{
//		while(ad[1]+1 < t3k);
//	}
//		if(w7r == 1)
//	{
//		while(ad[2]+1 < t7k);
//	}





    JRFlag =1;
    while(JRTime<180);  //1分钟
  	JRTime=0;
  	JRFlag =0;
	
}
else
{
	
	//err;
}

	MotorX0Mov(X_forward,800,xdelt);  //1mm？？？？？？？？？？？？？？？？？？？？？？？？
	//裂解

//	Send_Str(WorkStatusBuf1);

	
	MotorY1Mov(Y1_down,V_Y1_DOWN,y1firstmov);      
	
  MotorY1Mov(Y1_up,V_Y1_UP,Vibbottom0);
	
	
	MotorY2Mov(Y2_down,800,y2firstmov);	
	
	MotorY1Vib(EEprom[0],EEprom[1],EEprom[2]);       
	//磁棒振动0
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom0);
	
	Delay(EEprom[3]);
	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
//	Send_Str_uart4(" liejie_end\r\n");

	//磁珠混匀
//	Send_Str_uart4(" cizhuhunyun_begining\r\n");
//	Send_Str(WorkStatusBuf2);
Send_Str(":h=1\r\n");
	MotorY1Mov(Y1_down,V_Y1_DOWN,DISTANCE_Y1_DOWN);
	
	  MotorY1Mov(Y1_up,800,Vibbottom1);
			
//	MotoY1Mov(Y1_up,800,(vibbottom1/(2.034*20))*1600);
	MotorY1Vib(EEprom[4],EEprom[5],EEprom[6]);                   //磁棒振动1
	Delay(EEprom[3]);//
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom1);
	Delay(EEprom[7]);
	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[8]);
	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[9]);
	MotorX0Mov(X_backward,V_X0,DISTANCE_X0);  ///????????????????
//  Send_Str_uart4(" cizhuhunyun_end\r\n");
	//结合
//	Send_Str_uart4(" jiehe_beging\r\n");
	//Send_Str(WorkStatusBuf3);
	Send_Str(":j=1\r\n");
	/*----------------------------------------*/
   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
   //Delay(5); 
	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
	 
	 MotorY1Mov(Y1_up,800,Vibbottom2);
	 
	 //	MotoY1Mov(Y1_up,800,(vibbottom2/(2.034*20))*1600);  //39.33136676499508
		
		
	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
/*----------------------------------------*/	



	MotorY1Vib(EEprom[11],EEprom[12],EEprom[13]);                 //磁棒振动2
	
	Delay(EEprom[3]);//
	
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom2);
	Delay(EEprom[14]);
	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[15]);
	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[16]);
	MotorX0Mov(X_forward,V_X0,DISTANCE_X0*2);   //x zhou budong 
//	Send_Str_uart4(" jiehe_end\r\n");
	
////	TC1 = 0;  增加关闭4路继电器
////	TC3 = 0;


	// 洗涤1
//	Send_Str_uart4(" xidi1_begining\r\n");
//	Send_Str(WorkStatusBuf4);
Send_Str(":w1=1\r\n");
/*----------------------------------------*/
   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
   //Delay(5); 
	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
	 
	  MotorY1Mov(Y1_up,800,Vibbottom3);
/*----------------------------------------*/	
//	MotoY1Mov(Y1_up,800,(vibbottom3/(2.034*20))*1600);
	MotorY1Vib(EEprom[17],EEprom[18],EEprom[19]);	                //磁棒振动3
	Delay(EEprom[3]);//	
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom3);
	Delay(EEprom[20]);
	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[21]);
	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[22]);
	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
//	Send_Str_uart4(" xidi1_end\r\n");
	// 洗涤2
//	Send_Str_uart4(" xidi2_begining\r\n");
//	Send_Str(WorkStatusBuf5);
Send_Str(":w2=1\r\n");
/*----------------------------------------*/
   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
   //Delay(5); 
	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
	 
	 MotorY1Mov(Y1_up,800,Vibbottom4);
/*----------------------------------------*/	
//	MotoY1Mov(Y1_up,800,(vibbottom4/(2.034*20))*1600);
	MotorY1Vib(EEprom[23],EEprom[24],EEprom[25]);	               //磁棒振动4
	Delay(EEprom[3]);//	
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom4);
	Delay(EEprom[26]);
	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[27]);
	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[28]);
	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
//  Send_Str_uart4(" xidi2_end\r\n");
	//洗涤3
//	Send_Str_uart4(" xidi3_beginging\r\n");
//	Send_Str(WorkStatusBuf6);
Send_Str(":w3=1\r\n");
/*----------------------------------------*/
   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
   //Delay(5); 
	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
	  MotorY1Mov(Y1_up,800,Vibbottom5);
/*----------------------------------------*/	
//	MotoY1Mov(Y1_up,800,(vibbottom5/(2.034*20))*1600);
	MotorY1Vib(EEprom[29],EEprom[30],EEprom[31]);                //磁棒振动5
	
	Delay(EEprom[3]);//
	
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom5);
	Delay(EEprom[32]);
	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[33]);
	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[34]);
	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
//  Send_Str_uart4(" xidi3_end\r\n");
	//洗脱
//	Send_Str_uart4(" xituo_begining\r\n");
//	Send_Str(WorkStatusBuf7);
	Send_Str(":t=1\r\n");
/*----------------------------------------*/
   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
   //Delay(5); 
	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
	 
	 MotorY1Mov(Y1_up,800,Vibbottom6);
	 
/*----------------------------------------*/	
//	MotoY1Mov(Y1_up,800,(vibbottom6/(2.034*20))*1600);
	MotorY1Vib(EEprom[35],EEprom[36],EEprom[37]);               //磁棒振动6
	
	Delay(EEprom[3]);//
	
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom6);
	Delay(EEprom[38]);
	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[39]);
	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
	Delay(EEprom[40]);
	MotorX0Mov(X_backward,V_X0,DISTANCE_X0); //放到第二个工位，距离X4
//  Send_Str_uart4(" xituo_end\r\n");

////	TC2 = 0;  继续关闭其他几路
////	TC4 = 0;

	//磁珠释放
//	Send_Str_uart4(" cizhushifang_begining\r\n");
//	Send_Str(WorkStatusBuf8);
	Send_Str(":f=1\r\n");
	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
	MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP);
	 MotorY1Mov(Y1_up,800,Vibbottom7);
//	MotoY1Mov(Y1_up,800,(vibbottom7/(2.034*20))*1600);
	MotorY1Vib(EEprom[41],EEprom[42],EEprom[43]);              //磁棒振动7
	 
	Delay(EEprom[3]);//
	
	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom7);
//  Send_Str_uart4(" cizhushifang_end\r\n");
//	//结束


//	Y1Y2Reset();	
//	X0Reset();	
	

	//Send_Str_uart4(" end 1\r\n");
	Switch0 =1;
	Switch1 =1;
	Switch2 =1;
	Switch3 =1;
	Switch4 =1;
	Switch5 =1;
	Switch6 =1;
	Switch7 =1;	  //关闭继电器加热托盘	
	//Send_Str_uart4(" end 2\r\n");
	
//	for(i=30000;i>0;i--);      //延时	

  delay_ms(30000);	//风扇关闭需要延时一定的时间
	FUN  =0;	
	
	
	
	OverAlarm();
	Send_Str(":o=1\r\n");
	Flag_run=0;
	
  RunFlag =0;
	NVIC_SystemReset();
	
	
	
	//实验结束 切换 到磁套上升  
	//风扇延时 60秒 复位；
	
}




//void MovProcess(void)
//{
//  u16 i;
//	u16 Vibbottom0= (u16)vibbottom0*39.3;
//	u16 Vibbottom1= (u16)vibbottom1*39.3;
//  u16	Vibbottom2= (u16)vibbottom2*39.3;
//	u16 Vibbottom3= (u16)vibbottom3*39.3;
//	u16 Vibbottom4= (u16)vibbottom4*39.3;
//	u16 Vibbottom5= (u16)vibbottom5*39.3;
//	u16 Vibbottom6= (u16)vibbottom6*39.3;
//	u16 Vibbottom7= (u16)vibbottom7*39.3;
//	
//	
//	
//	
//	Send_Str(":s=1\r\n");
//	RunFlag=1;
//	
//	// 风扇；
//	// 风开；
//	FUN  =1;
////	BAK  =1;

//	Switch0=!w0r;
//	Switch1=!w1r;
//	Switch2=!w2r;
//	Switch3=!w3r;
//	Switch4=!w4r;
//	Switch5=!w5r;
//	Switch6=!w6r;
//	Switch7=!w7r;
//	
//	
//if(t0k&&t1k&&t2k&&t3k&&t4k&&t5k&&t6k&&t7k)
//{
//		Dac128S085_Vol(GetVoltageDACS(t0k,0),0);
//		////Switch0=!w0r;
//		Dac128S085_Vol(GetVoltageDACS(t1k,1),1);	

//		Dac128S085_Vol(GetVoltageDACS(t2k,2),2);//		Dac128S085_Vol(1200,2);  
//		//Switch2=!w2r;

//		Dac128S085_Vol(GetVoltageDACS(t3k,3),3);

//		//Switch3=!w3r;
//		Dac128S085_Vol(GetVoltageDACS(t4k,4),4);//	Dac128S085_Vol(1200,4); 

//		//Switch4=!w4r;
//		Dac128S085_Vol(GetVoltageDACS(t5k,5),5);//	Dac128S085_Vol(1200,5); 
//		//Switch5=!w5r;
//		Dac128S085_Vol(GetVoltageDACS(t6k,6),6);

//		//Switch6=!w6r;
//		Dac128S085_Vol(GetVoltageDACS(t7k,7),7); 
//	
//	
////			Dac128S085_Vol(GetVoltageDACS(t0k,7),7);
////		////Switch0=!w0r;
////		Dac128S085_Vol(GetVoltageDACS(t1k,5),5);	

////		Dac128S085_Vol(GetVoltageDACS(t2k,3),3);//		Dac128S085_Vol(1200,2);  
////		//Switch2=!w2r;

////		Dac128S085_Vol(GetVoltageDACS(t3k,1),1);

////		//Switch3=!w3r;
////		Dac128S085_Vol(GetVoltageDACS(t4k,4),4);//	Dac128S085_Vol(1200,4); 

////		//Switch4=!w4r;
////		Dac128S085_Vol(GetVoltageDACS(t5k,6),6);//	Dac128S085_Vol(1200,5); 
////		//Switch5=!w5r;
////		Dac128S085_Vol(GetVoltageDACS(t6k,0),0);

////		//Switch6=!w6r;
////		Dac128S085_Vol(GetVoltageDACS(t7k,2),2); 
//	
//	
//  JRFlag =1;
//  while(JRTime<10);  //1分钟
//	JRTime=0;
//	JRFlag =0;
//	
//}
//else
//{
//	
//	//err;
//}
//	


////	

//	

//	
//	
//	
//	
//	MotorX0Mov(X_forward,800,xdelt);  //1mm？？？？？？？？？？？？？？？？？？？？？？？？
//	//裂解
//	//Send_Str_uart4(" liejie_beging\r\n");
////	Send_Str(WorkStatusBuf1);


//	
//	MotorY1Mov(Y1_down,V_Y1_DOWN,y1firstmov);      
//	
//  MotorY1Mov(Y1_up,V_Y1_UP,Vibbottom0);
//	
//	
//	MotorY2Mov(Y2_down,800,y2firstmov);	
//	
//	MotorY1Vib(EEprom[0],EEprom[1],EEprom[2]);       
//	//磁棒振动0
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom0);
//	
//	Delay(EEprom[3]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////	Send_Str_uart4(" liejie_end\r\n");

//	//磁珠混匀
////	Send_Str_uart4(" cizhuhunyun_begining\r\n");
////	Send_Str(WorkStatusBuf2);
//Send_Str(":h=1\r\n");
//	MotorY1Mov(Y1_down,V_Y1_DOWN,DISTANCE_Y1_DOWN);
//	
//	  MotorY1Mov(Y1_up,800,Vibbottom1);
//			
////	MotoY1Mov(Y1_up,800,(vibbottom1/(2.034*20))*1600);
//	MotorY1Vib(EEprom[4],EEprom[5],EEprom[6]);                   //磁棒振动1
//	Delay(EEprom[3]);//
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom1);
//	Delay(EEprom[7]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[8]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[9]);
//	MotorX0Mov(X_backward,V_X0,DISTANCE_X0);  ///????????????????
////  Send_Str_uart4(" cizhuhunyun_end\r\n");
//	//结合
////	Send_Str_uart4(" jiehe_beging\r\n");
//	//Send_Str(WorkStatusBuf3);
//	Send_Str(":j=1\r\n");
//	/*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
//	 
//	 MotorY1Mov(Y1_up,800,Vibbottom2);
//	 
//	 //	MotoY1Mov(Y1_up,800,(vibbottom2/(2.034*20))*1600);  //39.33136676499508
//		
//		
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
///*----------------------------------------*/	



//	MotorY1Vib(EEprom[11],EEprom[12],EEprom[13]);                 //磁棒振动2
//	
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom2);
//	Delay(EEprom[14]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[15]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[16]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0*2);   //x zhou budong 
////	Send_Str_uart4(" jiehe_end\r\n");
//	
//////	TC1 = 0;  增加关闭4路继电器
//////	TC3 = 0;


//	// 洗涤1
////	Send_Str_uart4(" xidi1_begining\r\n");
////	Send_Str(WorkStatusBuf4);
//Send_Str(":w1=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
//	 
//	  MotorY1Mov(Y1_up,800,Vibbottom3);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom3/(2.034*20))*1600);
//	MotorY1Vib(EEprom[17],EEprom[18],EEprom[19]);	                //磁棒振动3
//	Delay(EEprom[3]);//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom3);
//	Delay(EEprom[20]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[21]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[22]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////	Send_Str_uart4(" xidi1_end\r\n");
//	// 洗涤2
////	Send_Str_uart4(" xidi2_begining\r\n");
////	Send_Str(WorkStatusBuf5);
//Send_Str(":w2=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
//	 
//	 MotorY1Mov(Y1_up,800,Vibbottom4);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom4/(2.034*20))*1600);
//	MotorY1Vib(EEprom[23],EEprom[24],EEprom[25]);	               //磁棒振动4
//	Delay(EEprom[3]);//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom4);
//	Delay(EEprom[26]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[27]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[28]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////  Send_Str_uart4(" xidi2_end\r\n");
//	//洗涤3
////	Send_Str_uart4(" xidi3_beginging\r\n");
////	Send_Str(WorkStatusBuf6);
//Send_Str(":w3=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
//	  MotorY1Mov(Y1_up,800,Vibbottom5);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom5/(2.034*20))*1600);
//	MotorY1Vib(EEprom[29],EEprom[30],EEprom[31]);                //磁棒振动5
//	
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom5);
//	Delay(EEprom[32]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[33]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[34]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////  Send_Str_uart4(" xidi3_end\r\n");
//	//洗脱
////	Send_Str_uart4(" xituo_begining\r\n");
////	Send_Str(WorkStatusBuf7);
//	Send_Str(":t=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-SEPARATE_POS);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-SEPARATE_POS);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,SEPARATE_POS);
//	 
//	 MotorY1Mov(Y1_up,800,Vibbottom6);
//	 
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom6/(2.034*20))*1600);
//	MotorY1Vib(EEprom[35],EEprom[36],EEprom[37]);               //磁棒振动6
//	
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom6);
//	Delay(EEprom[38]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[39]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[40]);
//	MotorX0Mov(X_backward,V_X0,DISTANCE_X0); //放到第二个工位，距离X4
////  Send_Str_uart4(" xituo_end\r\n");

//////	TC2 = 0;  继续关闭其他几路
//////	TC4 = 0;

//	//磁珠释放
////	Send_Str_uart4(" cizhushifang_begining\r\n");
////	Send_Str(WorkStatusBuf8);
//	Send_Str(":f=1\r\n");
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP);
//	 MotorY1Mov(Y1_up,800,Vibbottom7);
////	MotoY1Mov(Y1_up,800,(vibbottom7/(2.034*20))*1600);
//	MotorY1Vib(EEprom[41],EEprom[42],EEprom[43]);              //磁棒振动7
//	 
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP-Vibbottom7);
////  Send_Str_uart4(" cizhushifang_end\r\n");
////	//结束

//	OverAlarm();
//	Send_Str(":o=1\r\n");
//	Flag_run=0;
//  RunFlag =0;
////	Y1Y2Reset();	
////	X0Reset();	
//	

//	//Send_Str_uart4(" end 1\r\n");
//	Switch0 =1;
//	Switch1 =1;
//	Switch2 =1;
//	Switch3 =1;
//	Switch4 =1;
//	Switch5 =1;
//	Switch6 =1;
//	Switch7 =1;	  //关闭继电器加热托盘	
//	//Send_Str_uart4(" end 2\r\n");
//	
//	for(i=30000;i>0;i--);      //延时	
////	delay_ms(5000);	//风扇关闭需要延时一定的时间
//	FUN  =0;
//	NVIC_SystemReset();
//}




//void MovProcess(void)
//{
//  u16 i;
//	
//	Send_Str(":s=1\r\n");
//	RunFlag=1;
//	
//	// 风扇；
//	// 风开；
//	FUN  =1;
////	BAK  =1;
//	
//	//调整磁套和96孔板的横向距离
//	//MotorX0Mov(1,800,xdelt);  

////	 Switch0 =0; 
////  Switch1 =0;   //  打开8路继电器
////	Switch2 =0;
////	Switch3 =0;
////	Switch4 =0;
////	Switch5 =0;
////	Switch6 =0;
////	Switch7 =0;
//	
//	Switch0=!w0r;
//	Switch1=!w1r;
//	Switch2=!w2r;
//	Switch3=!w3r;
//	Switch4=!w4r;
//	Switch5=!w5r;
//	Switch6=!w6r;
//	Switch7=!w7r;
//	
//	
//Dac128S085_Vol(GetVoltageDACS(t0k,0),0);
//////Switch0=!w0r;
//Dac128S085_Vol(GetVoltageDACS(t1k,1),1);	

//Dac128S085_Vol(GetVoltageDACS(t2k,2),2);//		Dac128S085_Vol(1200,2);  
////Switch2=!w2r;

//Dac128S085_Vol(GetVoltageDACS(t3k,3),3);

////Switch3=!w3r;
//Dac128S085_Vol(GetVoltageDACS(t4k,4),4);//	Dac128S085_Vol(1200,4); 

////Switch4=!w4r;
//Dac128S085_Vol(GetVoltageDACS(t5k,5),5);//	Dac128S085_Vol(1200,5); 
////Switch5=!w5r;
//Dac128S085_Vol(GetVoltageDACS(t6k,6),6);

////Switch6=!w6r;
//Dac128S085_Vol(GetVoltageDACS(t7k,7),7); 
//	
//	
//	
//	
////Dac128S085_Vol(GetVoltageDACS(60,0),0);
//////Switch0=!w0r;
////Dac128S085_Vol(GetVoltageDACS(60,1),1);
//////Switch1=!w1r;
////Dac128S085_Vol(GetVoltageDACS(60,2),2);//		Dac128S085_Vol(1200,2);  
//////Switch2=!w2r;
////Dac128S085_Vol(GetVoltageDACS(60,3),3);
//////Switch3=!w3r;
////Dac128S085_Vol(GetVoltageDACS(60,4),4);//	Dac128S085_Vol(1200,4); 
//////Switch4=!w4r;
////Dac128S085_Vol(GetVoltageDACS(60,5),5);//	Dac128S085_Vol(1200,5); 
//////Switch5=!w5r;
////Dac128S085_Vol(GetVoltageDACS(60,6),6);
//////Switch6=!w6r;
////Dac128S085_Vol(GetVoltageDACS(60,7),7); 

//	
//	JRFlag =1;
//  while(JRTime<10);  //1分钟
//	JRTime=0;
//	JRFlag =0;
//	
//	
//	
//	
//	MotorX0Mov(X_forward,800,800);  //1mm？？？？？？？？？？？？？？？？？？？？？？？？
//	//裂解
//	//Send_Str_uart4(" liejie_beging\r\n");
////	Send_Str(WorkStatusBuf1);


//	MotorY1Mov(Y1_down,800,y1firstmov-500);      
////	MotoY1Mov(Y1_up,800,(vibbottom0/(2.034*20))*1600);
//	MotorY2Mov(Y2_down,800,y2firstmov-500);	
//	MotorY1Vib(EEprom[0],EEprom[1],EEprom[2]);                   //磁棒振动0
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
//	Delay(EEprom[3]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////	Send_Str_uart4(" liejie_end\r\n");

//	//磁珠混匀
////	Send_Str_uart4(" cizhuhunyun_begining\r\n");
////	Send_Str(WorkStatusBuf2);
//Send_Str(":h=1\r\n");
//	MotorY1Mov(Y1_down,V_Y1_DOWN,DISTANCE_Y1_DOWN);
////	MotoY1Mov(Y1_up,800,(vibbottom1/(2.034*20))*1600);
//	MotorY1Vib(EEprom[4],EEprom[5],EEprom[6]);                   //磁棒振动1
//	Delay(EEprom[3]);//
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
//	Delay(EEprom[7]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[8]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[9]);
//	MotorX0Mov(X_backward,V_X0,DISTANCE_X0);  ///????????????????
////  Send_Str_uart4(" cizhuhunyun_end\r\n");
//	//结合
////	Send_Str_uart4(" jiehe_beging\r\n");
//	//Send_Str(WorkStatusBuf3);
//	Send_Str(":j=1\r\n");
//	/*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-500);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-500);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,500);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom2/(2.034*20))*1600);
//	MotorY1Vib(EEprom[11],EEprom[12],EEprom[13]);                 //磁棒振动2
//	
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
//	Delay(EEprom[14]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[15]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[16]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0*2);   //x zhou budong 
////	Send_Str_uart4(" jiehe_end\r\n");
//	
//////	TC1 = 0;  增加关闭4路继电器
//////	TC3 = 0;


//	// 洗涤1
////	Send_Str_uart4(" xidi1_begining\r\n");
////	Send_Str(WorkStatusBuf4);
//Send_Str(":w1=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-500);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-500);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,500);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom3/(2.034*20))*1600);
//	MotorY1Vib(EEprom[17],EEprom[18],EEprom[19]);	                //磁棒振动3
//	Delay(EEprom[3]);//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
//	Delay(EEprom[20]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[21]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[22]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////	Send_Str_uart4(" xidi1_end\r\n");
//	// 洗涤2
////	Send_Str_uart4(" xidi2_begining\r\n");
////	Send_Str(WorkStatusBuf5);
//Send_Str(":w2=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-500);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-500);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,500);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom4/(2.034*20))*1600);
//	MotorY1Vib(EEprom[23],EEprom[24],EEprom[25]);	               //磁棒振动4
//	Delay(EEprom[3]);//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
//	Delay(EEprom[26]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[27]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[28]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////  Send_Str_uart4(" xidi2_end\r\n");
//	//洗涤3
////	Send_Str_uart4(" xidi3_beginging\r\n");
////	Send_Str(WorkStatusBuf6);
//Send_Str(":w3=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-500);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-500);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,500);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom5/(2.034*20))*1600);
//	MotorY1Vib(EEprom[29],EEprom[30],EEprom[31]);                //磁棒振动5
//	
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
//	Delay(EEprom[32]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[33]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[34]);
//	MotorX0Mov(X_forward,V_X0,DISTANCE_X0);
////  Send_Str_uart4(" xidi3_end\r\n");
//	//洗脱
////	Send_Str_uart4(" xituo_begining\r\n");
////	Send_Str(WorkStatusBuf7);
//	Send_Str(":t=1\r\n");
///*----------------------------------------*/
//   MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2-500);
//   //Delay(5); 
//	 MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP-500);
//	 MotorY1Mov(Y1_down,V_Y1_DOWN,500);
///*----------------------------------------*/	
////	MotoY1Mov(Y1_up,800,(vibbottom6/(2.034*20))*1600);
//	MotorY1Vib(EEprom[35],EEprom[36],EEprom[37]);               //磁棒振动6
//	
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
//	Delay(EEprom[38]);
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[39]);
//	MotorY1Y2Mov(Y2Y1_up,EEprom[10],DISTANCE_Y1Y2);
//	Delay(EEprom[40]);
//	MotorX0Mov(X_backward,V_X0,DISTANCE_X0);
////  Send_Str_uart4(" xituo_end\r\n");

//////	TC2 = 0;  继续关闭其他几路
//////	TC4 = 0;

//	//磁珠释放
////	Send_Str_uart4(" cizhushifang_begining\r\n");
////	Send_Str(WorkStatusBuf8);
//	Send_Str(":f=1\r\n");
//	MotorY1Y2Mov(Y2Y1_down,EEprom[10],DISTANCE_Y1Y2);
//	MotorY2Mov(Y2_up,V_Y2_UP,DISTANCE_Y2_UP);
////	MotoY1Mov(Y1_up,800,(vibbottom7/(2.034*20))*1600);
//	MotorY1Vib(EEprom[41],EEprom[42],EEprom[43]);              //磁棒振动7
//	 
//	Delay(EEprom[3]);//
//	
//	MotorY1Mov(Y1_up,V_Y1_UP,DISTANCE_Y1_UP);
////  Send_Str_uart4(" cizhushifang_end\r\n");
////	//结束

//	OverAlarm();
//	Send_Str(":o=1\r\n");
//	Flag_run=0;
//  RunFlag =0;
////	Y1Y2Reset();	
////	X0Reset();	
//	

//	//Send_Str_uart4(" end 1\r\n");
//	Switch0 =1;
//	Switch1 =1;
//	Switch2 =1;
//	Switch3 =1;
//	Switch4 =1;
//	Switch5 =1;
//	Switch6 =1;
//	Switch7 =1;	  //关闭继电器加热托盘	
//	//Send_Str_uart4(" end 2\r\n");
//	
//	for(i=30000;i>0;i--);      //延时	
////	delay_ms(5000);	//风扇关闭需要延时一定的时间
//	FUN  =0;
//	NVIC_SystemReset();
//}

void Delay(u16 t)
{
	
	delay_ms(t*1000);
	
}




