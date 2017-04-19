#ifndef __DeviceHatch_H
#define __DeviceHatch_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
typedef struct {
	
	//void 
	u8 HSoftVerM;  //02
	u8 HSoftVerS;
	u8 HSoftVer;
	u32 HSoftTimer;   //03
	u8 HHardwareVerM;  //04
	u8 HHardwareVerS;  
	u8 HHardwareVer;
	u32 HHardwareTimer;  //05
	
	u8 HAdressID; //11
	u16 HBoudValue; //12
	

	
	float HatchTemper; //31
	u32 HatchTime; //32


	float HRealTemper; //41


} DeviceHatch;


extern DeviceHatch HatchX;	
	

void Command_Deal_Hatch(u8 *s);


//extern u16 Current_Positon;
//extern u16 Last_Positon;
//extern u16 Current_Speed;
//extern u16 Last_Speed;

void HScanDevice(u8 D); //01
void HInitDevice(u8 D); //41
//void ClearErr(u8 D);   //42

void HStart(void); //42

void HatchApp(void);

	 
void HEmergyStop(void);//44
#endif
