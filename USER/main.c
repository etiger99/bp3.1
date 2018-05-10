#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	
#include "timer.h"
#include "sram.h"
#include "malloc.h"
#include "beep.h"
#include "tsensor.h"
#include "rtc.h"
#include "string.h"
#include "usmart.h"	
//#include "dm9000.h"
#include "enc28j60.h"
#include "lwip/netif.h"
#include "lwip_comm.h"
#include "lwipopts.h"
#include "httpd.h"
#include "ds18b20.h"
#include "stdio.h"
#include "hem7200.h"
#include "gpio.h"
#include "usart3.h"
#include "common.h"

/************************************************
 ALIENTEKս��STM32������LWIPʵ��
 ����RAW API��WebServer Serverʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


u8 buffer[10];

u8 cmd_verify[]={0xF0,0x20,0x21,0x01,0xE0};	   //Ѫѹ��״̬��ѯ����
u8 cmd_start[]={0xF0,0x20,0x21,0x02,0x31,0x00}; //Ѫѹ����������

u8 cmd_mode;

short temp,tempH,tempL;

long cnt=0;
u8 s=0;

vu8 USART1_RX_BUF[10];     //���ջ���1������������λ����ָ��֡��4���ֽ�
vu8 USART2_RX_BUF[20];	   //���ջ���2����������bpģ�������֡��12���ֽ�
vu8 data_upload[15]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00};	   //�ϴ�����λ��������֡��10���ֽڣ�Ԥ��15����

//vu8 USART_RX_STA;          //����״̬���   

vu8 RxCounter1=0x00;
vu8 RxCounter2=0x00;
vu8 USART1_flag=0x00;
vu8 USART2_flag=0x00;
vu16 bp_start=0x00;
vu8 bp_received=0x00;
vu8 bp_report=0x00;
vu8 cmd_received=0x00;

vu8 bp_fetch_permitted=0x00; 

vu32 clk_counter=0;
vu8 SDA[40]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
vu8 SDAA[2];
	
//�ж����õ��ı���
//uint64_t SDAAA;	
vu16 SDAAA;
vu8 SDAAM;
vu8 n=0;
vu8 m=0;
vu8 g=0;
vu8 d=0;
vu8 mb=0;
	
vu8 detect_wait=0;	
	
	
vu32 delay=671;	  //17+10+28+28+28+28+28+28+280+28+28*6=13*28+280+27=
	
short Temperate = 0;

//***************������ԭvoid atk_8266_test(void)����**********	
	u8 key;
	u8 timex;
//***************************************************************
/* Private function prototypes -----------------------------------------------*/

void NVIC_Configuration(void);
void RCC_Configuration(void);
void Init_All_Periph(void);

void Delay(vu32 nCount);

u8 BP_Init(void);
void bed_up(void);
void bed_down(void);
void bed_stop(void);

void clear_USART1_RX_BUF(void);
void disable_INT8(void);
void fetch_bp(void);



//����UI
//mode:
//bit0:0,������;1,����ǰ�벿��UI
//bit1:0,������;1,���غ�벿��UI
void lwip_test_ui(u8 mode)
{
	//u8 speed;
	u8 buf[30]; 
	POINT_COLOR=RED;
	if(mode&1<<0)
	{
		LCD_Fill(30,30,lcddev.width,110,WHITE);	//�����ʾ
		LCD_ShowString(30,30,200,16,16,"WARSHIP STM32F103");
		LCD_ShowString(30,50,200,16,16,"LWIP Webserver Test");
		LCD_ShowString(30,70,200,16,16,"ATOM@ALIENTEK");
		LCD_ShowString(30,90,200,16,16,"2015/3/21"); 	
	}
	if(mode&1<<1)
	{
		LCD_Fill(30,110,lcddev.width,lcddev.height,WHITE);	//�����ʾ
		LCD_ShowString(30,110,200,16,16,"lwIP Init Successed");
		if(lwipdev.dhcpstatus==2)sprintf((char*)buf,"DHCP IP:%d.%d.%d.%d",lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);//��ӡ��̬IP��ַ
		else sprintf((char*)buf,"Static IP:%d.%d.%d.%d",lwipdev.ip[0],lwipdev.ip[1],lwipdev.ip[2],lwipdev.ip[3]);//��ӡ��̬IP��ַ
		LCD_ShowString(30,130,210,16,16,buf); 
		//speed=DM9000_Get_SpeedAndDuplex();//�õ�����
		//if(speed&1<<1)LCD_ShowString(30,150,200,16,16,"Ethernet Speed:10M");
		//else LCD_ShowString(30,150,200,16,16,"Ethernet Speed:100M");
	}
}

void RCC_Configuration(void)
{
	SystemInit(); 	
	//ʹ�ܴ���ģ��1ʱ��,ʹ�ܴ�������GPIOģ��ʱ��,ʹ��AFIOģ��ʱ��	
	RCC_APB2PeriphClockCmd(
	RCC_APB2Periph_USART1 | 
	RCC_APB2Periph_GPIOA | 
	RCC_APB2Periph_GPIOB | 
	RCC_APB2Periph_GPIOC |
	RCC_APB2Periph_GPIOD | 
	RCC_APB2Periph_GPIOE | 
	RCC_APB2Periph_GPIOF |
	RCC_APB2Periph_GPIOG | 
	RCC_APB2Periph_AFIO, 
	ENABLE);	  //
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	
}

void NVIC_Configuration(void)
{ 
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//�������ȼ����飺��ռ���ȼ�0λ,�����ȼ�4λ
	                                                //                ��ռ���ȼ�   ����Ӧ���ȼ�
	
	//�����������λ�ú�ƫ��
	#ifdef  VECT_TAB_RAM  
		/* Set the Vector Table base location at 0x20000000 */ 
		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 		//������λ��RAM
	#else  /* VECT_TAB_FLASH  */
		/* Set the Vector Table base location at 0x08000000 */ 
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   //������λ��FLASH
	#endif


	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		//USART1�ж�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1


	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		//USART2�ж�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART2 
}

