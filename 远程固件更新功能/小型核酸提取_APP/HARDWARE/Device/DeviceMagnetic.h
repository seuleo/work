#ifndef __DeviceMagnetic_H
#define __DeviceMagnetic_H	 
#include "sys.h"  	

//extern u8 Sending;
extern u16 EEprom[7];

extern u8 Up;
extern u8 Down;

extern u8 Mov;
extern u8 Direction;
extern u16 MovDis;

extern u8 Write;
extern u8 Read;
extern u8 Reset;
extern u8 ExeCmdFlag;

extern u8 UpSlow;

extern u8 PositionJudge ;
extern u32 CurrentPosition ;
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
typedef struct {
	
	//void 
	u8 MSoftVerM;  //02
	u8 MSoftVerS;
	u8 MSoftVer;
	u32 MSoftTimer;   //03
	u8 MHardwareVerM;  //04
	u8 MHardwareVerS;  
	u8 MHardwareVer;
	u32 MHardwareTimer;  //05
	
	u8 MAdressID; //11
	u16 MBoudValue; //12
	
	u32 MPositionDe; //21
	u32 MPositionMem; //22
	
	u32 MCoderDe; //31
	u32 MCoderMem; //32
	u32 MSpeedDe; //33
	u32 MSpeedMem; //34
	
	float MUpDis;//51
	float MDownDis; //52
	
	float AdsorptionDis; //61
	u32 AdsorptionSpeed; //62
	float EmptyDis;
	u32 EmptySpeed ;
	u32 DownSpeed;
	u32 MoveSpeed;
	
	
	float MotoPosition;  //71
	
	
	
} DeviceMagnetic;


extern DeviceMagnetic MagneticX;	
	

//extern u16 Current_Positon;
//extern u16 Last_Positon;
//extern u16 Current_Speed;
//extern u16 Last_Speed;

void MScanDevice(u8 D); //01
void MInitDevice(u8 D); //41
//void ClearErr(u8 D);   //42

void InAdsorption(void); //42
void DeAdsorption(void); //43
void MEmergyStop(void);//44

void InitSwitch(void);

	void MagneticApp(void);

#endif
