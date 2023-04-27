#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//蜂鸣器端口定义
#define BEEP PAout(8)    // 蜂鸣器接口 PA8
#define BEEP_ON  0       //S8550三极管 IO口低电平导通 
#define BEEP_OFF 1       //S8550三极管 IO口高电平不导通

//继电器端口定义
#define WATER PBout(15) //加湿器接口 PB15
#define WATER_ON  1    //S8050三极管 IO口高电平导通   
#define WATER_OFF 0    //S8050三极管 IO口低电平不导通


void RELAY_Init(void);	//继电器初始化(雾化装置)
void BEEP_Init(void);    //蜂鸣器IO口初始化
void Drum_Level_Sensor_Init(void);//水位监测器初始化
#endif
