#include "sys.h"
#include "string.h"
#include "rs232.h"
#include "frame_deal.h" 
#include "string_deal.h"
#include "iocontrol.h"
#include "usart.h"
#include "rtc.h"
#include "timer3.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//制水机项目
//Water Generating Workstation
//通信帧处理   
//
//创建日期:2015/6/25
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C)shine
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
//u8 Flag_Debug = 3;         //0:发布版本（脱机制水），3：手动调试模式,2:自动转手动的切换
u8 Close_InDoor_Flag=0;
u8 Open_OutDoor_Flag=0;
u8 Close_OutDoor_Flag=0;
u8 Open_InDoor_Flag=0;
u8 DataTranfer_Flag=0;

u8 Flag_show =0; //启动演示
u8 Flag_Debug = 3; 
u8 Flag_TimePhase_Control = 0; //0:非时段控制，1：时段控制
u8 System_Mode = 2;       //系统工作模式
u8 Flag_Count_Setting_Para = 0; //启动前新设置参数更新标志，flag=1时需要更新flash

Frame_Struct  FRAME;  //通信转换帧变量
u8 USART3_TX_BUF[USART3_TRM_LEN];		//发送帧：字符数组
//u8 PassWord_Maintainer[9]={0x31,0x32,0x33,0x34,0x35,0x36,0x0d,0x0a},PassWord_Management[9]={0x32,0x33,0x34,0x35,0x36,0x37,0x0d,0x0a};//PassWord
u8 PassWord_Maintainer[8];
u8 PassWord_Management[8];
//u8 PassWord_Maintainer[8]={0x31,0x32,0x33,0x34,0x35,0x36,0x0d,0x0a},PassWord_Management[8]={0x32,0x33,0x34,0x35,0x36,0x37,0x0d,0x0a};//PassWord
//制水机需设置相关变量
RunTime_Struct  RunTime[3]; //启停时间段变量
Parameter_Struct   AbsolutePara; //极限参数变量
ControlVari_State_Struct  VariState; //系统控制变量
SetTime_Struct  SETTIME; //时间校准参数变量



//制水机需采集和计算的实时变量
TemHumi_Value_Struct value_temhumi; //温湿度状态值
Compressor_Para_Struct value_Compressor;//压缩机风量压力值
Volume_Tank_Struct value_volume_tank,value_yesterday_volume_tank;//储水箱相关量
Power_Consumption_Struct value_power_consumption,value_yesterday_power_consumption;//电能表相关量
Energy_ConsumpRatio_Struct value_energy_consumpRatio;//能耗比相关变量

u8 assert_Time_Date(RTC_TimeTypeDef* RTC_TimeStruct);

//通信帧处理相关函数
u8 FrameAnalysis(u8 *s); //将通信帧中信息分类提取
u8 Command_Deal(void);  //处理通信帧 
void AbsoluteParaStore(void); //提取极限参数 
void SetTime_Data(u8 *s); //提取时间校正参数
void Copy_RxBuf_to_TxBuf(u8 *rx_buf,u8 *tx_buf); //复制变量符号
uint8_t Extract_String(u8 *s,u8 *d); //提取字符串中等号'='后的字符
uint8_t Extract_VariableName(u8 *s); //提取字符串中等号'='前的字

//void Show_SystemStatus(void); //向串口屏发送系统实时状态


/** 
  * @brief  将通信帧中信息分类提取，存入结构体  
  */ 
