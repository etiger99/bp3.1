#include "delay.h"
#include "stdio.h"

extern vu8 detect_wait;
extern vu8 bp_fetch_permitted;
extern vu32 clk_counter;
extern vu8 SDAA[2];
//extern uint64_t SDAAA;
extern vu16 SDAAA;
extern vu8 SDAAM;

extern vu8 n;
extern vu8 m;
extern vu8 g;
extern vu8 d;
extern vu8 mb;

extern vu8 cmd_received;


void disable_INT8(void){
 	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	EXTI_ClearITPendingBit(EXTI_Line8);		 //*
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);  	//ѡ�񰴼����ڵ�GPIO�ܽ������ⲿ�ж���·

	EXTI_InitStructure.EXTI_Line = EXTI_Line8;	//���ð������е��ⲿ��·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //�ⲿ�жϴ�����ѡ��:EXTI_Trigger_Falling  EXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;		//ʹ���ⲿ�ж���״̬
	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;	 //*   //��ռ���ȼ�4λ,��16��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				 //*   //��ռ���ȼ�0λ,�����ȼ�4λ
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ⲿ�ж�ͨ������Ϊ��ֹ
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure); 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

void disable_INT0(void){
 	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	EXTI_ClearITPendingBit(EXTI_Line0);		 //*
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);  	//ѡ�񰴼����ڵ�GPIO�ܽ������ⲿ�ж���·

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//���ð������е��ⲿ��·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //�ⲿ�жϴ�����ѡ��:EXTI_Trigger_Falling  EXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;		//ʹ���ⲿ�ж���״̬
	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;	 //*   //��ռ���ȼ�4λ,��16��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				 //*   //��ռ���ȼ�0λ,�����ȼ�4λ
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ⲿ�ж�ͨ������Ϊ��ֹ
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure); 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

void EXTI8_Init()  //���ð�������
{
	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	EXTI_ClearITPendingBit(EXTI_Line8);		 //*
	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //�ⲿ�жϴ�����ѡ��:EXTI_Trigger_Falling  EXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		//ʹ���ⲿ�ж���״̬
	EXTI_Init(&EXTI_InitStructure);		
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�2λ��//4λ,��16��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				 //*   //��ռ���ȼ�2λ    //0λ,�����ȼ�4λ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ⲿ�ж�ͨ������Ϊ��ֹ
	//NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure); 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

void EXTI0_Init()  //���ð�������
{
		GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//ʹ�ܰ�������GPIOʱ��,ͬʱʹ��AFIOʱ��(��Ҫ�����ⲿ�жϼĴ���)  ����ƶ���main.c  RCC_Configuration()����
	//RCC_APB2PeriphClockCmd(BUTTON_CLK[Button] | RCC_APB2Periph_AFIO, ENABLE);			
	
	
	EXTI_ClearITPendingBit(EXTI_Line0);		 //*
	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//���ð������е��ⲿ��·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //�ⲿ�жϴ�����ѡ��:EXTI_Trigger_Falling  EXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		//ʹ���ⲿ�ж���״̬
	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
		//�жϣ����ԣ�����PC.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;    //PC.0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);  	//ѡ�񰴼����ڵ�GPIO�ܽ������ⲿ�ж���·
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	 //*   //��ռ���ȼ�4λ,��16��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				 //*   //��ռ���ȼ�0λ,�����ȼ�4λ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ⲿ�ж�ͨ������Ϊ��ֹ
	//NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure); 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}


void fetch_bp(void)
{

	
//	GPIO_WriteBit(GPIOC,GPIO_Pin_0,(BitAction)1);	//��������
//	delay_ms(5500);
//	GPIO_WriteBit(GPIOC,GPIO_Pin_0,(BitAction)0);
//	delay_ms(5500);
//	
//										   //�ȴ�
//	for(detect_wait=0;detect_wait<50;detect_wait++){
//		delay_ms(1000);
//	}
//	
//	GPIO_WriteBit(GPIOC,GPIO_Pin_0,(BitAction)1);	//�رղ���
//	delay_ms(5000);
//	GPIO_WriteBit(GPIOC,GPIO_Pin_0,(BitAction)0);
	
//	delay_ms(1000);
//	delay_ms(1000);	 				
//	
	delay_ms(1000);
	delay_ms(1000);

	
	GPIO_WriteBit(GPIOE,GPIO_Pin_4,(BitAction)1);	  //����
	delay_ms(200);
	
	GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)1);
	n=0;
	m=0;
	EXTI0_Init();
	bp_fetch_permitted=1; 			
	//GPIO_WriteBit(GPIOC,GPIO_Pin_7,0); //�����жϵ���
	
	delay_ms(1000);
	delay_ms(1000);
	GPIO_WriteBit(GPIOE,GPIO_Pin_4,(BitAction)0);

   	GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)1);
	disable_INT0();	
	GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)0);

	delay_ms(5000);
	GPIO_WriteBit(GPIOE,(BitAction)GPIO_Pin_2,(BitAction)1);	//�رն���
	delay_ms(1000);
	GPIO_WriteBit(GPIOE,(BitAction)GPIO_Pin_2,(BitAction)0);
	
	
	//printf("SDAAA = %llu  \n",SDAAA);
	//printf("------clk_counter = %u !!!!!!! \n",clk_counter);
	d = SDAAA & 0x00ff;
	g = (SDAAA & 0xff00) >> 8;
	g = g+25;
	mb = SDAAM;
	
	printf("SDAAA = %u  \n", SDAAA);
	printf(" gaoya = %d,  diya = %d ", g, d);
	printf(" %d  ", SDAAM);
	

}

void fetch_bp2(void)
{

	SDAAA=0;	      
	clk_counter=0;

	GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)0); 
	delay_us(2);
	GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)1); 

	EXTI0_Init();

	GPIO_WriteBit(GPIOE,GPIO_Pin_4,(BitAction)1);	  //����
	//delay_ms(200);




	//GPIO_WriteBit(GPIOC,GPIO_Pin_7,0); //�����жϵ���

	delay_ms(1000);
	delay_ms(1000);
	GPIO_WriteBit(GPIOE,GPIO_Pin_4,(BitAction)0);

	GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)1);//ʱ�ӱ�ǩ

	disable_INT0();
	GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)0);


	delay_ms(1000);
	//GPIO_WriteBit(GPIOE,(BitAction)GPIO_Pin_2,(BitAction)1);	//�رն���
	delay_ms(5000);
	//GPIO_WriteBit(GPIOE,(BitAction)GPIO_Pin_2,(BitAction)0);


	//printf("H bp = %d !!!!!!! \n",H);
	printf("SDAAA = %u  \n",SDAAA);
	//printf("------SDAA[1] = %d  \n",SDAA[1]);
	printf("------clk_counter = %u !!!!!!! \n",clk_counter);


	if(cmd_received){
	printf("oooooooooooo");
	cmd_received=0;
	}
		
}
