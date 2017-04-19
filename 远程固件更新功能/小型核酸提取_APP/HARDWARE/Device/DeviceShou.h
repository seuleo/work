#ifndef __DeviceShou_H
#define __DeviceShou_H	 
#include "sys.h" 

//需不需要定一个步进电机的细分常数，来确认角度脉冲；
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
typedef struct {
	
	//void 
	u8 SSoftVerM;  //02
	u8 SSoftVerS;
	u8 SSoftVer;
	u32 SSoftTimer;   //03
	u8 SHardwareVerM;  //04
	u8 SHardwareVerS;  
	u8 SHardwareVer;
	u32 SHardwareTimer;  //05
	
	u8 SAdressID; //11
	u16 SBoudValue; //12
	

	
//	float HatchTemper; //31
//	u32 HatchTime; //32


//	float HRealTemper; //41


} DeviceShou;



#define ErrLed PFout(9)

#define OkLed PFout(8)

#define angle0 0;  //旋转相应度数需要旋转的角度；与电机细分有关系；
#define angle90  100;
#define angle180  200;
#define angle270  270;


void InitStateLed(void);

extern DeviceShou ShouX;	
	

//extern u16 Current_Positon;
//extern u16 Last_Positon;
//extern u16 Current_Speed;
//extern u16 Last_Speed;

void SScanDevice(u8 D); //01
void SInitDevice(u8 D); //41
//void ClearErr(u8 D);   //42


void SCapture(void);   //to judge capture the sample by the lightswitch or encoder
void SPut(void);

void SRolation(u16 anglevalue);

void SRolationStop(void);
void SCaptureStop(void);

void SStart(void); //42

void ShouApp(void);

	 
void SEmergyStop(void);//44
#endif
