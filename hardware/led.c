#include "led.h"
	    
// IO��ʼ��
void BEEP_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
 	//������������PA8
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
 BEEP=BEEP_OFF;         //�رշ����������
}
 
//�̵���������
void RELAY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //ʹ��GPIOB�˿�ʱ��
	//����������PB15
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 		     //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	       //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);	 
	 
	WATER= WATER_OFF; 
}
