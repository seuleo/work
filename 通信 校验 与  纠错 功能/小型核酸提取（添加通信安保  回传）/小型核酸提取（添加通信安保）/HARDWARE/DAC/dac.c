#include "dac.h"
#include "adc.h"

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
 
//pb7 /synk
//pb6 din;




//DACͨ��1�����ʼ��
void Dac1_Init(void)
{  
  GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//ʹ��DACʱ��
	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Enable ;	//DAC1�������ر� BOFF1=1
  DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DACͨ��1
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ
}







//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(u16 vol)
{
	double temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}


u16 GetVoltageDAC0(u16 temperature)
{
  u16 DacV=0;
	u8 i;
  //�������� 40-99�ȣ�//31-102
	i=temperature-31;
	if(i<0)
	{
		
		
		DacV=2500;
		
		//err; �����¶ȱ�����
		
		return DacV;
		
		
	}
  else if(i>71)
	{
		i=71;
		//err ;over temp
		//DacV=2500; 
		
		//DacV=2500; 
		
    return TableDac[71];		
	}
	
	
	else return TableDac[i];		
	
	
}



//voltage = TableSearchVoltageDAC0( Table,EEpromJR[0],77 );			  //

//u16 TableSearchVoltageDAC0( u16 a[][60], u16 temperature, u16 n )
//{
//	int16 left = 0, right = n - 1, mid = 0;
//	mid = ( left + right ) / 2;
//	
//	while( left < right && a[0][mid] != temperature )
//	{
//		if( a[0][mid] < temperature )
//			left = mid + 1;
//		else if( a[0][mid] > temperature )
//			right = mid - 1;
//		mid = ( left + right ) / 2;
//	}
//	if( a[0][mid] == temperature )
//	{
//		return a[3][mid];
//	}
//	else
//	{
//		return -1;
//	}
	
//	u16 mid=0;
//	mid=temperature-29;
//	if(mid<0)
//	{
//		return -1;
//	}
//	else
//		return Table[2][mid];
//}




//u16 GetVoltageDAC0(u16 temperature)
//{
//  u16 DacV=0;
//	u8 i;
//  //�������� 40-99�ȣ�//31-102
//	i=temperature-40;
//	if(i<0)
//	{
//		
//		
//		DacV=2500;
//		
//		//err; �����¶ȱ�����
//		
//		return DacV;
//		
//		
//	}
//  if(i>59)
//	{
//		i=60;
//		//err ;over temp
//		DacV=2500; 
//		
//		//DacV=2500; 
//		
//    return TableDac[59];		
//	}
//	
//	
//	return TableDac[i];		
//	
//	
//}




void TemValueSet()
{
	
	
}












































