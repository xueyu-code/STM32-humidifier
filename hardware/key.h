#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
						  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//��ȡ����0  ѡ�񰴼�
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//��ȡ����1  ȷ�ϰ���
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//��ȡ����2 	+
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//��ȡ����3 	-
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//��ȡ����4 ���ذ���
 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define KEY2_PRES	  3	//KEY2����
#define KEY3_PRES   4	//KEY3����(��KEY_UP)
#define KEY4_PRES 	5	//KEY4����

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��	
#endif
