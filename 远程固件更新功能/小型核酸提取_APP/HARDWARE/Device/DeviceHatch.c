#include "DeviceHatch.h"
//孵育
#include "string_deal.h" 
#include "can.h"
//#include "DataDeal.h"
#include "moto.h"
#include "dac.h"
#include "exti.h"
#include "DeviceVibration.h"
#include "adc.h"
#include "timer.h"


DeviceHatch HatchX;

void HScanDevice(u8 D)
{
	
	
}
void HInitDevice(u8 D)
{
	//swtich;
	
	
	
	
	
	
}





void HStart()
{
	//err 
//	u16 temper;
//	temper=GetVoltageDAC0(HatchX.HatchTemper);
//	if(temper<40) temper=40;
//	if(temper>99) temper=99;
//	Dac1_Set_Vol(temper);
//	
//	//open switch ;
//	SwitchHot=1;
//	
		u16 temper;
	
  if(HatchX.HatchTemper<29) HatchX.HatchTemper=29;
	if(HatchX.HatchTemper>99) HatchX.HatchTemper=99;
	
	temper=GetVoltageDAC0(HatchX.HatchTemper);

	Dac1_Set_Vol(temper);
	
	//open switch ;
	SwitchHot=1;
	Flag_Hatch=1;
	
	
}
void HatchApp()
{
	
	
	
	
	
}


//void InitFan()
//{
//	
//	
//}

void HEmergyStop()
{
	Dac1_Set_Vol(2500);
	//stop switch;
	SwitchHot=0;
	
	
}

//  ack    ok  81 ??  82 ??? 83 ???  84 ????? 85 ???? 86????
//  errack     c1  c2  c3 c4  c5 c6
//?????? ??
//??? ??? ???
//err 1,?????? 2 ?????? 3,????? 4,??????????;
void Command_Deal_Hatch(u8 *s)
{
	u8 ReadData[8];
	
	if((s[0]==0x01)&&(s[1]==0x04))
	{
		switch(s[2])
		{
			case 0x01: HScanDevice(0x01);
				break;
			//case 0x02 :
			default : break;
		}		
		
	}
	if((s[0]==0x02)&&(s[1]==0x04))
	{
		ReadData[0] = 0x82;
		ReadData[1] = 0x04;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x02: 	
					ReadData[3] = HatchX.HSoftVerM;
				  ReadData[4] = HatchX.HSoftVerS;
				  ReadData[5] = HatchX.HSoftVer;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,6);
				
				break;
				case 0x03: 
          Int32_to_Hex(ReadData,HatchX.HSoftTimer);
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				
				break;
				case 0x04: 
        	ReadData[3] = HatchX.HHardwareVerM;
				  ReadData[4] = HatchX.HHardwareVerS;
				  ReadData[5] = HatchX.HHardwareVer;
				
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,6);
				break;			  
				case 0x05: 				
	        Int32_to_Hex(ReadData,HatchX.HHardwareTimer);
				
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				break;
				case 0x11: 
					 ReadData[3] = VibrationX.VAdressID;
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,4);
				break;
				case 0x12: 				
					ReadData[3] = HatchX.HBoudValue;
				  ReadData[4] = HatchX.HBoudValue>>8;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				break;
				
				case 0x31: 	
				//	Int32_to_Hex(ReadData,HatchX.HatchTemper);
				 // Int32_to_Hex(ReadData,HatchX.HRealTemper);
			//	  HatchX.HatchTime=Hex_to_Int32(s);
				 
				
				 ReadData[3]=HatchX.HatchTemper;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,4);
				break;
				case 0x32: 	
					
				  Int32_to_Hex(ReadData,HatchX.HatchTime);
					//ReadData[3]=HatchX.HatchTime;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				break;
				case 0x41:	
					
				 HatchX.HRealTemper =TableSearchTemperature();
				
					ReadData[3]=HatchX.HRealTemper;   ////////////////////////////////
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,4);
				break;
