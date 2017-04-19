#ifndef __FRAME_DEAL_H
#define __FRAME_DEAL_H
#include "sys.h"

///////////////////////////////////////////////////////////////////////////////
//制水机项目
//相关数据结构
//
//
//
//创建日期:2015/6/24
//版本：V1.0
//
//Copyright(C) 
//All rights reserved									  
///////////////////////////////////////////////////////////////////////////////

#define VariName_LEN 10
#define USART3_REC_LEN 32
#define USART3_TRM_LEN 32
#define Max_Length_Para 30
#define PRECISION 3	//小数点后的精确位数
#define	Max_Length_State 10		//系统控制状态量
extern u8 PassWord_Maintainer[8];
extern u8 PassWord_Management[8];
//相关状态量

/** 
  * @brief   温湿度状态值的结构体
  */ 
typedef struct{
	float Tem_External;		//外部环境温度T101
	float Humi_External;		//外部环境湿度H102
	float Tem_HeatExchanger;		//热交换器横向入口温度T103 
	float Humi_HeatExchanger;		//热交换器横向入口湿度H104
	float Tem_Evapsurface;		//蒸发器表面温度T301
//	float Tem_Compressor;		//压缩机温度T401
} TemHumi_Value_Struct;

/** 
  * @brief   压缩机风量压力值的结构体
  */ 
typedef struct{	
	float Quan_Airflow_Value;		   //新风流量F201 入口  
	float Quan_Airflow_Value_Sum;  //总风机流量F202 出口  
//	float Pre_Compressor_IN;		   //压缩机入口压力P402
//	float Pre_Compressor_OUT;		   //压缩机出口压力P403
} Compressor_Para_Struct;

/** 
  * @brief   储水箱相关量的结构体
  */ 
typedef struct{	
	u16   Water_Cnt;
	float Volume_Tank_Present;		//当前储水箱水量V501
	float Volume_Tank_Day;		//当日制水量V502
	float Volume_Tank_Month;		//当月制水量V503
	float Volume_Tank_Year;		//当年制水量V504
	float Volume_Tank_Sum;		//总制水量V505
	float Volume_Tank_Theory;		//总制水量V506
} Volume_Tank_Struct;

/** 
  * @brief   电能表相关量的结构体
  */ 
typedef struct{	
	float Voltage_EUA;		//当前电压EUA
	float Voltage_EUB;		//当前电压EUB
	float Voltage_EUC;		//当前电压EUC
	float Current_EIA;		//当前电流EIA
	float Current_EIB;		//当前电流EIB
	float Current_EIC;		//当前电流EIC
	
	float Power_EPQ;		//当前总功率EPQ
	float PowerConsum;
	
	float PowerConsum_Previously;		//前一天耗电显示值  增加一项，替代原来的 生成 昨天的结构体
	float PowerConsum_Day;		//当日耗电量EE601
	float PowerConsum_Month;		//当月耗电量EE602
	float PowerConsum_Year;		//当年耗电量EE603
	float PowerConsum_Sum;		//总耗电量EE604
} Power_Consumption_Struct;

/** 
  * @brief   能耗比相关变量的结构体，Energy consumption ratio
  */ 
typedef struct{	
	float ECR_Day;		//当日能耗比E701
	float ECR_Month;		//当月能耗比E702
	float ECR_Year;		//当年能耗比E703
	float ECR_Sum;		//总能耗比E704
} Energy_ConsumpRatio_Struct;

/** 
  * @brief   系统控制量相关状态的结构体
  */ 
typedef struct{
	uint8_t Fan_New_State;  //新风机启停状态，0：停止状态，1：启动状态   入口 
	uint8_t Fan_Total_State;  //风机启停状态，0：停止状态，1：启动状态 出口
	uint8_t Compressor_State;   //压缩机启停状态
	uint8_t Pump_State;  //水泵启停状态
	uint8_t ALARM_State; //电磁阀出水演示状态；
	uint8_t AirIn_State;   //进风口安全门开合状态
	uint8_t AirOut_State;    //出风口安全门开合状态
	uint8_t System_State;    //整机启停状态
	uint8_t SysCheck_State;   //系统自检成功或失败状态
	uint8_t DataTranfer_State;    //导出数据操作成败状态
	uint8_t TimeControl_State;    //是否启用时段控的状态
	uint8_t HightPress_State;     //高低压保护状态
	uint8_t LowPress_State;
	uint8_t FunInProtect_State;   //风扇热继保护状态
	uint8_t FunOutProtect_State;  
	uint8_t PH_State;   //相序状态
	uint8_t CmpProtect_State; //压缩机热继保护状态；
	
	}	ControlVari_State_Struct;

