#include "DeviceMagnetic.h"
#include "pwm.h"
#include "math.h"

#include "Common.h"

//磁分离
#include "can.h"
#include "string_deal.h" 
//#include "DataDeal.h"
#include "moto.h"
//机械轴
DeviceMagnetic MagneticX;	

//volatile u8 Sending;
 u8 UpSlow = 1;

 u16 EEprom[7] = {0,0,0,0,0,0,1};    //各元素按顺序排列吸附距离、吸附速度、空载距离、空载速度、下降速度、移动速度、本模块地址

//char8 ComRecvBuff[60] = {0};		  //串口接收缓冲区
//u8 WriteP = 0;

//u8 FrameReady = 0;

 
u8 Up = 0;
u8 Down = 0;
//u8 Mov;
//u8 Direction;
//u8 MovDis;
 
u8 Write = 0;
u8 Read = 1;
u8 Reset = 0;
u8 ExeCmdFlag = 0;				  //命令执行成功/失败标志
 
u8 Direction ;

u8 Mov;
u8 Direction;
u16 MovDis;



u8 PositionJudge =0;
u32 CurrentPosition =0 ; 

void MScanDevice(u8 D)
{
	
	
}


void MagneticApp()
{
//		SFRPAGE = CONFIG_PAGE;
	if(INT1 == 1)				       //上电时如果不在0位（底端限位开关），则磁分离模块复位。
	{
		//MotorMov(1,8000,60000);		 
		// AxisMove(AB_cnt ,MotoCurrentStruct.Maccel, MotoCurrentStruct.Mdecel,MotoCurrentStruct.MotoSpeed);
		
	}
	
	/*********************************上升*********************************/
		if(Up == 1 && INT0 == 1 && INT1 == 0)			   //必须在最底端且不在最顶端时才允许向上运动，UP == 1 上升命令
{
			Up = 0;
			PositionJudge = 1;							   //上升运动标志
			
			MotorMov(0,EEprom[3],EEprom[2]);			   //空载运动或者快速运动
			if( UpSlow == 1)
			{
				MotorMov(0,EEprom[1],EEprom[0]);		   //吸附运动
			}
			PositionJudge = 0;

			if( abs(EEprom[2] + EEprom[0] - CurrentPosition) < 100)    //应答
			{
				ExeCmdFlag = 1;						   //命令执行成功			
			}
			else
			{
				ExeCmdFlag = 0;						   //命令执行失败
			}
		}
		else if(Up == 1 && INT0 == 0)
		{
			Up = 0;		
		}		


/*********************************下降*********************************/

		if(Down == 1 && INT1 == 1)
		{			
			Down = 0;
			PositionJudge = 2;
			MotorMov(1,EEprom[4],60000);		 //下降运动
			PositionJudge = 0;

			if(INT1 == 0)                        //应答
			{
				ExeCmdFlag = 1;				     //命令执行成功			
			}
			else
			{
				ExeCmdFlag = 0;				     //命令执行失败
			}
		}
		else if(Down == 1 && INT1 == 0)
		{
			Down = 0;		
		}

/*********************************移动*********************************/
		if(Mov == 1)
		{			
			u16 a = 0;
			u16 b = 0;

			Mov = 0;
			if(Direction == 0 && INT0 == 1)						   //不在最顶端时才允许上升移动
			{
				a = CurrentPosition;				
				PositionJudge = 1;
				MotorMov(0,EEprom[5],MovDis);
				PositionJudge = 0;
				b = CurrentPosition;

				if(b - a > 0 && abs(b - a - MovDis) < 100)	        //应答
				{
					ExeCmdFlag = 1;				         //命令执行成功				
				}
				else
				{
					ExeCmdFlag = 0;				         //命令执行失败
				}
			}
			else if(Direction == 0 && INT0 == 0)
			{
							
			}

			if(Direction == 1 && INT1 == 1)							 //下不在最底端时才允许下降运动
			{
				a = CurrentPosition;				
				PositionJudge = 2;
				MotorMov(1,EEprom[5],MovDis);
				PositionJudge = 0;
				b = CurrentPosition;

				if(a - b > 0 && abs(a - b - MovDis) < 100)			//应答
				{
					ExeCmdFlag = 1;						   //命令执行成功				
				}
				else
				{
					ExeCmdFlag = 0;						   //命令执行失败
				}
			}
			else if(Direction == 1 && INT1 == 0)
			{
					
			}
			
		}
/*********************************复位*********************************/
		if(Reset == 1)
		{			
			Reset = 0;
			if(INT1 == 1)					 //不在最底端才允许复位
			{
				PositionJudge = 2;
				MotorMov(1,10000,60000);
				PositionJudge = 0;		
			}

			if(INT1 == 0)                    //应答
			{
				ExeCmdFlag = 1;			
			}
			else
			{
				ExeCmdFlag = 0;
			}
		}

/******************************写EEprom*********************************/
		if(Write == 1)
		{
			Write = 0;
		//	EEPROM_WriteArray( 0x00, (uchar*)EEprom, 14 );

		}
/******************************读EEprom*********************************/
		if(Read == 1)
		{
		 	Read = 0;			
	//		EEPROM_ReadArray( 0x00, (uchar*)EEprom, 14 );
//			Send_Str(ReadSuccess,7);
		}
		
		
				/******************************写EEprom*********************************/
		if(Write == 2)
		{
			Write = 0;
		//	EEPROM_WriteArray( 0x06, (uchar*)EEpromJR, 3 );
			
		}
/******************************读EEprom*********************************/
		if(Read == 2)
		{
		 	Read = 0;			
			//EEPROM_ReadArray( 0x06, (uchar*)EEpromJR, 3 );
		}
		

		if(StartJR==1)
		{
			                       //孵育模块加热
    	StartJR = 0;         //停止加热放到检测 持续加热的时间到了为止；
			//TemValueSet();
			                       //设置加热温度 DA
					
			ExeCmdFlag = 1;
		}
	
	

}

