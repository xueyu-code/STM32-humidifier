#include "led.h"
	    
// IO初始化
void BEEP_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
 	//蜂鸣器的引脚PA8
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
 BEEP=BEEP_OFF;         //关闭蜂鸣器的输出
}
 
//继电器的配置
void RELAY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //使能GPIOB端口时钟
	//雾化器的引脚PB15
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 		     //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	       //速度为50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);	 
	 
	WATER= WATER_OFF; 
}