u8 FrameAnalysis(u8 *s) 
{
	u8 P[2]="C";//
	
	Extract_VariableName(s);
	if(is_inquiry(s))
	{
		FRAME.FunctionID = 0xF1;   //查询操作
	}
	else
	{
		if(strcmp(FRAME.Vari,P) == 0)//FRAME.Vari
		{
			FRAME.FunctionID = 0xF2;  //操作命令
			FRAME.Parameter2 = Convert_ASCII_to_INT1(s);  //操作命令的参数
			/*
			if((FRAME.Parameter1 < 0) || (FRAME.Parameter1 > 1))
			{
				//报告错误
				return 0;
			}
			*/
		}
		else
		{
			FRAME.FunctionID = 0xF3;  //设置命令
			
			if((FRAME.VariID > 100)&&(FRAME.VariID <= 110))  //因参数的格式不同，分4种情况，此为第一种情况，温湿度值
			{
				FRAME.Parameter1 = Convert_ASCII_to_FLOAT(s);
				AbsoluteParaStore();
			}
			 
			if((FRAME.VariID >= 111)&&(FRAME.VariID <= 116))  //第二种参数，时间（小时：分钟）
			{
				switch(FRAME.VariID)
				{
					case 111:
						RunTime[0].Start_Hour = Convert_ASCII_to_INT1(s);  //第1组启动时间
						RunTime[0].Start_Min = Convert_ASCII_to_INT2(s);
						break;
					case 112:
						RunTime[0].Stop_Hour = Convert_ASCII_to_INT1(s);   //第1组停止时间
						RunTime[0].Stop_Min = Convert_ASCII_to_INT2(s);
						break;
					case 113:
						RunTime[1].Start_Hour = Convert_ASCII_to_INT1(s);  //第2组启动时间
						RunTime[1].Start_Min = Convert_ASCII_to_INT2(s);
					  break;
					case 114:
						RunTime[1].Stop_Hour = Convert_ASCII_to_INT1(s);   //第2组停止时间
						RunTime[1].Stop_Min = Convert_ASCII_to_INT2(s);
						break;
					case 115:
						RunTime[2].Start_Hour = Convert_ASCII_to_INT1(s);   //第3组启动时间
						RunTime[2].Start_Min = Convert_ASCII_to_INT2(s);
						break;
					case 116:
						RunTime[2].Stop_Hour = Convert_ASCII_to_INT1(s);    //第3组停止时间
						RunTime[2].Stop_Min = Convert_ASCII_to_INT2(s);
					
					//FLASH 保存数据 
						break;
				}
				
				
				
			}
			
			if(FRAME.VariID == 117)  //第三种参数，时间校准参数（年月日时分秒）
			{
				SetTime_Data(s);
					//RS232_Send_Data("OK\r\n",4);
			}
			if(FRAME.VariID == 118)   //第四种参数，设置密码
			{
				Extract_String(Frame_Store[SeqNum_Frame_Deal],PassWord_Maintainer);
				Write_Para_ToFlashC(2);
				//printf("OK\n");
				RS232_Send_Data(":S118=OK\r\n",9);
				//
			}
			if(FRAME.VariID == 119)
			{
				Extract_String(Frame_Store[SeqNum_Frame_Deal],PassWord_Management);
				Write_Para_ToFlashC(2);
				//
				//printf("OK\n");
				RS232_Send_Data(":S119=OK\r\n",9);
			}
		}
	}
	return 1;
}

/** 
  * @brief  处理通信帧 
  */ 
