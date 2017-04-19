#include "DeviceReagent.h"
#include "string_deal.h" 
//试剂

#include "can.h"
//#include "DataDeal.h"
#include "moto.h"

//OPEN ONE TIMER TO CONTROL TEMP TO GET TEMP TO UPDATE TO PC 
// 	char Para_Data[30]={0};  Float_to_String2(value_volume_tank.Volume_Tank_Day,Para_Value,1);       //????? / strcat(Para_Data,Time_Date);  
//	 strcat(Para_Data,"\r\n");        TC1:TCACTUALTEMP=21.14   TC1:TCACTUALTEMP?\r  TC1:TCADJUSTTEMP=8.00  TC1:TCADJUSTTEMP?    @0
//   TC1:TCMODE? TC1:TCMODE=0 TC1:TCSW? TC1:TCSW=0 TC1:TCOE?  TC1:TCOE=0   //most important 
//TC1:TCSETVOLTAGE? TC1:TCSETVOLTAGE=0.00 TC1:TCACTUALVOLTAGE? TC1:TCACTUALVOLTAGE=0.09  TC1:TCACTUALCURRENT?  TC1:TCACTUALCURRENT=0.16 TC1:TCHARDWARE?  TC1:TCHARDWARE=1


DeviceReagent ReagentX;

void RScanDevice(u8 D)
{
	
	
}
void RInitDevice(u8 D)
{
	
}
void RStart()
{
	
	
}

void ReagentApp()
{
	
	
}


void InitFan()
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//??GPIOF??

  //GPIOF9,F10?????
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??
  GPIO_Init(GPIOF, &GPIO_InitStructure);//???
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9);//GPIOF9,F10???,??
}

void REmergyStop()
{
	
	
}
//  ack    ok  81 广播  82 读参数 83 写参数  84 发同步命令 85 异步命令 86本机状态
//  errack     c1  c2  c3 c4  c5 c6
//接收后执行完 应答
//应答后 接收到 再应答
//err 1,报文格式错误 2 数据效验粗无 3，无此数据项 4，写入参数超过有效范围；
void Command_Deal_Reagent(u8 *s)
{
	u8 ReadData[8];
	
	if((s[0]==0x01)&&(s[1]==0x05))
	{
		switch(s[2])
		{
			case 0x01: RScanDevice(0x01);
				break;
			//case 0x02 :
			default : break;
		}		
		
	}
	if((s[0]==0x02)&&(s[1]==0x05))
	{
		ReadData[0] = 0x82;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x02: 	
					ReadData[3] = ReagentX.RSoftVerM;
				  ReadData[4] = ReagentX.RSoftVerS;
				  ReadData[5] = ReagentX.RSoftVer;
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				
				break;
				case 0x03: 
          Int32_to_Hex(ReadData,ReagentX.RSoftTimer);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				
				break;
				case 0x04: 
        	ReadData[3] = ReagentX.RHardwareVerM;
				  ReadData[4] = ReagentX.RHardwareVerS;
				  ReadData[5] = ReagentX.RHardwareVer;
				
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				break;			  
				case 0x05: 				
	        Int32_to_Hex(ReadData,ReagentX.RHardwareTimer);
				
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x11: 
					 ReadData[3] = ReagentX.RAdressID;
				   CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x12: 				
					ReadData[3] = ReagentX.RBoudValue;
				  ReadData[4] = ReagentX.RBoudValue>>8;
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				
				case 0x31: 	
					Int32_to_Hex(ReadData,ReagentX.ReagentTemper);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x32: 	
					ReadData[3]=ReagentX.ReagentTime;
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x41:	
					ReadData[3]=ReagentX.RWorkState;
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x42: 	
					Int32_to_Hex(ReadData,ReagentX.RRealTemper);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;

			default : break;
				//err 
		}		
	}
	if((s[0]==0x03)&&(s[1]==0x05))
	{   
		
		ReadData[0] = 0x83;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
		   	case 0x02: 				
					ReagentX.RSoftVerM=s[3];
				  ReagentX.RSoftVerS=s[4];
				  ReagentX.RSoftVer=s[5];
				  CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x03: 
					 ReagentX.RSoftTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x04: 
					 ReagentX.RHardwareVerM=s[3];
				   ReagentX.RHardwareVerS=s[4];
				   ReagentX.RHardwareVer=s[5];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x05: 
					 ReagentX.RHardwareTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x11: 
					 ReagentX.RAdressID = s[3];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x12: 
					 ReagentX.RBoudValue =s[3]<<8;
				   ReagentX.RBoudValue+=s[4];
				   CAN1_Send_Msg_id(ReadData,0x12,3);				   
				break;
			
				case 0x31: 
					  ReagentX.ReagentTemper=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x32: 
					  ReagentX.ReagentTime=s[3];
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x41: 
					  ReagentX.RWorkState=s[3];
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;

			default : break;
		}
		
		// 保存参数到FLASH中去；采用均衡算法；
		
		
	}
	
	//发同步命令 02 
	if((s[0]==0x04)&&(s[1]==0x05))
	{
		
  	ReadData[0] = 0x84;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
	 	switch(s[2])
		{
		   	
				case 0x21: 
					RInitDevice(0x01);
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x22: 
					
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x23: 
					
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x44: 
					
				  ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x45: 
					 
					 ReadData[3] = 0x02;
			     CAN1_Send_Msg_id(ReadData,0x12,4);
				break;

			default : break;
		}
	}
	
	// 01  Recive命令执行完毕  02 命令执行完毕
	if((s[0]==0x05)&&(s[1]==0x05))
	{
		
		ReadData[0] = 0x85;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x51: 

				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x52: 
		
				    ReadData[3] = 0x01;

				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);

				break;
				case 0x53: 
		
				    ReadData[3] = 0x01;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				
  
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				
				break;

		  	default : break;
		}
	}
	if((s[0]==0x06)&&(s[1]==0x05))
	{
//				switch(s[2])
//		{
////		   	case 0x64: AScanDevice(0x01);
////				break;
//			default : break;
//		}
	}
	
	
}