#ifndef __DeviceAxis_H
#define __DeviceAxis_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
typedef struct {
	
	//void 
	u8 ASoftVerM;  //02
	u8 ASoftVerS;
	u8 ASoftVer;
	u32 ASoftTimer;   //03
	u8 AHardwareVerM;  //04
	u8 AHardwareVerS;  
	u8 AHardwareVer;
	u32 AHardwareTimer;  //05
	
	u8 AAdressID; //11
	u16 ABoudValue; //12
	
	u32 APositionDe; //21
	u32 APositionMem; //22
	
	u32 ACoderDe; //31
	u32 ACoderMem; //32
	u32 ASpeedDe; //33
	u32 ASpeedMem; //34
	
//  u32 MotoPosition; 
	
	float AForDis;//51
	float ABackDis; //52
	float AInitDis; //53
	
//		u8 MOTO_DIR_State;  //
	u32 AMotoAccel; //61
//	u32 MotoDecel; // 
  u32 AMotoInitAccel; //62
	u32 AMotoSpeed;   //63
	u32 AMotoInitSpeed;
	
	float AMotoPosition;  //71
	
	
	
} DeviceAxis;



//#define MotoEN PBout(6)	 //



extern DeviceAxis AxisX;	
extern DeviceAxis AxisY;	
extern DeviceAxis AxisZ;	


//extern u16 Current_Positon;
//extern u16 Last_Positon;
//extern u16 Current_Speed;
//extern u16 Last_Speed;

void AScanDevice(u8 D); //01
void ASoftverRead(u8 *s);
void ASoftTimerRead(u8 *s);
void AHardverRead(u8 *s);
void AHardwareTimerRead(u8 *s);




void ASoftverWrite(u8 *s);
void ASoftTimerWrite(u8 *s);
void AHardverWrite(u8 *s);
void AHardwareTimerWrite(u8 *s);



void AInitDevice(u8 D); //41
void AClearErr(u8 D);   //42
void AxisEnable(void); //43
void AxisDisable(void); //44
void AEmergyStop(void);//45
void Command_Deal_Axis(u8 *s);

void AxisApp(void);

#endif
