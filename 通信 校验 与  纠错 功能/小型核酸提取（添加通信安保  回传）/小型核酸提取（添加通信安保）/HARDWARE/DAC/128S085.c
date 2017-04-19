#include "128S085.h"
//#include "adc.h"
#include "spi.h"
#include "delay.h"

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
 

//DACͨ��1�����ʼ��
//void Dac1_Init(void)
//{  
//GPIO_InitTypeDef  GPIO_InitStructure;
//DAC_InitTypeDef DAC_InitType;

//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//ʹ��DACʱ��
//	 
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
//GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

//DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
//DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
//DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
//DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Enable ;	//DAC1�������ر� BOFF1=1
//DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

//DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DACͨ��1

//DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ
//}
//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
//void Dac1_Set_Vol(u16 vol)
//{
//	double temp=vol;
//	temp/=1000;
//	temp=temp*4096/3.3;
//	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
//}

void Dac128S085_Init(void)//DACͨ��1��ʼ��	 
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);//ʹ��SPI1ʱ��
 
  //GPIOFB3,4,5��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_5;//PB3~5���ù������	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); //PB3����Ϊ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); //PB4����Ϊ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); //PB5����Ϊ SPI1
 
	//����ֻ���SPI�ڳ�ʼ��
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//��λSPI1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//ֹͣ��λSPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����

//	SPI1_ReadWriteByte(0xff);//��������		 
	
	
  Dac128S085_CS=1;			//SPI FLASH��ѡ��
//	SPI1_Init();		   			//��ʼ��SPI
	//SPI1_SetSpeed(SPI_BaudRatePrescaler_8);		//����Ϊ42/4=10.5 Mʱ��,����ģʽ 
	
}




void Dac128S_Init(void)
{
	  
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//??GPIOF??

  //GPIOF9,F10?????
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOB, &GPIO_InitStructure);//???
	
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//GPIOF9,F10???,??
	GPIO_SetBits(GPIOB,GPIO_Pin_5);//GPIOF9,F10???,??
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);//GPIOF9,F10???,??
	
	Dac128S085_Vol(0xfff,9);       //����adc128s085 ΪWTMģʽ
	Dac128S085_Vol(0xfff,12);      //����adc128s085��8��ͨ�������ߵ�ѹ
	
	
}//DACͨ��1��ʼ��	 

//void Dac128S085_Vol(u16 vol,u8 chanle1)
//{
//	
// int i = 16;
// u16 data =0;

// data= vol+(chanle1<<12);
//	
// Dac128S085_CS=1;
// delay_us(1);
// Dac128S085_CS=0;
// 
// while(i--)        {
//	      SCK=1;
//	      if(data&0x8000)
//					SDO=1;
//				else
//					SDO=0;
//				   
//				delay_us(1);
//				SCK=0;
//				data <<= 1; 
//				delay_us(1);
//				
//}
//SCK=1; 
//Dac128S085_CS=1;
//delay_us(10);
//}

//��ֵ�˲���
//u16 GetMedianNum(u16 * bArray, u8 iFilterLen)  
//{  
//    u8 i,j;// ?????  
//    u16 bTemp;  
//      
//    // ????
//    for (j = 0; j < iFilterLen - 1; j ++)  
//    {  
//        for (i = 0; i < iFilterLen - j - 1; i ++)  
//        {  
//            if (bArray > bArray[i + 1])  
//            {  
//                // ??
//                bTemp = bArray;  
//                bArray = bArray[i + 1];  
//                bArray[i + 1] = bTemp;  
//            }  
//        }  
//    }   
//    bTemp = bArray[(iFilterLen + 1) / 2];  


//    return bTemp;  
//}  
void Dac128S085_Vol(u16 vol,u16 chanle1)
{
	
 int i = 16;
 u16 data =0;
 data= vol+(chanle1<<12); 
 Dac128S085_CS=1;
 delay_us(2);
 Dac128S085_CS=0;
 
 while(i--)        
	 {
	      SCK=1;
	      if(data&0x8000)
					SDO=1;
				else
					SDO=0;
				   
				delay_us(2);
				SCK=0;
				data <<= 1; 
				delay_us(2);
				
}
SCK=1; 
Dac128S085_CS=1;
delay_us(20);
}



//0-7 ����12λ ���� 
void Dac128S085_Set_Vol(u16 vol,u8 chanle1)
{
	
	  
   
  Dac128S085_CS=0;			//SPI FLASH��ѡ��
	
	SPI_I2S_SendData(SPI1, vol); //ͨ������SPIx����һ��byte  ����
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//�ȴ���������  
	
		
	Dac128S085_CS=1;			//SPI FLASH��ѡ��
	
	
	
}


void DacUpdate()
{
	
	Dac128S085_CS=0;			//SPI FLASH��ѡ��
	
	SPI_I2S_SendData(SPI1, 0xA0FF); //ͨ������SPIx����һ��byte  ����
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//�ȴ���������  
	
		
	Dac128S085_CS=1;			//SPI FLASH��ѡ��
	
	
	
}
	//����ͨ��1�����ѹ




//u16 GetVoltageDAC0(u16 temperature)
//{
//  u16 DacV=0;
//	u8 i;
//  //�������� 40-99�ȣ�//31-102
//	i=temperature-31;
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
//  else if(i>71)
//	{
//		i=71;
//		//err ;over temp
//		//DacV=2500; 
//		
//		//DacV=2500; 
//		
//    return TableDac[71];		
//	}
//	
//	
//	else return TableDac[i];		
//	
//	
//}



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




void TemSet()
{
	
	
}












































