#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//CAN���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0 
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
	  	
#define REC_LEN 8   //���ջ���,���64���ֽ�

#define Max_Frame_Count 20 //һ���Խ��ղ����10��ָ֡��

extern u8 Frame_Store[Max_Frame_Count][REC_LEN]; //֡�������飬���ɴ��10��ָ֡��
extern u8   SeqNum_Frame_REC;  //֡����������Ŀǰ֡�洢λ��
extern u8   SeqNum_Frame_Deal; //֡����������Ŀǰִ֡��λ��
	
//CAN1����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.								    
										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
u8 CAN1_Send_Msg(u8* msg,u8 len);						//��������
//u8 CAN1_Send_Msg_id(u8* msg,u8 len,u16 id);
u8 CAN1_Send_Msg_id(u8* msg,u16 id,u8 len);
u8 CAN1_Receive_Msg(u8 *buf);							//��������
void Command_Deal(u8 *s);
void Command_DealTest(u8 *s);
#endif

