uint8_t Command_Deal(void)
{
	switch(FRAME.FunctionID)
	{
		uint8_t t;
		uint8_t Control_State[Max_Length_State];
		case 0xF1:	//查询，返回状态
			/********************对于参数极限值的查询，只需读取相应变量即可*******************/
			Copy_RxBuf_to_TxBuf(Frame_Store[SeqNum_Frame_Deal],USART3_TX_BUF);
			if(strcmp(FRAME.Vari,"S") == 0)		//
			{
				 
				if((FRAME.VariID > 100)&&(FRAME.VariID < 111))
				 {
					 float absolute_para;
					 u8  Absolute_para[Max_Length_Para];
					 
					 switch(FRAME.VariID)
					  {
						 case 101:
							absolute_para = AbsolutePara.Humi_External_DOWN;
						  Float_to_String(absolute_para,Absolute_para,1);
							break;
						case 102:
							absolute_para = AbsolutePara.Tem_External_UP;
							Float_to_String(absolute_para,Absolute_para,1);
							break;
						case 103:
							absolute_para = AbsolutePara.Tem_External_DOWN;
							Float_to_String(absolute_para,Absolute_para,1);
							break;
						case 104:
							absolute_para = AbsolutePara.Tem_Evapsurf_DOWN;
							Float_to_String(absolute_para,Absolute_para,1);
							break;
						case 105:
//							absolute_para = AbsolutePara.Tem_Evapsurf_UP;
//							Float_to_String(absolute_para,Absolute_para,1);
							break;
						case 106:
							absolute_para = AbsolutePara.Level_Tank_UP;
							Float_to_String(absolute_para,Absolute_para,2);
							break;
						case 107:
							absolute_para = AbsolutePara.Level_Tank_DOWN;
							Float_to_String(absolute_para,Absolute_para,2);
							break;
						case 108:
							absolute_para = AbsolutePara.Quan_Airflow_DOWN;//111.132;
							Float_to_String(absolute_para,Absolute_para,3);
							break;
//						case 109:
//							absolute_para = AbsolutePara.Pre_High_DOWN;
//							Float_to_String(absolute_para,Absolute_para,2);
//							break;
//						case 110:
//							absolute_para = AbsolutePara.Pre_Low_DOWN; //1187.970显示的精度是1187.969
//							Float_to_String(absolute_para,Absolute_para,2);
//							break;
					 }
					//Float_to_String(absolute_para,Absolute_para,PRECISION);
					strcat(USART3_TX_BUF,Absolute_para);
			 }
				else if((FRAME.VariID > 110)&&(FRAME.VariID < 117))
				{
					uint8_t Time_para[8];
					switch(FRAME.VariID)
					{
						case 111:
							Int_to_String_Time( RunTime[0].Start_Hour,RunTime[0].Start_Min,Time_para);//INT_Time--->ASCII
						break;
						case 112:
							Int_to_String_Time( RunTime[0].Stop_Hour,RunTime[0].Stop_Min,Time_para);//INT_Time--->ASCII
						break;
						case 113:
							Int_to_String_Time( RunTime[1].Start_Hour,RunTime[1].Start_Min,Time_para);//INT_Time--->ASCII
						break;
						case 114:
							Int_to_String_Time( RunTime[1].Stop_Hour,RunTime[1].Stop_Min,Time_para);//INT_Time--->ASCII
						break;
						case 115:
							Int_to_String_Time( RunTime[2].Start_Hour,RunTime[2].Start_Min,Time_para);//INT_Time--->ASCII
						break;
						case 116:
							Int_to_String_Time( RunTime[2].Stop_Hour,RunTime[2].Stop_Min,Time_para);//INT_Time--->ASCII
						break;
					}
					strcat(USART3_TX_BUF,Time_para);
				}
				else if(FRAME.VariID == 117)
				{
//					RTC_GetDate(RTC_Format_BIN, &RTC_Date_New);
//					RTC_GetTime(RTC_Format_BIN, &RTC_Time_New);
//					USART3_TX_BUF[6] = '2';//":S117=20150729000000\r\n";
//					USART3_TX_BUF[7] = '0';
//					USART3_TX_BUF[8] = RTC_Date_New.RTC_Year/10+0x30;
//					USART3_TX_BUF[9] = RTC_Date_New.RTC_Year%10+0x30;
//					USART3_TX_BUF[10] = RTC_Date_New.RTC_Month/10+0x30;
//					USART3_TX_BUF[11] = RTC_Date_New.RTC_Month%10+0x30;
//					USART3_TX_BUF[12] = RTC_Date_New.RTC_Date/10+0x30;
//					USART3_TX_BUF[13] = RTC_Date_New.RTC_Date%10+0x30;
//					USART3_TX_BUF[14] = RTC_Time_New.RTC_Hours/10+0x30;
//					USART3_TX_BUF[15] = RTC_Time_New.RTC_Hours%10+0x30;
//					USART3_TX_BUF[16] = RTC_Time_New.RTC_Minutes/10+0x30;
//					USART3_TX_BUF[17] = RTC_Time_New.RTC_Minutes%10+0x30;
//					USART3_TX_BUF[18] = RTC_Time_New.RTC_Seconds/10+0x30;
//					USART3_TX_BUF[19] = RTC_Time_New.RTC_Seconds%10+0x30;
//					USART3_TX_BUF[20] = '\r';
//					USART3_TX_BUF[21] = '\n';
//					  RTC_Date_New.RTC_Year/10+0x30=USART3_TX_BUF[8]；
//					                                USART3_TX_BUF[9]；
					
				}
				else if(FRAME.VariID == 118)
				{
					strcat(USART3_TX_BUF,PassWord_Maintainer);		//将:a=和30\r\n两部分合并
				}
				else if(FRAME.VariID == 119)
				{
					strcat(USART3_TX_BUF,PassWord_Management);		//将:a=和30\r\n两部分合并
				}
		}
			
			/********************对于系统控制量的状态值查询*******************/
			else if(strcmp(FRAME.Vari,"C") == 0)		//
			{
				uint8_t control_state;
				//uint8_t Control_State[Max_Length_State];
				switch(FRAME.VariID)
				{
					case 101:
							control_state = VariState.Fan_New_State;
							break;
						case 102:
							control_state = VariState.Compressor_State;
							break;
						case 103:
							control_state = VariState.Pump_State;
							break;
						case 104:
							control_state = VariState.AirIn_State;
							break;
						case 105:
							control_state = VariState.AirOut_State;
							break;
						case 106:
							control_state = VariState.System_State; //系统启动状态
							break;
						case 107:
							control_state = VariState.SysCheck_State;
							break;
						case 108:
							control_state = VariState.DataTranfer_State;
							break;
						case 109:
							control_state = VariState.TimeControl_State;
							break;
						case 110:
							control_state = VariState.Fan_Total_State;
							break;
				}
				Int_to_String(control_state,Control_State);
				strcat(USART3_TX_BUF,Control_State);
			}
			
			/********************对于系统状态量的查询*******************/
			else		//直接读取全局变量，然后上传
			{
				float para_value = 0;
				uint8_t  Para_Value[Max_Length_Para];
				if(strcmp(FRAME.Vari,"RS") == 0)
				{
					Int_to_String(System_Mode,Para_Value);
					strcat(USART3_TX_BUF,Para_Value);
				}
				else
				{
					if(strcmp(FRAME.Vari,"T") == 0)
					{
					
						switch(FRAME.VariID)
						{
							case 101:
								para_value = value_temhumi.Tem_External;
							break;
							case 103:
								para_value = value_temhumi.Tem_HeatExchanger;
							break;
							case 301:
								para_value = value_temhumi.Tem_Evapsurface;
							break;
//							case 401:
//								para_value = value_temhumi.Tem_Compressor;
//							break;
						}
						Float_to_String(para_value,Para_Value,1);
					}
					else if(strcmp(FRAME.Vari,"H") == 0)
					{
						switch(FRAME.VariID)
						{
							case 102:
								para_value = value_temhumi.Humi_External;
							break;
							case 104:
								para_value = value_temhumi.Humi_HeatExchanger;
							break;
						}
						Float_to_String(para_value,Para_Value,1);
					}
					else if(strcmp(FRAME.Vari,"F") == 0)
					{
						switch(FRAME.VariID)
						{
							case 201:
								para_value = value_Compressor.Quan_Airflow_Value;
							break;
							case 202:
								para_value = value_Compressor.Quan_Airflow_Value_Sum;
							break;
						}
						Float_to_String(para_value,Para_Value,1);
					}
//					else if(strcmp(FRAME.Vari,"P") == 0)
//					{
//						switch(FRAME.VariID)
//						{
//							case 402:
//								para_value = value_Compressor.Pre_Compressor_IN;
//							break;
//							case 403:
//								para_value = value_Compressor.Pre_Compressor_OUT;
//							break;
//						}
//						Float_to_String(para_value,Para_Value,3);
//					}
					else if(strcmp(FRAME.Vari,"V") == 0)
					{
						switch(FRAME.VariID)
						{
							case 501:
								para_value = value_volume_tank.Volume_Tank_Present;
							  Float_to_String(para_value,Para_Value,3);
							break;
							case 502:
								para_value = value_volume_tank.Volume_Tank_Day;
							  Float_to_String(para_value,Para_Value,1);
							break;
							case 503:
								para_value = value_volume_tank.Volume_Tank_Month;
							  Float_to_String(para_value,Para_Value,1);
							break;
							case 504:
								para_value = value_volume_tank.Volume_Tank_Year;
							  Float_to_String(para_value,Para_Value,1);
							break;
							case 505:
								para_value = value_volume_tank.Volume_Tank_Sum;
							  Float_to_String(para_value,Para_Value,1);
							break;
							case 506:
								para_value = value_volume_tank.Volume_Tank_Theory;
							  Float_to_String(para_value,Para_Value,1);
							break;
						}
						
					}
					/*******************关于电能表相关参数********************************/
					else if(strcmp(FRAME.Vari,"EE") == 0)
					{
						switch(FRAME.VariID)
						{
							case 601:
								para_value = value_power_consumption.PowerConsum_Day;
							break;
							case 602:
								para_value = value_power_consumption.PowerConsum_Month;
							break;
							case 603:
								para_value = value_power_consumption.PowerConsum_Year;
							break;
							case 604:
								para_value = value_power_consumption.PowerConsum_Sum;
							break;
						}
						Float_to_String(para_value,Para_Value,1);
					}
					else if(strcmp(FRAME.Vari,"E") == 0)
					{
						switch(FRAME.VariID)
						{
							case 701:
								para_value = value_energy_consumpRatio.ECR_Day;
							break;
							case 702:
								para_value = value_energy_consumpRatio.ECR_Month;
							break;
							case 703:
								para_value = value_energy_consumpRatio.ECR_Year;
							break;
							case 704:
								para_value = value_energy_consumpRatio.ECR_Sum;
							break;
						}
						Float_to_String(para_value,Para_Value,1);
					}
					else 
					{
						if(strcmp(FRAME.Vari,"EUA") == 0)
						{
							para_value = value_power_consumption.Voltage_EUA;
							//Float_to_String(para_value,Para_Value,1);
						}
						else if(strcmp(FRAME.Vari,"EUB") == 0)
						{
							para_value = value_power_consumption.Voltage_EUB;
							
							//Float_to_String(para_value,Para_Value,1);
						}
						else if(strcmp(FRAME.Vari,"EUC") == 0)
						{
							para_value = value_power_consumption.Voltage_EUC;
							//Float_to_String(para_value,Para_Value,1);
						}
					
				
						else if(strcmp(FRAME.Vari,"EPQ") == 0)
						{
							para_value = value_power_consumption.Power_EPQ;
							//Float_to_String(para_value,Para_Value,2);
						}
						else if(strcmp(FRAME.Vari,"EIA") == 0)
						{
							para_value = value_power_consumption.Current_EIA;
							//Float_to_String(para_value,Para_Value,2);
						}
						else if(strcmp(FRAME.Vari,"EIB") == 0)
						{
							para_value = value_power_consumption.Current_EIB;
							//Float_to_String(para_value,Para_Value,2);
						}
						else if(strcmp(FRAME.Vari,"EIC") == 0)
						{
							para_value = value_power_consumption.Current_EIC;
							//Float_to_String(para_value,Para_Value,2);
						}
						
						Float_to_String(para_value,Para_Value,1);
						
					}
					
					/******将参数值转变成字符表示，并合并到应答缓冲数组中******/
					//Float_to_String(para_value,Para_Value,PRECISION);
					strcat(USART3_TX_BUF,Para_Value);
				}
			}
	
			/*******************发送函数部分****************************/
			for(t=0;t<strlen(USART3_TX_BUF);t++)
			{
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
				USART_SendData(USART3, USART3_TX_BUF[t]);         //向串口1发送数据
			}
			while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
			
		break;
		
		case 0xF2:	//操作命令，完成相应控制，返回此时的状态
			Copy_RxBuf_to_TxBuf(Frame_Store[SeqNum_Frame_Deal],USART3_TX_BUF);
		  //uint8_t Control_State_Present[Max_Length_State];
			switch(FRAME.VariID)
			{
				
				case 101:		//风机启停
					if(FRAME.Parameter2 == 1)		//启动
					{
						VariState.Fan_New_State = 1;
					}
					if(FRAME.Parameter2 == 0)		//停止
					{
						VariState.Fan_New_State = 0;
					}
					delay_ms(120);
					FAN_Control(VariState.Fan_New_State);
					Int_to_String(VariState.Fan_New_State,Control_State);
					break;
					
				case 102:		//压缩机启停
					if(FRAME.Parameter2 == 1)		//启动
					{
						VariState.Compressor_State = 1;
						
					}
					if(FRAME.Parameter2 == 0)		//停止
					{
						VariState.Compressor_State = 0;
					}
					delay_ms(120);
					Compressor1_Control(VariState.Compressor_State);
					delay_ms(120);
					UV_Control(VariState.Compressor_State);
					
					Int_to_String(VariState.Compressor_State,Control_State);
					break;
					
				case 103:		//水泵启停
					if(FRAME.Parameter2 == 1)		//启动
					{
						VariState.Pump_State = 1;
					}
					if(FRAME.Parameter2 == 0)		//停止
					{
						VariState.Pump_State = 0;
					}
					delay_ms(120);
					PUMP_Control(VariState.Pump_State);
					Int_to_String(VariState.Pump_State,Control_State);
					break;
					
				case 104:		//进风口安全门开合
					if(FRAME.Parameter2 == 1)		//开门
					{
						VariState.AirIn_State = 1;
						Open_InDoor_Flag=1;
//						 Flag_Door =1;
					}
					if(FRAME.Parameter2 == 0)		//关门
					{
						VariState.AirIn_State = 0;
						Close_InDoor_Flag=1;
//						 Flag_Door =1;
					}
					delay_ms(120);
					Door_AirIn_Control(VariState.AirIn_State);
					delay_ms(10);
					Int_to_String(VariState.AirIn_State,Control_State);
					break;
					
				case 105:		//出风口安全门开合
					if(FRAME.Parameter2 == 1)		//开门
					{
						VariState.AirOut_State = 1;
//						Close_OutDoor_Flag=1;
//						 Flag_Door =1;
						Open_OutDoor_Flag=1;
					}
					if(FRAME.Parameter2 == 0)		//关门
					{
						Close_OutDoor_Flag=1;
//						 Flag_Door =1;
//						Open_OutDoor_Flag=1;
						VariState.AirOut_State = 0;
					}
					delay_ms(120);
					Door_AirOut_Control(VariState.AirOut_State);
					delay_ms(10);
					Int_to_String(VariState.AirOut_State,Control_State);
					break;
					
				case 106:		//整机启停
					if(FRAME.Parameter2 == 1)		//启动
					{
						VariState.System_State = 1;
						Flag_Debug = 0;
						System_Mode = 1;//设置成制水模式
//						if(Flag_Count_Setting_Para) //将参数保存至flash中
//						{
//							Flag_Count_Setting_Para = 0;
//							
//							
//							//保存数据
//						}
					}
					if(FRAME.Parameter2 == 0)		//停止
					{
						System_Mode = 0;
						VariState.System_State = 0;
						Flag_Debug = 1;
					}
					Int_to_String(VariState.System_State,Control_State);
					break;
					
				case 107:		//系统自检
					if(FRAME.Parameter2 == 1)		//开启自检
					{
						VariState.SysCheck_State = 1;
						SysCheck();
					}
					if(FRAME.Parameter2 == 0)		//停止
					{
						VariState.SysCheck_State = 0;
					}				
					
					Int_to_String(VariState.SysCheck_State,Control_State);				
					break;
					
				case 108:		//导出数据
					if(FRAME.Parameter2 == 0)		//导出数据请求
					{
						VariState.DataTranfer_State = 0;
						DataTranfer_Flag=1;
					}
					/*if(FRAME.Parameter2 == 0)		//停止
					{
						VariState.DataTranfer_State = 0;
					}*/
					Int_to_String(VariState.DataTranfer_State,Control_State);
					break;
					
				case 109:		//启用时段控
					if(FRAME.Parameter2 == 1)		//开启时段控
					{
						VariState.TimeControl_State = 1;
					}
					if(FRAME.Parameter2 == 0)		//关闭时段控
					{
						VariState.TimeControl_State = 0;
					}
					Int_to_String(VariState.TimeControl_State,Control_State);
					break;
				case 110:  //总风机控制
					if(FRAME.Parameter2 == 1)  //启动
					{
						VariState.Fan_Total_State = 1;
					}
					if(FRAME.Parameter2 == 0)  //停止
					{
						VariState.Fan_Total_State = 0;
					}
					delay_ms(120);
					Fan_Total_Control(VariState.Fan_Total_State);
					Int_to_String(VariState.Fan_Total_State,Control_State);
					break;
			
				case 111:  //控制
					if(FRAME.Parameter2 == 1)  //启动
					{
						VariState.ALARM_State = 1;
					}
					if(FRAME.Parameter2 == 0)  //停止
					{
						VariState.ALARM_State = 0;
					}
					delay_ms(120);
					ALARM_Show_Control(VariState.ALARM_State);
					Int_to_String(VariState.ALARM_State,Control_State);
			}
			/************************操作指令的应答部分**********************************/
			strcat(USART3_TX_BUF,Control_State);
			/*******************发送函数部分****************************/
			for(t=0;t<strlen(USART3_TX_BUF);t++)
			{
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
				USART_SendData(USART3, USART3_TX_BUF[t]);         //向串口1发送数据
			}
			while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
			break;
			
		case 0xF3:	//设置命令，保存至全局变量，以便后续写入flash
			if((FRAME.VariID == 118)||(FRAME.VariID == 119))
			{
				printf("OK\n");
			}
			break;
	}
	return 1;
}
/** 
  * @brief  提取极限参数 
  */ 
