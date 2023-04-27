#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
						  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//读取按键0  选择按键
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//读取按键1  确认按键
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//读取按键2 	+
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//读取按键3 	-
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//读取按键4 返回按键
 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	  2	//KEY1按下
#define KEY2_PRES	  3	//KEY2按下
#define KEY3_PRES   4	//KEY3按下(即KEY_UP)
#define KEY4_PRES 	5	//KEY4按下

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数	
#endif
