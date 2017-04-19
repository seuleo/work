#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.csom
//修改日期:2011/6/14
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
////////////////////////////////////////////////////////////////////////////////// 	
//#define USART_REC_LEN  			300  	//定义最大接收字节数 200
#define USART_REC_LEN  			300  	//定义最大接收字节数 200



#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收



#define RS232_REC_LEN 16    //接收缓冲,最大64个字节
#define Max_Frame_Count 48 //一次性接收并存放10条帧指令

//extern u8 Frame_Store[Max_Frame_Count][RS232_REC_LEN]; //帧缓存数组，最多可存放10条帧指令
extern u8   SeqNum_Frame_REC;  //帧缓存数组中目前帧存储位置
extern u8   SeqNum_Frame_Deal; //帧缓存数组中目前帧执行位置

extern u8 RS232_RX_BUF[RS232_REC_LEN]; 		
extern u16 RS232_RX_CNT;    			//接收到的数据长度
extern u16 Flag_Deal;  //正在处理的标志
extern u16  Circle_Frame_Deal; //指令缓冲区，执行指令的循环数




extern u8 Sending;
extern u8 dat_ok;
//extern u8 revbuf[600];
extern u16 EEprom[50];

extern u8 sss;    //启动/停止
extern u8 ppp;
extern u8 BufId[5];
extern u8 BufValue[5];
extern u16 NumValue;

extern u16 lll;
extern u16 uuu;
extern u16 tzw;
extern u16 s0p;
//extern u16 usk;
//extern u16 usr;
//extern u16 uss;
//extern u16 us0;
//extern u16 us9;
extern u16 s1p;
extern u16 s2p;
extern short s3p;
extern u16 s4p;
extern u16 s5p;



extern u8 t0k;
extern u8 t1k;
extern u8 t2k;
extern u8 t3k;
extern u8 t4k;
extern u8 t5k;
extern u8 t6k;
extern u8 t7k;


extern u8 w0r;
extern u8 w1r;
extern u8 w2r;
extern u8 w3r;
extern u8 w4r;
extern u8 w5r;
extern u8 w6r;
extern u8 w7r;

extern u8 vibbottom0;
extern u8 vibbottom1;
extern u8 vibbottom2;
extern u8 vibbottom3;
extern u8 vibbottom4;
extern u8 vibbottom5;
extern u8 vibbottom6;
extern u8 vibbottom7;
extern u8 vibbottom8;


extern u16 usy;
extern u16 xdelt;
extern u16 y1firstmov;
extern u16 y2firstmov;
extern u16 WriteP;
extern u16 ReadP ;

extern unsigned char  WorkStatusBuf1[15];
extern unsigned char  WorkStatusBuf2[15];
extern unsigned char  WorkStatusBuf3[15];
extern unsigned char  WorkStatusBuf4[15];
extern unsigned char  WorkStatusBuf5[15];
extern unsigned char  WorkStatusBuf6[15];
extern unsigned char  WorkStatusBuf7[15];
extern unsigned char  WorkStatusBuf8[15];
extern unsigned char  WorkStatusBuf9[15];
extern unsigned char  WorkStatusBuf10[15];
extern unsigned char  WorkStatusBuf11[18];
extern unsigned char  WorkStatusBuf12[15];



void SendOneByte(unsigned char c);//发送一字节
void Send_Str(unsigned char* str);//发送字符串
void SendOneByte_uart4(unsigned char c);//发送一字节
void Send_Str_uart4(unsigned char* str);//发送字符串

int my_atoi(const char * str);
unsigned char  DataCheck(unsigned char* id,unsigned char* value);


void Package(unsigned char* id,unsigned char* value,unsigned char* tempbuf);



void FrameCopyDeal(void);

void SendBack_L(void);
void SendBack_H(void);
void SendBack_J(void);
void SendBack_1(void);
void SendBack_2(void);
void SendBack_3(void);
void SendBack_T(void);
void SendBack_S(void);
void SendBack(void);
  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
void USART1_Send_Data(u8 *buf,u8 len);


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
#endif


