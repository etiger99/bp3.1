#include "gpio.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//�������ͨ������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	

	//�����LED0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0   PB.5 
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //�����   LED�͵�ƽ��Ч
	//�����LED1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1  PE.5 
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  			
	GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //����� 	
	//�������ΪѪѹģ�����������̵������ƶ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    //PE.2		 
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 
	//GPIO_SetBits(GPIOE,GPIO_Pin_2); 		
	//�������ΪѪѹģ�������������̵������ƶˡ�	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		//PE.4 
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				
	// GPIO_SetBits(GPIOE,GPIO_Pin_4); 
	//�������Ϊʱ��λ�ü���źš�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;        //PC.7
	GPIO_Init(GPIOC, &GPIO_InitStructure); 	
	GPIO_SetBits(GPIOC,GPIO_Pin_7);
	
	
	
	//���룬SDA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;     // PC.9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	//�ƶ���EXTI0_Init()��
//	//�жϣ����ԣ������PC.8
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;    //PC.0
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);  	//ѡ�񰴼����ڵ�GPIO�ܽ������ⲿ�ж���·
	
	//�жϣ�SCL
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			// PC.8           //����  ʹ��ǰ��ѡ��ֹJTAGʹ�ô�����	 �͵�ƽ��Ч,�����������������ã���֮�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//  GPIO_Mode_IN_FLOATING��������     GPIO_Mode_IPU  ��������   GPIO_Mode_IPD ��������	
	GPIO_Init(GPIOC, &GPIO_InitStructure);			
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);  	//ѡ�񰴼����ڵ�GPIO�ܽ������ⲿ�ж���·
	
	
	
	//��ʼ����Ϊ�̵������ơ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);

//	//��ʼ��PB9��Ϊ�̵�������
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);


//	//��ʼ��PC0��ΪѪѹģ�����������̵������ƶˡ�
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);



}
