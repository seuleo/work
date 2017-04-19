#ifndef __128S085_H
#define __128S085_H	 
#include "sys.h"	     			    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//DAC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved 
////////////////////////////////////////////////////////////////////////////////// 	

#define	Dac128S085_CS 		PBout(7)  		//W25QXX��Ƭѡ�ź�
#define	SCK 		PBout(3)  		//W25QXX��Ƭѡ�ź�
#define	SDO 		PBout(5)  		//W25QXX��Ƭѡ�ź�
//#define DAC_A_FULL   0x0FFC
//#define DAC_B_three_quarters   0x1C00
//#define	DAC_C_half 0x2800
//#define	DAC_D_one_quarter 0x3400
//#define DAC_E_FULL 	0x4FFC
//#define DAC_F_half 	0x5800
#define DAC_UPDATE 0xA0FF //8��ͨ��




void Dac128S085_Init(void);		//DACͨ��1��ʼ��	 	 
void Dac128S085_Set_Vol(u16 vol,u8 chanle);	//����ͨ��1�����ѹ

void DacUpdate();

void TemSet();

void Dac128S_Init(void);
void Dac128S085_Vol(u16 vol,u16 chanle1);



//void TemValueSet();

//u16 TableSearchVoltageDAC0( u16 a[][60], u16 temperature, u16 n );


//u16 GetVoltageDAC0(u16 temperature);


#endif

















