#include "DeviceShou.h"
//孵育
#include "string_deal.h" 
#include "can.h"
//#include "DataDeal.h"
#include "moto.h"

 DeviceShou ShouX;

void SScanDevice(u8 D)
{
	
	
}


void SCapture()
{
	
}
void SPut()
{
	
}
void SRolationStop()
{
	
	
}
void SCaptureStop()
{
	
}

void SRolation(u16 anglevalue)
	
{
	
	
}
	

void InitStateLed()
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

void SInitDevice(u8 D)
{
	
}
void SStart()
{
	
	
}
void ShouApp()
{
}


//void InitFan()
//{
//	
//	
//}

void SEmergyStop()
{
	
	
}
//  ack    ok  81 广播  82 读参数 83 写参数  84 发同步命令 85 异步命令 86本机状态
//  errack     c1  c2  c3 c4  c5 c6
//接收后执行完 应答
//应答后 接收到 再应答
//err 1,报文格式错误 2 数据效验粗无 3，无此数据项 4，写入参数超过有效范围；
void Command_Deal_Shou(u8 *s)
{
	u8 ReadData[8];
	
	if((s[0]==0x01)&&(s[1]==0x04))
	{
		switch(s[2])
		{
			case 0x01: SScanDevice(0x01);
				break;
			//case 0x02 :
			default : break;
		}		
		
	}
	if((s[0]==0x02)&&(s[1]==0x04))
	{
		ReadData[0] = 0x82;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x02: 	
					ReadData[3] = ShouX.SSoftVerM;
				  ReadData[4] = ShouX.SSoftVerS;
				  ReadData[5] = ShouX.SSoftVer;
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				
				break;
				case 0x03: 
          Int32_to_Hex(ReadData,ShouX.SSoftTimer);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				
				break;
				case 0x04: 
        	ReadData[3] = ShouX.SHardwareVerM;
				  ReadData[4] = ShouX.SHardwareVerS;
				  ReadData[5] = ShouX.SHardwareVer;
				
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				break;			  
				case 0x05: 				
	        Int32_to_Hex(ReadData,ShouX.SHardwareTimer);
				
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x11: 
					 ReadData[3] = ShouX.SAdressID;
				   CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x12: 				
					ReadData[3] = ShouX.SBoudValue;
				  ReadData[4] = ShouX.SBoudValue>>8;
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				
				case 0x31: 	
				//	Int32_to_Hex(ReadData,ShouX.HatchTemper);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x32: 	
				//	ReadData[3]=ShouX.HatchTime;
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x41:	
				//	ReadData[3]=ShouX.HRealTemper;   ////////////////////////////////
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x42: 	
				//	Int32_to_Hex(ReadData,ShouX.HRealTemper);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;

			default : break;
				//err 
		}		
	}
	if((s[0]==0x03)&&(s[1]==0x04))
	{   
		
		ReadData[0] = 0x83;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
		   	case 0x02: 				
					ShouX.SSoftVerM=s[3];
				  ShouX.SSoftVerS=s[4];
				  ShouX.SSoftVer=s[5];
				  CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x03: 
					 ShouX.SSoftTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x04: 
					 ShouX.SHardwareVerM=s[3];
				   ShouX.SHardwareVerS=s[4];
				   ShouX.SHardwareVer=s[5];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x05: 
					 ShouX.SHardwareTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x11: 
					 ShouX.SAdressID = s[3];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x12: 
					 ShouX.SBoudValue =s[3]<<8;
				   ShouX.SBoudValue+=s[4];
				   CAN1_Send_Msg_id(ReadData,0x12,3);				   
				break;
			
				case 0x31: 
					//  ShouX.HatchTemper=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x32: 
					 // ShouX.HatchTime=s[3];
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
//				case 0x41: 
//					  ShouX.RWorkState=s[3];
//				    CAN1_Send_Msg_id(ReadData,0x12,3);
//				break;

			default : break;
		}
		
		// 保存参数到FLASH中去；采用均衡算法；
		
		
	}
	
	//发同步命令 02 
	if((s[0]==0x04)&&(s[1]==0x04))
	{
		
  	ReadData[0] = 0x84;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
	 	switch(s[2])
		{
		   	
				case 0x21: 
					SInitDevice(0x01);
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
	if((s[0]==0x05)&&(s[1]==0x04))
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
	if((s[0]==0x06)&&(s[1]==0x04))
	{
//				switch(s[2])
//		{
////		   	case 0x64: AScanDevice(0x01);
////				break;
//			default : break;
//		}
	}
	
	
}