//*************************************************************************************/
//uchar BIN2BCD(uchar bin)
//{
//    uchar bcd = 0;

//    bcd =(uchar) ((((bin) / 10) << 4) + (bin) % 10);

//    return bcd;
//}
///*************************************************************************************
//函数名：BCD2BIN()
//函数功能：BCD转二进制
//输入参数：bcd BCD码
//输出参数：无
//函数返回值：二进制码
//*************************************************************************************/
//uchar BCD2BIN(uchar bcd)
//{
//	uchar bin = 0;

//    bin = (uchar)((bcd & 0x0f) +(bcd >> 4) * 10);

//    return bin;
//}

//if(CCF0 == 1)		   // CEX0中断处理
//	{ 
//		CCF0 = 0;
//	    PCA0CPL0 = CEX0_COMPARE_VALUE & 0x00FF;   // Set up first edge
//        PCA0CPH0 = (CEX0_COMPARE_VALUE & 0xFF00) >> 8;
//        PCA_value = PCA0CPL0;
//        PCA_value |= PCA0CPH0 << 8;
//        CEX0_COMPARE_VALUE = PCA_value + DIVIDE_RATI0;
//        PCACH0_Num++;

//		if(PositionJudge == 1)
//		{
//			CurrentPosition++;							//计算当前距0点的位置
//		}
//		if(PositionJudge == 2)
//		{
//			CurrentPosition--;
//		}

//		if(DIVIDE_RATI0 > 921600/FrequencyTrans0 && DistanceTrans0 - PCACH0_Num > LADDER_NUM)    	   //加速
//	 	{
//			if(DIVIDE_RATI0 <= StepWide0)
//			{
//				DIVIDE_RATI0 = 921600/FrequencyTrans0;
//			}
//			else
//			{
//				DIVIDE_RATI0 = DIVIDE_RATI0 - StepWide0;
//				if(DIVIDE_RATI0 <= 921600/FrequencyTrans0)
//				{
//					DIVIDE_RATI0 = 921600/FrequencyTrans0;
//				}
//			}				
//		}