void AbsoluteParaStore(void)
{
	switch(FRAME.VariID)
	{
			case 101:
			AbsolutePara.Humi_External_DOWN = FRAME.Parameter1;
			break;
		case 102:
			AbsolutePara.Tem_External_UP = FRAME.Parameter1;
			break;
		case 103:
			AbsolutePara.Tem_External_DOWN = FRAME.Parameter1;
		//
		Write_Para_ToFlashC(0);
			break;
		case 104:
			AbsolutePara.Tem_Evapsurf_DOWN = FRAME.Parameter1;
			break;
//		case 105:
//			AbsolutePara.Tem_Evapsurf_UP = FRAME.Parameter1;
//			break;
		case 106:
			AbsolutePara.Level_Tank_UP = FRAME.Parameter1;
			break;
		case 107:
			AbsolutePara.Level_Tank_DOWN = FRAME.Parameter1;
		//
			Write_Para_ToFlashC(0);
		
			break;
		case 108:
			AbsolutePara.Quan_Airflow_DOWN = FRAME.Parameter1;
		//
			Write_Para_ToFlashC(0);
			break;
//		case 109:
//			AbsolutePara.Pre_High_DOWN = FRAME.Parameter1;
//			break;
//		case 110:
//			AbsolutePara.Pre_Low_DOWN = FRAME.Parameter1;
//			break;
	}
	
}
/** 
  * @brief    提取时间校正参数
  * @param  
  * @retval 
  */ 
