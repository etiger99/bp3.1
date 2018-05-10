#include "ds18b20.h"
//#include "SysTickDelay.h"	
#include "delay.h"
#include "stdio.h"

//Mini STM32������
//DS18B20 �������� 
//����ԭ��@ALIENTEK
//2010/6/17	 

//��λDS18B20
void DS18B20_Rst(void)	   
	{                 
	DS18B20_IO_OUT(); //SET PA0 OUTPUT
	Clr_DS18B20_DQ_OUT; //����DQ
	delay_us(750);    //����750us
	Set_DS18B20_DQ_OUT; //DQ=1 
	delay_us(15);     //15US
	}

//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
u8 DS18B20_Check(void) 	   
	{   
	u8 retry=0;
	DS18B20_IO_IN();//SET PA0 INPUT	 
	while (DS18B20_DQ_IN&&retry<200)
		{
		retry++;
		delay_us(1);
		};	 
	if(retry>=200)return 1;
	else retry=0;
	while (!DS18B20_DQ_IN&&retry<240)
		{
		retry++;
		delay_us(1);
		};
	if(retry>=240)return 1;	    
	return 0;
	}
	
//��DS18B20��ȡһ��λ
//����ֵ��1/0
u8 DS18B20_Read_Bit(void) 			 // read one bit
	{
	u8 data;
	DS18B20_IO_OUT();//SET PA0 OUTPUT
	Clr_DS18B20_DQ_OUT; 
	delay_us(2);
	Set_DS18B20_DQ_OUT; 
	DS18B20_IO_IN();//SET PA0 INPUT
	delay_us(12);
	if(DS18B20_DQ_IN)data=1;
	else data=0;	 
	delay_us(50);           
	return data;
	}
	
	
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
u8 DS18B20_Read_Byte(void)    // read one byte
	{        
	u8 i,j,dat;
	dat=0;
	for (i=1;i<=8;i++) 
		{
		j=DS18B20_Read_Bit();
		dat=(j<<7)|(dat>>1);
		}						    
	return dat;
	}
	
	
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(u8 dat)     
	{             
	u8 j;
	u8 testb;
	DS18B20_IO_OUT();//SET PA0 OUTPUT;
	for (j=1;j<=8;j++) 
		{
		testb=dat&0x01;
		dat=dat>>1;
		if (testb) 
			{
			Clr_DS18B20_DQ_OUT;// Write 1
			delay_us(2);                            
			Set_DS18B20_DQ_OUT;
			delay_us(60);             
			}
		else 
			{
			Clr_DS18B20_DQ_OUT;// Write 0
			delay_us(60);             
			Set_DS18B20_DQ_OUT;
			delay_us(2);                          
			}
		}
	}
	
	
//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{   						               
	DS18B20_Rst();	   
	DS18B20_Check();	 
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0x44);// convert
} 
	
//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����    	 
u8 DS18B20_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
	//RCC->APB2ENR|=1<<2;    //ʹ��PORTA��ʱ�� 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	 //ʹ��PORTA��ʱ��  
	//GPIOA->CRL&=0XFFFFFFF0;//PORTA.0 �������
	//GPIOA->CRL|=0X00000003;
	//GPIOA->ODR|=1<<0;      //���1
	/* Configure PA0 */
	GPIO_InitStructure.GPIO_Pin = DS18B20_DQ_OUT_PIN;  //SPI CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DS18B20_DQ_OUT_PORT, &GPIO_InitStructure);
	/* Deselect the PA0 Select high */
	GPIO_SetBits(DS18B20_DQ_OUT_PORT,DS18B20_DQ_OUT_PIN);
	DS18B20_Rst();
	return DS18B20_Check();
}  
	
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
short DS18B20_Get_Temp(void)
	{
	u8 temp;
	u8 TL,TH;
	short tem;
	DS18B20_Start ();                    // ds1820 start convert
	DS18B20_Rst();
	DS18B20_Check();	 
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0xbe);// convert	    
	TL=DS18B20_Read_Byte(); // LSB   
	TH=DS18B20_Read_Byte(); // MSB  
	
	if(TH>7)
		{
		TH=~TH;
		TL=~TL; 
		temp=0;//�¶�Ϊ��  
		}
	else temp=1;//�¶�Ϊ��	  	  
	tem=TH; //��ø߰�λ
	tem<<=8;    
	tem+=TL;//��õװ�λ
	tem=(float)tem*0.625;//ת��     
	if(temp)return tem; //�����¶�ֵ
	else return -tem;    
	} 
 
short fetcht()
{
	int t;
	short temp=0,tempH=0,tempL=0;
	
				
				for(t=0;t<10;t++){
					temp+=DS18B20_Get_Temp();
					delay_ms(200);	

				}
				temp=temp/10;

				if(temp<0){
					temp=-temp;			
					//printf("\n -     \n");	
						
				}
				tempH=temp/10; //�������� 
				tempL=temp%10; //С������

				
				if(tempH>70){
					temp=0;
					delay_ms(1000);
					for(t=0;t<10;t++){
						temp+=DS18B20_Get_Temp();
						delay_ms(200);
					}
					temp=temp/10;
	
					if(temp<0){
						temp=-temp;			
						printf("\n -     \n");	
					}
					tempH=temp/10; //�������� 
					tempL=temp%10; //С������ 
				}

				temp=0;
				for(t=0;t<10;t++){
					temp+=DS18B20_Get_Temp();
					delay_ms(200);	

				}
				temp=temp/10;

				if(temp<0){
					temp=-temp;			
					//printf("\n -     \n");	
				}
				tempH=temp/10; //�������� 
				tempL=temp%10; //С������

//				data_upload[0]=0xF0;
//				data_upload[1]=0xF1;
//				data_upload[2]=0x00;
//				data_upload[3]=0x00;
//				data_upload[4]=0x00;
//				data_upload[5]=0x00;
//				data_upload[6]=0x00;
//				data_upload[7]=tempH;
//				data_upload[8]=tempL;
//				data_upload[9]=0xFF;
				
//				for(t=0;t<10;t++){
//					
//					//USART_SendData(USART1, data_upload[t]);										   
//					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
//				}
				tempH=tempH+2;
				tempL=tempL+5;
				//printf("Tempreture is : %d.", tempH); 
				//printf("%d \n", tempL);
				//delay_ms(200);
				temp=temp*10+120;
        return temp;
				//clear_USART1_RX_BUF();
}