//		if(DistanceTrans0 - PCACH0_Num < LADDER_NUM)				   //减速
//		{
//			DIVIDE_RATI0 = DIVIDE_RATI0 + StepWide0;	
//		}
//	 
//    }	


	//01
void MInitDevice(u8 D)
{
	
}//41
//void ClearErr(u8 D);   //42

void InAdsorption()
{
	
}	//42
void DeAdsorption()
{
	
}
//43
void MEmergyStop()
{
	
}//44
/*************************************************************************************
函数名：MotorMov( )
函数功能：控制步进电机旋转
函数参数：direction 电机运动方向，frequency 频率或者速度，distance 距离
函数返回值：无
*************************************************************************************/

//void MotorMov(char8 direction,uint16 frequency,uint16 distance)
//{

//	char SFRPAGE_save = SFRPAGE;
//	SFRPAGE = CONFIG_PAGE;
//	X_DIR = direction;
//	X_EN = 1;

//	FrequencyTrans0 = frequency;
//	DistanceTrans0 = distance;
//	PCACH0_Num = 0;

//	StepWide0 = (SYSCLK/24/100 - SYSCLK/24/frequency)/LADDER_NUM;	   		    

//	PCA_CEX0_Init0();
//	while(PCACH0_Num<distance)
//	{}
//	PCACH0_Num = 0;
//	SFRPAGE = PCA0_PAGE;
//	PCA0CPM0 &= 0x00;
//	SFRPAGE = SFRPAGE_save;
//}