void SetTime_Data(u8 *s)
{
	uint8_t i=0,SetTimeState=0;
	
	u8 ampm;
	//assert(s != NULL); //判断字符串是否为空 
	while(s[i] != '=') i++; //除去等号前的变量符号的内容
	i = i + 3;               //指向等号后第一个量
	
	SETTIME.Year_Set = (s[i]-'0')*10+(s[i+1]-'0');
	SETTIME.Mon_Set = (s[i+2]-'0')*10+(s[i+3]-'0');
	SETTIME.Date_Set = (s[i+4]-'0')*10+(s[i+5]-'0');
	SETTIME.Hour_Set = (s[i+6]-'0')*10+(s[i+7]-'0');
	SETTIME.Min_Set = (s[i+8]-'0')*10+(s[i+9]-'0');
	SETTIME.Sec_Set = (s[i+10]-'0')*10+(s[i+11]-'0');
	/*	
	if(SETTIME.Hour_Set > 12)
	{
		SETTIME.Hour_Set -= 12;
		ampm = RTC_H12_PM;
	}
	else
	{
		ampm = RTC_H12_AM;
	}
	*/	
	
	SetTimeState=RTC_Set_Date(SETTIME.Year_Set,SETTIME.Mon_Set,SETTIME.Date_Set,5);
	if(!SetTimeState) RTC_Set_Date(SETTIME.Year_Set,SETTIME.Mon_Set,SETTIME.Date_Set,5);
	SetTimeState=RTC_Set_Time(SETTIME.Hour_Set,SETTIME.Min_Set,SETTIME.Sec_Set,0);
	if(!SetTimeState) RTC_Set_Time(SETTIME.Hour_Set,SETTIME.Min_Set,SETTIME.Sec_Set,0);
}
/** 
  * @brief   从USART_RX_BUF[USART_REC_LEN]复制变量符号到USART_TX_BUF[USART_TRM_LEN]
  * @param  例如"a="
  * @retval 
  */
 void Copy_RxBuf_to_TxBuf(u8 *rx_buf,u8 *tx_buf)
 {
	 
	 uint8_t i=0;
	 //assert(rx_buf != NULL); //判断字符串是否为空 
	 while(rx_buf[i] != '=')
	 {
		 tx_buf[i] = rx_buf[i];
		 i++;
	 }
	 tx_buf[i] = rx_buf[i];
	 tx_buf[i+1] = '\0';
 }
 /** 
  * @brief 
  * @param 提取字符串中等号'='后的字符,存入字符数组中 
  * @retval 
  */ 
