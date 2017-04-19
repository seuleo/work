#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2011/6/14
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
//#define USART_REC_LEN  			300  	//�����������ֽ��� 200
#define USART_REC_LEN  			600  	//�����������ֽ��� 200



#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����



#define RS232_REC_LEN 16    //���ջ���,���64���ֽ�
#define Max_Frame_Count 48 //һ���Խ��ղ����10��ָ֡��

//extern u8 Frame_Store[Max_Frame_Count][RS232_REC_LEN]; //֡�������飬���ɴ��10��ָ֡��
extern u8   SeqNum_Frame_REC;  //֡����������Ŀǰ֡�洢λ��
extern u8   SeqNum_Frame_Deal; //֡����������Ŀǰִ֡��λ��

extern u8 RS232_RX_BUF[RS232_REC_LEN]; 		
extern u16 RS232_RX_CNT;    			//���յ������ݳ���
extern u16 Flag_Deal;  //���ڴ���ı�־
extern u16  Circle_Frame_Deal; //ָ�������ִ��ָ���ѭ����




extern u8 Sending;
extern u8 dat_ok;
//extern u8 revbuf[600];
extern u16 EEprom[50];

extern u8 sss;    //����/ֹͣ
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



void SendOneByte(unsigned char c);//����һ�ֽ�
void Send_Str(unsigned char* str);//�����ַ���
void SendOneByte_uart4(unsigned char c);//����һ�ֽ�
void Send_Str_uart4(unsigned char* str);//�����ַ���

int my_atoi(const char * str);
unsigned char  DataCheck(unsigned char* id,unsigned char* value);


void Package(unsigned char* id,unsigned char* value,unsigned char* tempbuf);
u16 crc16(unsigned char *addr, int num, u16 crc);  

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
  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
void USART1_Send_Data(u8 *buf,u8 len);


//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