//				case 0x42: 	
//					//Int32_to_Hex(ReadData,HatchX.HRealTemper);
//				
//				  ReadData[3]=HatchX.HRealTemper;
//				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
//				break;

			default : break;
				//err 
		}		
	}
	if((s[0]==0x03)&&(s[1]==0x04))
	{   
		
		ReadData[0] = 0x83;
		ReadData[1] = 0x04;
		ReadData[2] = s[2];
		switch(s[2])
		{
		   	case 0x02: 				
					HatchX.HSoftVerM=s[3];
				  HatchX.HSoftVerS=s[4];
				  HatchX.HSoftVer=s[5];
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x03: 
					 HatchX.HSoftTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x04: 
					 HatchX.HHardwareVerM=s[3];
				   HatchX.HHardwareVerS=s[4];
				   HatchX.HHardwareVer=s[5];
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x05: 
					 HatchX.HHardwareTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x11: 
					 VibrationX.VAdressID = s[3];
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x12: 
					 HatchX.HBoudValue =s[3]<<8;
				   HatchX.HBoudValue+=s[4];
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);				   
				break;
			
				case 0x31: 
					  //HatchX.HatchTemper=Hex_to_Int32(s);
				    HatchX.HatchTemper= s[3];
			    	CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x32: 
					  HatchX.HatchTime=Hex_to_Int32(s);
				
			    	CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
//				case 0x41: 
//					  HatchX.RWorkState=s[3];
//				    CAN1_Send_Msg_id(ReadData,0x12,3);
//				break;

			default : break;
		}
		
		// ?????FLASH??;??????;
		
		
	}
	
	
	
	
		if((s[0]==0x12)&&(s[1]==0x04))
	{
		ReadData[0] = 0x92;
		ReadData[1] = 0x04;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x02: 	
					ReadData[3] = HatchX.HSoftVerM;
				  ReadData[4] = HatchX.HSoftVerS;
				  ReadData[5] = HatchX.HSoftVer;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,6);
				
				break;
				case 0x03: 
          Int32_to_Hex(ReadData,HatchX.HSoftTimer);
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				
				break;
				case 0x04: 
        	ReadData[3] = HatchX.HHardwareVerM;
				  ReadData[4] = HatchX.HHardwareVerS;
				  ReadData[5] = HatchX.HHardwareVer;
				
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,6);
				break;			  
				case 0x05: 				
	        Int32_to_Hex(ReadData,HatchX.HHardwareTimer);
				
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				break;
				case 0x11: 
					 ReadData[3] = VibrationX.VAdressID;
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,4);
				break;
				case 0x12: 				
					ReadData[3] = HatchX.HBoudValue;
				  ReadData[4] = HatchX.HBoudValue>>8;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				break;
				
				case 0x31: 	
				//	Int32_to_Hex(ReadData,HatchX.HatchTemper);
				 // Int32_to_Hex(ReadData,HatchX.HRealTemper);
			//	  HatchX.HatchTime=Hex_to_Int32(s);
				 
				
				 ReadData[3]=HatchX.HatchTemper;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,4);
				break;
				case 0x32: 	
					
				  Int32_to_Hex(ReadData,HatchX.HatchTime);
					//ReadData[3]=HatchX.HatchTime;
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
				break;
				case 0x41:	
					
				 HatchX.HRealTemper =TableSearchTemperature();
				
					ReadData[3]=HatchX.HRealTemper;   ////////////////////////////////
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,4);
				break;
//				case 0x42: 	
//					//Int32_to_Hex(ReadData,HatchX.HRealTemper);
//				
//				  ReadData[3]=HatchX.HRealTemper;
//				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,7);
//				break;

			default : break;
				//err 
		}		
	}
	if((s[0]==0x13)&&(s[1]==0x04))
	{   
		
		ReadData[0] = 0x93;
		ReadData[1] = 0x04;
		ReadData[2] = s[2];
		switch(s[2])
		{
		   	case 0x02: 				
					HatchX.HSoftVerM=s[3];
				  HatchX.HSoftVerS=s[4];
				  HatchX.HSoftVer=s[5];
				  CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x03: 
					 HatchX.HSoftTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x04: 
					 HatchX.HHardwareVerM=s[3];
				   HatchX.HHardwareVerS=s[4];
				   HatchX.HHardwareVer=s[5];
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x05: 
					 HatchX.HHardwareTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x11: 
					 VibrationX.VAdressID = s[3];
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x12: 
					 HatchX.HBoudValue =s[3]<<8;
				   HatchX.HBoudValue+=s[4];
				   CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);				   
				break;
			
				case 0x31: 
					  //HatchX.HatchTemper=Hex_to_Int32(s);
				    HatchX.HatchTemper= s[3];
			    	CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x32: 
					  HatchX.HatchTime=Hex_to_Int32(s);
				
			    	CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
//				case 0x41: 
//					  HatchX.RWorkState=s[3];
//				    CAN1_Send_Msg_id(ReadData,0x12,3);
//				break;

			default : break;
		}
		
		// ?????FLASH??;??????;
		
		
	}
	
	
	
	
	
	//????? 02 
	if((s[0]==0x04)&&(s[1]==0x04))
	{
		
  	ReadData[0] = 0x84;
		ReadData[1] = 0x04;
		ReadData[2] = s[2];
	 	switch(s[2])
		{
		   	
				case 0x21: 
					HInitDevice(0x01);
				//	ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,4);
				break;
				case 0x22: 
					HStart();
				
				
				//	ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x23: 
					
			  	HEmergyStop();
				//	ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;


			default : break;
		}
	}