int main(void)
{	 

	
	RCC_Configuration();
	delay_init();	    	//��ʱ������ʼ��	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	//NVIC_Configuration();
	
	GPIO_Configuration();
	
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			    //LED�˿ڳ�ʼ��
	LCD_Init();				//��ʼ��LCD		
	KEY_Init();
	RTC_Init();				//RTC��ʼ��

	TIM3_Int_Init(1000,719);//��ʱ��3Ƶ��Ϊ100hz
 	//usmart_dev.init(72);	//��ʼ��USMART	
	//W25QXX_Init();				//��ʼ��W25Q128
  usart3_init(115200);		//��ʼ������3 
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	
	
	POINT_COLOR = RED; 		
	
	printf("\n  DS18B20 TEST     \n");
	
	lwip_test_ui(1);		//����ǰ�벿��UI		    
	
	while(lwip_comm_init()) //lwip��ʼ��
	{
		LCD_ShowString(30,110,200,20,16,"LWIP Init Falied!");
		delay_ms(1200);
		LCD_Fill(30,110,230,130,WHITE); //�����ʾ
		LCD_ShowString(30,110,200,16,16,"Retrying...");  
	}
	LCD_ShowString(30,110,200,20,16,"LWIP Init Success!");
 	LCD_ShowString(30,130,200,16,16,"DHCP IP configing...");
#if LWIP_DHCP   //ʹ��DHCP
	while((lwipdev.dhcpstatus!=2)&&(lwipdev.dhcpstatus!=0XFF))//�ȴ�DHCP��ȡ�ɹ�/��ʱ���
	{
		
		lwip_periodic_handle();	//LWIP�ں���Ҫ��ʱ����ĺ���
		//lwip_pkt_handle();
	}
#endif
	lwip_test_ui(2);		//���غ�벿��UI 
	delay_ms(500);			//��ʱ1s
	delay_ms(500);
	httpd_init();  			//Web Serverģʽ
	

//					delay_ms(6000);	
//					GPIO_WriteBit(GPIOF,GPIO_Pin_0,(BitAction)1);
//					delay_ms(6000);	
//					GPIO_WriteBit(GPIOF,GPIO_Pin_0,(BitAction)0);
//				
//			
//					delay_ms(6000);
//					GPIO_WriteBit(GPIOF,GPIO_Pin_1,(BitAction)1);
//					delay_ms(6000);
//					GPIO_WriteBit(GPIOF,GPIO_Pin_1,(BitAction)0);
//		
//					delay_ms(6000);	
//					GPIO_WriteBit(GPIOF,GPIO_Pin_2,(BitAction)1);
//					delay_ms(6000);	
//					GPIO_WriteBit(GPIOF,GPIO_Pin_2,(BitAction)0);
//			
//					delay_ms(6000);
//					GPIO_WriteBit(GPIOF,GPIO_Pin_3,(BitAction)1);
//					delay_ms(6000);
//					GPIO_WriteBit(GPIOF,GPIO_Pin_3,(BitAction)0);
//				

	
	printf("\n  DS18B20 TEST     \n");
		
	while(DS18B20_Init())//��ʼ��DS18B20,����18B20
	{  
		printf("\n  DS18B20 Check Failed!  \n");
			delay_ms(500);		  
			printf("\n  Please Check!     \n");
			delay_ms(500);
	}
		printf("\n DS18B20 Ready!        \n");
	
	

	
//  	while(1)
//	{	
//		lwip_periodic_handle();
//		//lwip_pkt_handle();  

//	}
//	
	
	//POINT_COLOR=RED;
	//Show_Str_Mid(0,30,"ATK-ESP8266 WIFIģ�����",16,240); 
	while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
	{
		atk_8266_quit_trans();//�˳�͸��
		atk_8266_send_cmd("AT+CIPMODE=0","OK",200);  //�ر�͸��ģʽ	
		//Show_Str(40,55,200,16,"δ��⵽ģ��!!!",16,0);
		delay_ms(800);
		LCD_Fill(40,55,200,55+16,WHITE);
		//Show_Str(40,55,200,16,"��������ģ��...",16,0); 
	} 
		while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���
		atk_8266_mtest_ui(32,30);
	
	
	
	while(1)
	{
		lwip_periodic_handle();
		delay_ms(10); 
		atk_8266_at_response(1);//���ATK-ESP8266ģ�鷢�͹���������,��ʱ�ϴ�������
		key=KEY_Scan(0); 
		if(key)
		{
			LCD_Clear(WHITE);
			POINT_COLOR=RED;
			switch(key)
			{
				case 1://KEY0
					//Show_Str_Mid(0,30,"ATK-ESP WIFI-AP+STA ����",16,240);
					//Show_Str_Mid(0,50,"��������ATK-ESP8266ģ�飬���Ե�...",12,240);
					atk_8266_apsta_test();	//������̫������
					break;
				case 2://KEY1
					//Show_Str_Mid(0,30,"ATK-ESP WIFI-STA ����",16,240);
					//Show_Str_Mid(0,50,"��������ATK-ESP8266ģ�飬���Ե�...",12,240);
					atk_8266_wifista_test();//WIFI STA����
					break;
				case 4://WK_UP
					atk_8266_wifiap_test();	//WIFI AP����
					break;
			}
			atk_8266_mtest_ui(32,30);
			timex=0;
		} 	 
		if((timex%20)==0)LED0=!LED0;//200ms��˸ 
		timex++;	 
	} 
		
	
}
