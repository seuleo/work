#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"   
#include "stmflash.h" 
#include "iap.h"   

//ALIENTEK 探索者STM32F407开发板 实验50
//串口IAP实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


int main(void)
{ 
	u8 t;
	u8 key;
	u16 oldcount=0;	//老的串口接收数据值
	u16 applenth=0;	//接收到的app代码长度
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200

	while(1)
	{
	 	if(USART_RX_CNT)
		{
			if(oldcount==USART_RX_CNT)//新周期内,没有收到任何数据,认为本次数据接收完成.
			{
				applenth=USART_RX_CNT;
				oldcount=0;
				USART_RX_CNT=0;
				printf("用户程序接收完成!\r\n");
				printf("代码长度:%dBytes\r\n",applenth);
				
				
		 if(applenth)
		{
				printf("开始更新固件...\r\n");	
 				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
				{	 
					iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码   			
					printf("固件更新完成!\r\n");	
					
			   if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
			   {	 
				  iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
			   }
				}else 
				{ 
					printf("非FLASH应用程序!\r\n");
				}
 			}else 
			{
				printf("没有可以更新的固件!\r\n");
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
//				if(clearflag==0)LCD_Fill(30,210,240,210+16,WHITE);//清除显示
//			}
//		}	  	 
//		key=KEY_Scan(0);
		
//		if(key==WKUP_PRES)	//WK_UP按键按下
//		{
//			if(applenth)
//			{
//				printf("开始更新固件...\r\n");	
// 				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
//				{	 
//					iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码   			
//					printf("固件更新完成!\r\n");	
//					
//			   if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
//			   {	 
//				  iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
//			   }
//				}else 
//				{ 
//					printf("非FLASH应用程序!\r\n");
//				}
// 			}else 
//			{
//				printf("没有可以更新的固件!\r\n");
//			}
//					 
//		}

		   
		 
	}  
}