//极限参数
	
/** 
  * @brief   极限参数结构体
  */ 
typedef struct{
	float Tem_External_UP;		//外部温度上限
	float Tem_External_DOWN;		//外部温度下限
	float Humi_External_DOWN;		//外部湿度下限
	float Tem_Evapsurf_DOWN;		//蒸发器温度下限
//	float Tem_Evapsurf_UP;		//蒸发器温度上限
//	float Tem_Compressor_UP;		//压缩机温度上限
	
	float Level_Tank_UP;		//储水箱水位上限
	float Level_Tank_DOWN;		//储水箱水位下限
	
	float Quan_Airflow_DOWN;		//新风流量下限
	
//	float Pre_High_DOWN;		//内循环高压下限
//	float Pre_Low_DOWN;		//内循环低压下限
} Parameter_Struct;

//设置参数
/** 
  * @brief   启停时间段结构体
  */ 
typedef struct{
	uint8_t Start_Hour;  //启动时刻，小时
	uint8_t Start_Min;   //启动时刻，分钟
	uint8_t Stop_Hour;   //停止时刻，小时
	uint8_t Stop_Min;    //停止时刻，分钟
}	RunTime_Struct;
/** 
  * @brief   时间校准参数结构体
  */ 
typedef struct{
	uint8_t Year_Set;  //校准时间，年
	uint8_t Mon_Set;   //校准时间，月
	uint8_t Date_Set;  //校准时间，日
	uint8_t Hour_Set;   //校准时间，时
	uint8_t Min_Set;    //校准时间，分
	uint8_t Sec_Set;    //校准时间，秒
	}	SetTime_Struct;

/** 
  * @brief   通信转换帧结构体 
  */ 
typedef struct{
	uint8_t FunctionID;          //功能码
	u8  Vari[VariName_LEN]; //变量字母表示部分
	int16_t VariID;              //变量数值部分
	float   Parameter1;
	u8  Parameter2;
}	Frame_Struct;

extern u8 Close_InDoor_Flag;
extern u8 Open_OutDoor_Flag;
extern u8 Close_OutDoor_Flag;
extern u8 Open_InDoor_Flag;
extern u8 DataTranfer_Flag;


extern u8 Flag_show ;//用于演示 流水的过程
extern u8 Flag_Debug; //0:发布版本（脱机制水），3：手动调试模式,2:自动转手动的切换
extern u8 Flag_TimePhase_Control; //0:非时段控制，1：时段控制 
extern u8 System_Mode; //系统工作模式 0:除霜模式，1:制水模式，2：待机模式，3：自检模式

extern Frame_Struct  FRAME;  //通信转换帧变量
extern RunTime_Struct  RunTime[3]; //启停时间段变量
extern Parameter_Struct   AbsolutePara; //极限参数变量
extern ControlVari_State_Struct  VariState; //系统控制变量
extern SetTime_Struct  SETTIME; //时间校准参数变量
//extern u8 PassWord_Maintainer[9]; //维护密码
//extern u8 PassWord_Management[9]; //管理密码

extern TemHumi_Value_Struct value_temhumi; //温湿度状态值
extern Compressor_Para_Struct value_Compressor;//压缩机风量压力值
extern Volume_Tank_Struct value_volume_tank,value_yesterday_volume_tank;//储水箱相关量
extern Power_Consumption_Struct value_power_consumption,value_yesterday_power_consumption;//电能表相关量
extern Energy_ConsumpRatio_Struct value_energy_consumpRatio;//能耗比相关变量

extern u8 USART3_TX_BUF[USART3_TRM_LEN];		//发送帧：字符数组

u8 assert_Time_Date(RTC_TimeTypeDef* RTC_TimeStruct);

uint8_t FrameAnalysis(u8 *s); //将通信帧中信息分类提取
uint8_t Command_Deal(void);  //处理通信帧
void Show_SystemStatus(void); //向串口屏发送系统实时状态
void Show_SystemSensorData(void); //send uart real sersor data
#endif
