#ifndef __MOTO_H
#define __MOTO_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
typedef struct {
  //! What part of the speed ramp we are in.
  u8 run_state ;
  //! Direction stepper motor should move.
  u8 dir ;
  //! Peroid of next timer delay. At start this value set the accelration rate.
  u16 step_delay;
  //! What step_pos to start decelaration
  u32 decel_start;
	
	u32 run_start;
  //! Sets deceleration rate.
//  u16 decel_val;
  //! Minimum time delay (max speed)
  u16 min_delay;
  //! Counter used when accelerateing/decelerateing to calculate step_delay.
  u32 accel_count;
	
} speedRampData;


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#define T1_FREQ 2000000
#define T1_FREQ_2 1000000
#define SPR 1000
// Maths constants. To simplify maths when calculating in AxisMoveRel().
#define ALPHA (2*3.14159/SPR)                    // 2*pi/spr
#define A_T_x100 ((long)(ALPHA*T1_FREQ*100))     // (ALPHA / T1_FREQ)*100
#define T1_FREQ_148 ((int)((T1_FREQ*0.676)/100)) // divided by 100 and scaled by 0.676
#define A_SQ (long)(ALPHA*2*100000*100000)         // 
#define A_x20000 (int)(ALPHA*20000)              // ALPHA*20000
// Speed ramp states
#define STOP  0
#define ACCEL 1
#define RUN   2
#define DECEL 3
#define LRUN  4

extern u8 XResetFlag;
extern u8 Y1ResFlag;
extern u8 Y2ResFlag;

extern u8 XStopFlag;
extern u8 YStopFlag;


#define	 FREQUENCY_ADD  100       //¼Ó¼õËÙµÄÃ¿¼¶ÐèÒªµÄÆµÂÊÊý
#define  FREQUENCY_START 200	  //Æô¶¯µÄÆµÂ

#define  DIVIDVALUE 2000;

extern speedRampData srdx,srd1y,srd2y;	
	
//extern Moto_Struct MotoCurrentStruct;
extern u16 Current_Positon;
extern u16 Last_Positon;


extern u8 Vib;
 
extern u8 Y1RSTOV;
extern u8 Y2RSTOV;
extern u8 X0RSTOV;
extern u8 Y1Y2RSTOV;
extern u8 RSTALARM;
extern u8 door;


//void MotorXYZInit(void);	// DS1	  X ,Y moto  enable io and  direction io 
#define X_EN PAout(12)
#define X_DIR PAout(11)	// DS0
//#define X_EN PBout(6)
//#define X_DIR PBout(7)	// DS0

#define YB_DIR PCout(8)	// DS1	 
#define YB_EN PCout(9)	// DS0    Y1


#define YT_EN PDout(14)	// DS1	  
#define YT_DIR PDout(15)	// DS0

#define XACCNUM 80
//#define YACCNUM 20

#define YACCNUM 12


#define X2ACCNUM 160
#define X3ACCNUM 200

#define Y2ACCNUM 40

#define XminSpeed 50
#define YminSpeed 50

extern u16 XACC[XACCNUM];
extern u16 XACCReset[XACCNUM];

extern u16 YACC[6][YACCNUM];
extern u8 Y1SFlag;

//extern u16 YACC1[YACCNUM];
//extern u16 YACC2[YACCNUM];
//extern u16 YACC3[YACCNUM];
//extern u16 YACC4[YACCNUM];
//extern u16 YACC5[YACCNUM];

extern u16 Y1Y2ACC[6]; 

extern u16 YACCReset[YACCNUM];


//extern u8 


 void MotorX0Mov(u8 direction,u16 frequency,u32 distance);
 void MotorY1Mov(u8 direction,u16 frequency,u16 distance);
 void MotorY2Mov(u8 direction,u16 frequency,u16 distance);
 void MotorY1Y2Mov(u8 direction,u16 frequency,u16 distance);
 void MotorY1Vib(u32 vib_v,u32 amp,u32 t);
 void MotorX0Reset(u8 direction,u16 frequency,u32 distance);
 void MotorY1Reset(u8 direction,u16 frequency,u16 distance);
 void MotorY2Reset(u8 direction,u16 frequency,u16 distance);
 void Y1Y2Reset(void);
 void X0Reset(void);
// void Delay(uint16 time);
// void Delay1(uint16 time);
 void OverAlarm(void);
 void ResetAlarm(void);
 void ErrorAlarm(void);

//u32 sqrt(u32 x);
#endif


