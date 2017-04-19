#ifndef __FRAME_DEAL_H
#define __FRAME_DEAL_H
#include "sys.h"

///////////////////////////////////////////////////////////////////////////////
//��ˮ����Ŀ
//������ݽṹ
//
//
//
//��������:2015/6/24
//�汾��V1.0
//
//Copyright(C) 
//All rights reserved									  
///////////////////////////////////////////////////////////////////////////////

#define VariName_LEN 10
#define USART3_REC_LEN 32
#define USART3_TRM_LEN 32
#define Max_Length_Para 30
#define PRECISION 3	//С�����ľ�ȷλ��
#define	Max_Length_State 10		//ϵͳ����״̬��
extern u8 PassWord_Maintainer[8];
extern u8 PassWord_Management[8];
//���״̬��

/** 
  * @brief   ��ʪ��״ֵ̬�Ľṹ��
  */ 
typedef struct{
	float Tem_External;		//�ⲿ�����¶�T101
	float Humi_External;		//�ⲿ����ʪ��H102
	float Tem_HeatExchanger;		//�Ƚ�������������¶�T103 
	float Humi_HeatExchanger;		//�Ƚ������������ʪ��H104
	float Tem_Evapsurface;		//�����������¶�T301
//	float Tem_Compressor;		//ѹ�����¶�T401
} TemHumi_Value_Struct;

/** 
  * @brief   ѹ��������ѹ��ֵ�Ľṹ��
  */ 
typedef struct{	
	float Quan_Airflow_Value;		   //�·�����F201 ���  
	float Quan_Airflow_Value_Sum;  //�ܷ������F202 ����  
//	float Pre_Compressor_IN;		   //ѹ�������ѹ��P402
//	float Pre_Compressor_OUT;		   //ѹ��������ѹ��P403
} Compressor_Para_Struct;

/** 
  * @brief   ��ˮ��������Ľṹ��
  */ 
typedef struct{	
	u16   Water_Cnt;
	float Volume_Tank_Present;		//��ǰ��ˮ��ˮ��V501
	float Volume_Tank_Day;		//������ˮ��V502
	float Volume_Tank_Month;		//������ˮ��V503
	float Volume_Tank_Year;		//������ˮ��V504
	float Volume_Tank_Sum;		//����ˮ��V505
	float Volume_Tank_Theory;		//����ˮ��V506
} Volume_Tank_Struct;

/** 
  * @brief   ���ܱ�������Ľṹ��
  */ 
typedef struct{	
	float Voltage_EUA;		//��ǰ��ѹEUA
	float Voltage_EUB;		//��ǰ��ѹEUB
	float Voltage_EUC;		//��ǰ��ѹEUC
	float Current_EIA;		//��ǰ����EIA
	float Current_EIB;		//��ǰ����EIB
	float Current_EIC;		//��ǰ����EIC
	
	float Power_EPQ;		//��ǰ�ܹ���EPQ
	float PowerConsum;
	
	float PowerConsum_Previously;		//ǰһ��ĵ���ʾֵ  ����һ����ԭ���� ���� ����Ľṹ��
	float PowerConsum_Day;		//���պĵ���EE601
	float PowerConsum_Month;		//���ºĵ���EE602
	float PowerConsum_Year;		//����ĵ���EE603
	float PowerConsum_Sum;		//�ܺĵ���EE604
} Power_Consumption_Struct;

/** 
  * @brief   �ܺı���ر����Ľṹ�壬Energy consumption ratio
  */ 
typedef struct{	
	float ECR_Day;		//�����ܺı�E701
	float ECR_Month;		//�����ܺı�E702
	float ECR_Year;		//�����ܺı�E703
	float ECR_Sum;		//���ܺı�E704
} Energy_ConsumpRatio_Struct;

/** 
  * @brief   ϵͳ���������״̬�Ľṹ��
  */ 
typedef struct{
	uint8_t Fan_New_State;  //�·����ͣ״̬��0��ֹͣ״̬��1������״̬   ��� 
	uint8_t Fan_Total_State;  //�����ͣ״̬��0��ֹͣ״̬��1������״̬ ����
	uint8_t Compressor_State;   //ѹ������ͣ״̬
	uint8_t Pump_State;  //ˮ����ͣ״̬
	uint8_t ALARM_State; //��ŷ���ˮ��ʾ״̬��
	uint8_t AirIn_State;   //����ڰ�ȫ�ſ���״̬
	uint8_t AirOut_State;    //����ڰ�ȫ�ſ���״̬
	uint8_t System_State;    //������ͣ״̬
	uint8_t SysCheck_State;   //ϵͳ�Լ�ɹ���ʧ��״̬
	uint8_t DataTranfer_State;    //�������ݲ����ɰ�״̬
	uint8_t TimeControl_State;    //�Ƿ�����ʱ�οص�״̬
	uint8_t HightPress_State;     //�ߵ�ѹ����״̬
	uint8_t LowPress_State;
	uint8_t FunInProtect_State;   //�����ȼ̱���״̬
	uint8_t FunOutProtect_State;  
	uint8_t PH_State;   //����״̬
	uint8_t CmpProtect_State; //ѹ�����ȼ̱���״̬��
	
	}	ControlVari_State_Struct;