uint8_t Extract_String(u8 *s,u8 *d)
{
	u8 i = 0,j = 0;
	if(s[0]==':')
	{
		while(s[i] != '=') i++; //除去等号前的变量符号的内容
		i++;               //指向等号后第一个量
//		while(is_letter(s[i]))
		while(is_digit(s[i]))
		{
			d[j++] = s[i++];
		}
		d[j++] = '\r';
		d[j++] = '\n';
		//d[j] = '\0';
		return 1;
	}
	return 0;
}

/** 
  * @brief 提取字符串中等号'='前的字符,即提取变量名称
  * @param  
  * @retval 
  */ 
u8 Extract_VariableName(u8 *s)
{
	u8 i = 0;
	int16_t  value;
	if(s[0]==':')
	{
		i++;
		while(is_letter(s[i]))                 //首先将变量符号的字母部分存储在数组中
		{
			FRAME.Vari[i-1] = s[i];
			i++;
		}
		FRAME.Vari[i-1] = '\0';
		if(s[i] == '=')
			i++;
		 for(value = 0;is_digit(s[i]);i++)      //计算变量符号的数字部分
		{
			value = value*10+(s[i]-'0');
		}
		FRAME.VariID = value;
		return 1;
	}
	return 0;
}
/** 
  * @brief 判断现在时刻是否满足三个时段
  * @param  
  * @retval 
  */ 
