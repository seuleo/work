#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
						  
////////////////////////////////////////////////////////////////////////////////// 	 
 
#define TIMES_AVER      32   

void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  

//u16 TableSearchTemperature123( int a[][77], u16 voltage, u16 n );
//extern u16 Table[3][77];
extern volatile u16 aADCDualConvertedValue[64][8];
extern volatile float TempNow[8];
extern volatile u8 TempLast[8];
extern volatile u16 ConvertedValue[96][8];

extern u16 TableAdc[8][72];

extern u16 TableDac[8][72];

void filter(void);

float  TableSearchTemperatures(u16 adcv,u8 idex);


u16 GetVoltageDACS(u16 temperature,u8 index);

//float  TableSearchTemperaturef2(u16 adcv);
//float  TableSearchTemperaturef3(u16 adcv);
//float  TableSearchTemperaturef4(u16 adcv);

extern u8 FlagDMA;

extern u16 BDDac[8];

extern u16 BDAdc[8];

extern float ad[8];


extern u16 JRTime;
extern u8 JRFlag;

void bsp_InitADC(void);


//u8 TableSearchTemperature(void);
float TableSearchTemperature(u8 jj,u16 adcv);

u16  filters(u8 k);


#endif 