//���޲���
	
/** 
  * @brief   ���޲����ṹ��
  */ 
typedef struct{
	float Tem_External_UP;		//�ⲿ�¶�����
	float Tem_External_DOWN;		//�ⲿ�¶�����
	float Humi_External_DOWN;		//�ⲿʪ������
	float Tem_Evapsurf_DOWN;		//�������¶�����
//	float Tem_Evapsurf_UP;		//�������¶�����
//	float Tem_Compressor_UP;		//ѹ�����¶�����
	
	float Level_Tank_UP;		//��ˮ��ˮλ����
	float Level_Tank_DOWN;		//��ˮ��ˮλ����
	
	float Quan_Airflow_DOWN;		//�·���������
	
//	float Pre_High_DOWN;		//��ѭ����ѹ����
//	float Pre_Low_DOWN;		//��ѭ����ѹ����
} Parameter_Struct;

//���ò���
/** 
  * @brief   ��ͣʱ��νṹ��
  */ 
typedef struct{
	uint8_t Start_Hour;  //����ʱ�̣�Сʱ
	uint8_t Start_Min;   //����ʱ�̣�����
	uint8_t Stop_Hour;   //ֹͣʱ�̣�Сʱ
	uint8_t Stop_Min;    //ֹͣʱ�̣�����
}	RunTime_Struct;
/** 
  * @brief   ʱ��У׼�����ṹ��
  */ 
typedef struct{
	uint8_t Year_Set;  //У׼ʱ�䣬��
	uint8_t Mon_Set;   //У׼ʱ�䣬��
	uint8_t Date_Set;  //У׼ʱ�䣬��
	uint8_t Hour_Set;   //У׼ʱ�䣬ʱ
	uint8_t Min_Set;    //У׼ʱ�䣬��
	uint8_t Sec_Set;    //У׼ʱ�䣬��
	}	SetTime_Struct;

/** 
  * @brief   ͨ��ת��֡�ṹ�� 
  */ 
typedef struct{
	uint8_t FunctionID;          //������
	u8  Vari[VariName_LEN]; //������ĸ��ʾ����
	int16_t VariID;              //������ֵ����
	float   Parameter1;
	u8  Parameter2;
}	Frame_Struct;

extern u8 Close_InDoor_Flag;
extern u8 Open_OutDoor_Flag;
extern u8 Close_OutDoor_Flag;
extern u8 Open_InDoor_Flag;
extern u8 DataTranfer_Flag;


extern u8 Flag_show ;//������ʾ ��ˮ�Ĺ���
extern u8 Flag_Debug; //0:�����汾���ѻ���ˮ����3���ֶ�����ģʽ,2:�Զ�ת�ֶ����л�
extern u8 Flag_TimePhase_Control; //0:��ʱ�ο��ƣ�1��ʱ�ο��� 
extern u8 System_Mode; //ϵͳ����ģʽ 0:��˪ģʽ��1:��ˮģʽ��2������ģʽ��3���Լ�ģʽ

extern Frame_Struct  FRAME;  //ͨ��ת��֡����
extern RunTime_Struct  RunTime[3]; //��ͣʱ��α���
extern Parameter_Struct   AbsolutePara; //���޲�������
extern ControlVari_State_Struct  VariState; //ϵͳ���Ʊ���
extern SetTime_Struct  SETTIME; //ʱ��У׼��������
//extern u8 PassWord_Maintainer[9]; //ά������
//extern u8 PassWord_Management[9]; //��������

extern TemHumi_Value_Struct value_temhumi; //��ʪ��״ֵ̬
extern Compressor_Para_Struct value_Compressor;//ѹ��������ѹ��ֵ
extern Volume_Tank_Struct value_volume_tank,value_yesterday_volume_tank;//��ˮ�������
extern Power_Consumption_Struct value_power_consumption,value_yesterday_power_consumption;//���ܱ������
extern Energy_ConsumpRatio_Struct value_energy_consumpRatio;//�ܺı���ر���

extern u8 USART3_TX_BUF[USART3_TRM_LEN];		//����֡���ַ�����

u8 assert_Time_Date(RTC_TimeTypeDef* RTC_TimeStruct);

uint8_t FrameAnalysis(u8 *s); //��ͨ��֡����Ϣ������ȡ
uint8_t Command_Deal(void);  //����ͨ��֡
void Show_SystemStatus(void); //�򴮿�������ϵͳʵʱ״̬
void Show_SystemSensorData(void); //send uart real sersor data
#endif
