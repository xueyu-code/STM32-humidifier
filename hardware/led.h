#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//�������˿ڶ���
#define BEEP PAout(8)    // �������ӿ� PA8
#define BEEP_ON  0       //S8550������ IO�ڵ͵�ƽ��ͨ 
#define BEEP_OFF 1       //S8550������ IO�ڸߵ�ƽ����ͨ

//�̵����˿ڶ���
#define WATER PBout(15) //��ʪ���ӿ� PB15
#define WATER_ON  1    //S8050������ IO�ڸߵ�ƽ��ͨ   
#define WATER_OFF 0    //S8050������ IO�ڵ͵�ƽ����ͨ


void RELAY_Init(void);	//�̵�����ʼ��(��װ��)
void BEEP_Init(void);    //������IO�ڳ�ʼ��
void Drum_Level_Sensor_Init(void);//ˮλ�������ʼ��
#endif
