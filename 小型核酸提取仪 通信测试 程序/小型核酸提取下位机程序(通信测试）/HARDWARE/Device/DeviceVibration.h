#ifndef __DeviceVibration_H
#define __DeviceVibration_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
//#define J1  PDout(0)
//#define J2  PDout(1)
//#define J3  PDout(2)
//#define J4  PDout(3)
//#define J5  PDout(4)
//#define J6  PDout(5)
//#define J7  PDout(6)
//#define J8  PDout(7)


extern  u8 RunFlag;



typedef struct {
	
	//void 
	u8 VSoftVerM;  //02
	u8 VSoftVerS;
	u8 VSoftVer;
	u32 VSoftTimer;   //03
	u8 VHardwareVerM;  //04
	u8 VHardwareVerS;  
	u8 VHardwareVer;
	u32 VHardwareTimer;  //05
	
	u16 VAdressID; //11
	u8 VMainID;
	u8 VSubID;
	u16 VAdressMask;
	
	u16 VBoudValue; //12
	
	u32 VPositionDe; //21
	u32 VPositionMem; //22
	
	u32 VCoderDe; //31
	u32 VCoderMem; //32
	u32 VSpeedDe; //33
	u32 VSpeedMem; //34

	u32 VibrationSpeed; //51
	u32 VibrationTime; //52

} DeviceVibration;


extern DeviceVibration VibrationX;	
	
void Delay(u16 t);



void MovProcess();

#endif