//  ack    ok  81 广播  82 读参数 83 写参数  84 发同步命令 85 异步命令 86本机状态
//  errack     c1  c2  c3 c4  c5 c6
//接收后执行完 应答
//应答后 接收到 再应答
//err 1,报文格式错误 2 数据效验粗无 3，无此数据项 4，写入参数超过有效范围；
void Command_Deal_Magnetic(u8 *s)
{
	u8 ReadData[8];
	
	if((s[0]==0x01)&&(s[1]==0x02))
	{
		switch(s[2])
		{
			case 0x01: MScanDevice(0x01);
				break;
			//case 0x02 :
			default : break;
		}		
		
	}
	if((s[0]==0x02)&&(s[1]==0x02))
	{
		ReadData[0] = 0x82;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
				case 0x02: 	
					ReadData[3] = MagneticX.MSoftVerM;
				  ReadData[4] = MagneticX.MSoftVerS;
				  ReadData[5] = MagneticX.MSoftVer;
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				
				break;
				case 0x03: 
          Int32_to_Hex(ReadData,MagneticX.MSoftTimer);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				
				break;
				case 0x04: 
        	ReadData[3] = MagneticX.MHardwareVerM;
				  ReadData[4] = MagneticX.MHardwareVerS;
				  ReadData[5] = MagneticX.MHardwareVer;
				
				  CAN1_Send_Msg_id(ReadData,0x12,6);
				break;			  
				case 0x05: 				
	        Int32_to_Hex(ReadData,MagneticX.MHardwareTimer);
				
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x11: 
					 ReadData[3] = MagneticX.MAdressID;
				   CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x12: 				
					ReadData[3] = MagneticX.MBoudValue;
				  ReadData[4] = MagneticX.MBoudValue>>8;
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x21: 	
					Int32_to_Hex(ReadData,MagneticX.MPositionDe);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x22: 
					Int32_to_Hex(ReadData,MagneticX.MPositionMem);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x31: 	
					Int32_to_Hex(ReadData,MagneticX.MCoderDe);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x32: 	
					Int32_to_Hex(ReadData,MagneticX.MCoderMem);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 033:	
					Int32_to_Hex(ReadData,MagneticX.MSpeedDe);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x34: 	
					Int32_to_Hex(ReadData,MagneticX.MSpeedMem);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;

				case 0x61:
//					Int32_to_Hex(ReadData,MagneticX.AMotoAccel);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x62: 
//					Int32_to_Hex(ReadData,MagneticX.AMotoInitAccel);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
				case 0x63: 
//					Int32_to_Hex(ReadData,MagneticX.AMotoSpeed);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
		    case 0x64: 
//					Int32_to_Hex(ReadData,MagneticX.AMotoInitSpeed);
				  CAN1_Send_Msg_id(ReadData,0x12,7);
				break;
			default : break;
				//err 
		}		
	}
	if((s[0]==0x03)&&(s[1]==0x02))
	{   
		
		ReadData[0] = 0x83;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
		switch(s[2])
		{
		   	case 0x02: 				
					MagneticX.MSoftVerM=s[3];
				  MagneticX.MSoftVerS=s[4];
				  MagneticX.MSoftVer=s[5];
				  CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x03: 
					 MagneticX.MSoftTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x04: 
					 MagneticX.MHardwareVerM=s[3];
				   MagneticX.MHardwareVerS=s[4];
				   MagneticX.MHardwareVer=s[5];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x05: 
					 MagneticX.MHardwareTimer=Hex_to_Int32(s);
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x11: 
					 MagneticX.MAdressID = s[3];
				   CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x12: 
					 MagneticX.MBoudValue =s[3]<<8;
				   MagneticX.MBoudValue+=s[4];
				   CAN1_Send_Msg_id(ReadData,0x12,3);				   
				break;
				case 0x21: 
					  MagneticX.MPositionDe =Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x22: 
					  MagneticX.MPositionMem =Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x31: 
					  MagneticX.MCoderDe=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x32: 
					  MagneticX.MCoderMem=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 033: 
					  MagneticX.MSpeedDe=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x34: 
						MagneticX.MSpeedMem=Hex_to_Int32(s);
						CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				
				case 0x61: 
//					  MagneticX.MMotoAccel=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x62: 
//					  MagneticX.MMotoInitAccel=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
				case 0x63: 
//					  MagneticX.MMotoSpeed=Hex_to_Int32(s);
			    	CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
		    case 0x64:
//				  	MagneticX.MMotoInitSpeed=Hex_to_Int32(s);
				    CAN1_Send_Msg_id(ReadData,0x12,3);
				break;
			default : break;
		}
		
		// 保存参数到FLASH中去；采用均衡算法；
		
		
	}
	
	//发同步命令 02 
	if((s[0]==0x04)&&(s[1]==0x02))
	{
		
  	ReadData[0] = 0x84;
		ReadData[1] = 0x01;
		ReadData[2] = s[2];
	 	switch(s[2])
		{
		   	
				case 0x41: 
					MInitDevice(0x01);
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x42: 
		
					ReadData[3] = 0x02;
			    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x43: 
					
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
				case 0x51: 

				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x52: 

				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				case 0x53: 
		
//				MotoCurrentStruct.Maccel= 
//				MotoCurrentStruct.Mdecel=
//				MotoCurrentStruct.MotoSpeed=
				
				 
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);
				break;
				
			default : break;
		}
	}
	
	// 01  Recive命令执行完毕  02 命令执行完毕
	if((s[0]==0x05)&&(s[1]==0x02))
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
				    
				    ReadData[3] = 0x02;
				    CAN1_Send_Msg_id(ReadData,0x12,4);

				break;
				case 0x53: 
////				    MagneticX.AInitDis=Hex_to_Float(s);
//				    ReadData[3] = 0x01;
//				    CAN1_Send_Msg_id(ReadData,0x12,4);
//				
//            MotoInitForStep(MagneticX.MInitDis);
//				    ReadData[3] = 0x02;
//				    CAN1_Send_Msg_id(ReadData,0x12,4);
//				
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