//	
		//????? 02 
	if((s[0]==0x14)&&(s[1]==0x04))
	{
		
  	ReadData[0] = 0x94;
		ReadData[1] = 0x04;
		ReadData[2] = s[2];
	 	switch(s[2])
		{
		   	
				case 0x21: 
					HInitDevice(0x01);
//					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x22: 
					HStart();
				
				
				//	ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;
				case 0x23: 
					
			  	HEmergyStop();
				//	ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,VibrationX.VAdressID,3);
				break;

			default : break;
		}
	}
}










//  ack    ok  81 广播  82 读参数 83 写参数  84 发同步命令 85 异步命令 86本机状态
//  errack     c1  c2  c3 c4  c5 c6
//接收后执行完 应答
//应答后 接收到 再应答
//err 1,报文格式错误 2 数据效验粗无 3，无此数据项 4，写入参数超过有效范围；
//void Command_Deal_Hatch(u8 *s)
//{
//	u8 ReadData[8];
//	
//	if((s[0]==0x01)&&(s[1]==0x04))
//	{
//		switch(s[2])
//		{
//			case 0x01: HScanDevice(0x01);
//				break;
//			//case 0x02 :
//			default : break;
//		}		
//		
//	}
//	if((s[0]==0x02)&&(s[1]==0x04))
//	{
//		ReadData[0] = 0x82;
//		ReadData[1] = 0x01;
//		ReadData[2] = s[2];
//		switch(s[2])
//		{
//				case 0x02: 	
//					ReadData[3] = HatchX.HSoftVerM;
//				  ReadData[4] = HatchX.HSoftVerS;
//				  ReadData[5] = HatchX.HSoftVer;
//				  CAN1_Send_Msg_id(ReadData,0x12,6);
//				
//				break;
//				case 0x03: 
//          Int32_to_Hex(ReadData,HatchX.HSoftTimer);
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,7);
//				
//				break;
//				case 0x04: 
//        	ReadData[3] = HatchX.HHardwareVerM;
//				  ReadData[4] = HatchX.HHardwareVerS;
//				  ReadData[5] = HatchX.HHardwareVer;
//				
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,6);
//				break;			  
//				case 0x05: 				
//	        Int32_to_Hex(ReadData,HatchX.HHardwareTimer);
//				
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,7);
//				break;
//				case 0x11: 
//					 ReadData[3] = HatchX.HAdressID;
//				   CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				break;
//				case 0x12: 				
//					ReadData[3] = HatchX.HBoudValue;
//				  ReadData[4] = HatchX.HBoudValue>>8;
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,7);
//				break;
//				
//				case 0x31: 	
//					Read_HatchTemper_FromFlash(1);
//				
//					Int32_to_Hex(ReadData,HatchX.HatchTemper);
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,7);
//				break;
//				case 0x32: 	
//					
//				  Read_HatchTime_FromFlash(1);
//				  Int32_to_Hex(ReadData,HatchX.HatchTime);
//					//ReadData[3]=HatchX.HatchTime;
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,7);
//				break;
//				 
//				case 0x41:	
//					ReadData[3]=HatchX.HRealTemper;   ////////////////////////////////
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,7);
//				break;
//				case 0x42: 	
//					Int32_to_Hex(ReadData,HatchX.HRealTemper);
//				  CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,7);
//				break;