u8 assert_Time_Date(RTC_TimeTypeDef* RTC_TimeStruct)
{
	u8 i = 0;
	for(i = 0; i < 3; i++)
	{
		if((RunTime[i].Start_Hour != RunTime[i].Stop_Hour)||(RunTime[i].Start_Min != RunTime[i].Stop_Min))
		{
			if((RunTime[i].Stop_Hour > RunTime[i].Start_Hour)||((RunTime[i].Stop_Hour == RunTime[i].Start_Hour)&&(RunTime[i].Stop_Min > RunTime[i].Start_Min)))
			{
				if((RTC_TimeStruct->RTC_Hours < 24)&&(RTC_TimeStruct->RTC_Minutes < 60))
				{
					if((RTC_TimeStruct->RTC_Hours > RunTime[i].Start_Hour)||((RTC_TimeStruct->RTC_Hours == RunTime[i].Start_Hour)&&(RTC_TimeStruct->RTC_Minutes > RunTime[i].Start_Min)))
					{
						if((RTC_TimeStruct->RTC_Hours < RunTime[i].Stop_Hour)||((RTC_TimeStruct->RTC_Hours == RunTime[i].Stop_Hour)&&(RTC_TimeStruct->RTC_Minutes < RunTime[i].Stop_Min)))
							return 1;
					}
				}
			}
		}
	}
	return 0;
}
/** 
  * @brief 向串口屏发送系统实时状态
  * @param  
  * @retval 
  */
