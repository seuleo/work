#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"   
#include "stmflash.h" 
#include "iap.h"   

//ALIENTEK ̽����STM32F407������ ʵ��50
//����IAPʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


int main(void)
{ 
	u8 t;
	u8 key;
	u16 oldcount=0;	//�ϵĴ��ڽ�������ֵ
	u16 applenth=0;	//���յ���app���볤��
	u8 clearflag=0; 
//<<<<<<< .mine
//	//LLL;
//||||||| .r37
//	
//=======
//>>>>>>> .r38
//	//WWW;
//<<<<<<< .mine
//	//WWW;
//||||||| .r36
//=======
////LLL
//>>>>>>> .r37
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200

	while(1)
	{
	 	if(USART_RX_CNT)
		{
			if(oldcount==USART_RX_CNT)//��������,û���յ��κ�����,��Ϊ�������ݽ������.
			{
				applenth=USART_RX_CNT;
				oldcount=0;
				USART_RX_CNT=0;
				printf("�û�����������!\r\n");
				printf("���볤��:%dBytes\r\n",applenth);
				
				
		 if(applenth)
		{
				printf("��ʼ���¹̼�...\r\n");	
 				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
				{	 
					iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//����FLASH����   			
					printf("�̼��������!\r\n");	
					
			   if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
			   {	 
				  iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
			   }
				}else 
				{ 
					printf("��FLASHӦ�ó���!\r\n");
				}
 			}else 
			{
				printf("û�п��Ը��µĹ̼�!\r\n");
			}
				
				
			}else oldcount=USART_RX_CNT;			
		}
//		t++;
		delay_ms(10);
//		if(t==30)
//		{
//			LED0=!LED0;
//			t=0;
//			if(clearflag)
//			{
//				clearflag--;
//				if(clearflag==0)LCD_Fill(30,210,240,210+16,WHITE);//�����ʾ
//			}
//		}	  	 
//		key=KEY_Scan(0);
		
//		if(key==WKUP_PRES)	//WK_UP��������
//		{
//			if(applenth)
//			{
//				printf("��ʼ���¹̼�...\r\n");	
// 				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
//				{	 
//					iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//����FLASH����   			
//					printf("�̼��������!\r\n");	
//					
//			   if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
//			   {	 
//				  iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
//			   }
//				}else 
//				{ 
//					printf("��FLASHӦ�ó���!\r\n");
//				}
// 			}else 
//			{
//				printf("û�п��Ը��µĹ̼�!\r\n");
//			}
//					 
//		}

		   
		 
	}  
}