//			default : break;
//				//err 
//		}		
//	}
//	if((s[0]==0x03)&&(s[1]==0x04))
//	{   
//		
//		ReadData[0] = 0x83;
//		ReadData[1] = 0x01;
//		ReadData[2] = s[2];
//		switch(s[2])
//		{
////		   	case 0x02: 				
////					HatchX.HSoftVerM=s[3];
////				  HatchX.HSoftVerS=s[4];
////				  HatchX.HSoftVer=s[5];
////				  CAN1_Send_Msg_id(ReadData,0x12,3);
////				break;
////				case 0x03: 
////					 HatchX.HSoftTimer=Hex_to_Int32(s);
////				   CAN1_Send_Msg_id(ReadData,0x12,3);
////				break;
////				case 0x04: 
////					 HatchX.HHardwareVerM=s[3];
////				   HatchX.HHardwareVerS=s[4];
////				   HatchX.HHardwareVer=s[5];
////				   CAN1_Send_Msg_id(ReadData,0x12,3);
////				break;
////				case 0x05: 
////					 HatchX.HHardwareTimer=Hex_to_Int32(s);
////				   CAN1_Send_Msg_id(ReadData,0x12,3);
////				break;
//				case 0x11: 
//					 HatchX.HAdressID = s[3];
//				   CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,3);
//				break;
//				case 0x12: 
//					 HatchX.HBoudValue =s[3]<<8;
//				   HatchX.HBoudValue+=s[4];
//				   CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,3);				   
//				break;
//			
//				case 0x31: 
//					  HatchX.HatchTemper=Hex_to_Int32(s);
//				    Write_HatchTemper_ToFlash(1);
//				
//			    	CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,3);
//				break;
//				case 0x32: 
//					  HatchX.HatchTime=s[3];
//				
//				    Write_HatchTime_ToFlash(1);
//				
//			    	CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,3);
//				break;
////				case 0x41: 
////					  HatchX.RWorkState=s[3];
////				    CAN1_Send_Msg_id(ReadData,0x12,3);
////				break;

//			default : break;
//		}
//		
//		// 保存参数到FLASH中去；采用均衡算法；
//		
//		
//	}
//	
//	//发同步命令 02 
//	if((s[0]==0x04)&&(s[1]==0x04))
//	{
//		
//  	ReadData[0] = 0x84;
//		ReadData[1] = 0x01;
//		ReadData[2] = s[2];
//	 	switch(s[2])
//		{
//		   	
//				case 0x21: 
//					HInitDevice(0x01);
//					ReadData[3] = 0x02;
//			    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				break;
//				case 0x22: 
//					
//					ReadData[3] = 0x02;
//			    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				break;
//				case 0x23: 
//					
//					ReadData[3] = 0x02;
//			    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				break;
//				case 0x44: 
//					
//				  ReadData[3] = 0x02;
//			    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				break;
//				case 0x45: 
//					 
//					 ReadData[3] = 0x02;
//			     CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				break;

//			default : break;
//		}
//	}
//	
//	// 01  Recive命令执行完毕  02 命令执行完毕
//	if((s[0]==0x05)&&(s[1]==0x04))
//	{
//		
//		ReadData[0] = 0x85;
//		ReadData[1] = 0x01;
//		ReadData[2] = s[2];
//		switch(s[2])
//		{
//				case 0x51: 

//				    ReadData[3] = 0x02;
//				    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				break;
//				case 0x52: 
//		
//				    ReadData[3] = 0x01;

//				    ReadData[3] = 0x02;
//				    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);

//				break;
//				case 0x53: 
//		
//				    ReadData[3] = 0x01;
//				    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				
//  
//				    ReadData[3] = 0x02;
//				    CAN1_Send_Msg_id(ReadData,HatchX.HAdressID,4);
//				
//				break;

//		  	default : break;
//		}
//	}
//	if((s[0]==0x06)&&(s[1]==0x04))
//	{
////				switch(s[2])
////		{
//////		   	case 0x64: AScanDevice(0x01);
//////				break;
////			default : break;
////		}
//	}
//	
//	
//}