void Show_SystemStatus(void)
{
//	RS232_Send_Data(":RS=0\r\n",7);
//	RS232_Send_Data(":RS=1\r\n",7);
//	RS232_Send_Data(":RS=2\r\n",7);
//	RS232_Send_Data(":RS=3\r\n",7);
//	
	
	//
	if(VariState.SysCheck_State) RS232_Send_Data(":RS=3\r\n",7);
	
	if(System_Mode==1) 	RS232_Send_Data(":RS=1\r\n",7);
	else if(System_Mode==2) 	RS232_Send_Data(":RS=2\r\n",7);
	else if(VariState.Fan_Total_State) RS232_Send_Data(":RS=0\r\n",7);
	
	
	
//	uint8_t  SystemStatus_Value[Max_Length_Para] = {0};
//	uint8_t t;
//	
//	USART3_TX_BUF[0] = ':';
//	USART3_TX_BUF[1] = 'R';
//	USART3_TX_BUF[2] = 'S';
//	USART3_TX_BUF[3] = '=';
//	USART3_TX_BUF[4] = '\0';
//		
//	Int_to_String(System_Mode,SystemStatus_Value);
//	strcat(USART3_TX_BUF,SystemStatus_Value);
//	
//	for(t=0;t<strlen(USART3_TX_BUF);t++)
//	{
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
//		USART_SendData(USART3, USART3_TX_BUF[t]);         //向串口1发送数据
//	}
//	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束	
}


void Show_SystemSensorData(void)
{
	  
    delay_ms(5);

	
}