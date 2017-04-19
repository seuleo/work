#include "DeviceAxis.h"
#include "can.h"
//#include "DataDeal.h"
#include "moto.h"
#include "string_deal.h" 
#include "pwm.h"


//数据存储功能；
//机械轴
DeviceAxis AxisX;	
DeviceAxis AxisY;	
DeviceAxis AxisZ;	

void AScanDevice(u8 D) //01
{
	 
	
}



void AxisApp()
{
	
}

void AInitDevice(u8 D) //41
{
  
	 MotoBackStep(AxisX.AMotoPosition);
	 
	 MotoInit();

	
}

void AClearErr(u8 D)   //42
{
	
	
	
}
void AxisEnable() //43
{
	 
	
}
void AxisDisable() //44
{
		
}

void AEmergyStop()//45
{

	
}

//  ack    ok  81 广播  82 读参数 83 写参数  84 发同步命令 85 异步命令 86本机状态
//  errack     c1  c2  c3 c4  c5 c6
//接收后执行完 应答
//应答后 接收到 再应答
//err 1,报文格式错误 2 数据效验粗无 3，无此数据项 4，写入参数超过有效范围；
void Command_Deal_Axis(u8 *s)
{
	u8 ReadData[8];
	
	if((s[0]==0x01)&&(s[1]==0x01))
	{
		
		ReadData[0] = 0x81;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
			case 0x01: 
				ReadData[3] = 0x03;
				AScanDevice(0x01);
			  CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
			//case 0x02 :
			default : break;
		}		
		
	}
	if((s[0]==0x02)&&(s[1]==0x01))
	{
		ReadData[0] = 0x82;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x02: 	
					ReadData[3] = AxisX.ASoftVerM;
				  ReadData[4] = AxisX.ASoftVerS;
				  ReadData[5] = AxisX.ASoftVer;
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				
				break;
				case 0x03: 
          Int32_to_Hex(ReadData,AxisX.ASoftTimer);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				
				break;
				case 0x04: 
        	ReadData[3] = AxisX.AHardwareVerM;
				  ReadData[4] = AxisX.AHardwareVerS;
				  ReadData[5] = AxisX.AHardwareVer;
				
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				break;			  
				case 0x05: 				
	        Int32_to_Hex(ReadData,AxisX.AHardwareTimer);
				
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x11: 
					 ReadData[3] = AxisX.AAdressID;
				   CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x12: 				
					ReadData[3] = AxisX.ABoudValue;
				  ReadData[4] = AxisX.ABoudValue>>8;
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x21: 	
					Int32_to_Hex(ReadData,AxisX.APositionDe);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x22: 
					Int32_to_Hex(ReadData,AxisX.APositionMem);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x31: 	
					Int32_to_Hex(ReadData,AxisX.ACoderDe);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x32: 	
					Int32_to_Hex(ReadData,AxisX.ACoderMem);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 033:	
					Int32_to_Hex(ReadData,AxisX.ASpeedDe);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x34: 	
					Int32_to_Hex(ReadData,AxisX.ASpeedMem);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;

				case 0x61:
					Int32_to_Hex(ReadData,AxisX.AMotoAccel);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x62: 
					Int32_to_Hex(ReadData,AxisX.AMotoInitAccel);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x63: 
					Int32_to_Hex(ReadData,AxisX.AMotoSpeed);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
		    case 0x64: 
					Int32_to_Hex(ReadData,AxisX.AMotoInitSpeed);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
			default : break;
				//err 
		}		
	}
	if((s[0]==0x03)&&(s[1]==0x01))
	{   
		
		ReadData[0] = 0x83;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
		   	case 0x02: 				
					AxisX.ASoftVerM=s[3];
				  AxisX.ASoftVerS=s[4];
				  AxisX.ASoftVer=s[5];
				  CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x03: 
					 AxisX.ASoftTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x04: 
					 AxisX.AHardwareVerM=s[3];
				   AxisX.AHardwareVerS=s[4];
				   AxisX.AHardwareVer=s[5];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x05: 
					 AxisX.AHardwareTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x11: 
					 AxisX.AAdressID = s[3];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x12: 
					 AxisX.ABoudValue =s[3]<<8;
				   AxisX.ABoudValue+=s[4];
				   CAN1_Send_Msg_id(ReadData,0x12,3);				   
				break;
				case 0x21: 
					  AxisX.APositionDe =Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x22: 
					  AxisX.APositionMem =Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x31: 
					  AxisX.ACoderDe=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x32: 
					  AxisX.ACoderMem=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 033: 
					  AxisX.ASpeedDe=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x34: 
						AxisX.ASpeedMem=Hex_to_Int32(s);
						CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				
				case 0x61: 
					  AxisX.AMotoAccel=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x62: 
					  AxisX.AMotoInitAccel=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x63: 
					  AxisX.AMotoSpeed=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
		    case 0x64:
				  	AxisX.AMotoInitSpeed=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
			default : break;
		}
		
		// 保存参数到FLASH中去；采用均衡算法；
		
		
	}
	
	//发同步命令 02 
	if((s[0]==0x04)&&(s[1]==0x01))
	{
		
  	ReadData[0] = 0x84;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
	 	switch(s[2])
		{
		   	
				case 0x41: 
					AInitDevice(0x01);
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x42: 
					AClearErr(0x01);
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x43: 
					AxisEnable();
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x44: 
					AxisDisable();
				  ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x45: 
					 AEmergyStop();
					 ReadData[3] = 0x02;
			     CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x51: 
			    	AxisX.AForDis=Hex_to_Float(s);
				    MotoCurrentStruct.Maccel= AxisX.AMotoAccel;
				    MotoCurrentStruct.Mdecel= AxisX.AMotoAccel;
				    MotoCurrentStruct.MotoSpeed=  AxisX.AMotoSpeed;
				
				    MotoForStep(AxisX.AForDis);
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x52: 
				    AxisX.ABackDis=Hex_to_Float(s);
				    MotoCurrentStruct.Maccel= AxisX.AMotoAccel;
				    MotoCurrentStruct.Mdecel= AxisX.AMotoAccel;
				    MotoCurrentStruct.MotoSpeed=   AxisX.AMotoSpeed;
				    
				    MotoForStep(AxisX.ABackDis);
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x53: 
				    AxisX.AInitDis=Hex_to_Float(s);
//				MotoCurrentStruct.Maccel= 
//				MotoCurrentStruct.Mdecel=
//				MotoCurrentStruct.MotoSpeed=
				
				    MotoInitForStep(AxisX.AInitDis);
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				
			default : break;
		}
	}
	
	// 01  Recive命令执行完毕  02 命令执行完毕
	if((s[0]==0x05)&&(s[1]==0x01))
	{
		
		ReadData[0] = 0x85;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x51: 
			    	AxisX.AForDis=Hex_to_Float(s);
				    ReadData[3] = 0x01;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				
				    MotoCurrentStruct.Maccel= AxisX.AMotoAccel;
				    MotoCurrentStruct.Mdecel= AxisX.AMotoAccel;
				    MotoCurrentStruct.MotoSpeed=  AxisX.AMotoSpeed;			
				    MotoForStep(AxisX.AForDis);
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x52: 
				    AxisX.ABackDis=Hex_to_Float(s);
				    ReadData[3] = 0x01;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				    MotoCurrentStruct.Maccel= AxisX.AMotoAccel;
				    MotoCurrentStruct.Mdecel= AxisX.AMotoAccel;
				    MotoCurrentStruct.MotoSpeed=   AxisX.AMotoSpeed;
				    MotoForStep(AxisX.ABackDis);
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);

				break;
				case 0x53: 
				    AxisX.AInitDis=Hex_to_Float(s);
				    ReadData[3] = 0x01;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				
            MotoInitForStep(AxisX.AInitDis);
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				
				break;

		  	default : break;
		}
	}
	if((s[0]==0x06)&&(s[1]==0x01))
	{
//				switch(s[2])
//		{
////		   	case 0x64: AScanDevice(0x01);
////				break;
//			default : break;
//		}
	}
	
	
}