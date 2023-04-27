#include "stm32f10x.h"   // Device header
#include "delay.h"
#include "OLED.h"
#include "led.h"
#include "key.h"
#include "dht11.h"
#include "sys.h"
#include "usart.h"
#include "rtc.h" 
#include "AD.h"

//olde标志位
u8 oled_flag=0;
int Mode_Change=2;//模式转换
//初始阈值
u16 Start_Temp = 35;//温度阈值
u16 Start_Hum = 45;//湿度阈值

u8 temperature;  	    
u8 humidity; 
u16 ADValue;//ADC数据
float Voltage,High;

void DHTII_Get(void );//温湿度数据采集函数
void Time_display(void);//实时时间显示+定时函数
void key_Set(void);//按键设置(参数)

int main(void)
{
	delay_init();	//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	  //串口初始化为115200
	
	BEEP_Init();            //蜂鸣器初始化
	RELAY_Init();           //继电器初始化
	KEY_Init();							//按键初始化
	while(RTC_Init())				//RTC初始化
	{
		delay_ms(800);
	}
	while(DHT11_Init())     //DHT11模块初始化
	{
	 	delay_ms(600);
	};	
	BEEP=0;
	delay_ms(300);
	BEEP=1;//全部都初始化完成，蜂鸣器响一下
	OLED_Init ();//OLED初始化
	AD_Init ();
	OLED_Clear();						//OLED清屏
	my_oled_display1();
	
			while(1)
			{
				DHTII_Get();
				Time_display();

				//水位监测
				ADValue = AD_GetValue (ADC_Channel_0);//adc测量值
				Voltage = (float )ADValue /4095 * 3.3;//转换电压
				High =(1000*Voltage)/33;//水位深度
				if(High <20)
				{
					BEEP = 0;//响
				}
				else
				{
					BEEP=1;//不响
				}
				
				key_Set();
					if(Mode_Change ==0)
						{
							if(humidity <Start_Hum)
							{
								WATER = WATER_ON ;
							}
							if(humidity >=Start_Hum)
							{
								WATER=WATER_OFF;
							}
						}
			}
}

void Time_display(void)//实时时间显示+定时函数
{
	u16 obj=0;
	if((obj!=calendar.sec)&&(oled_flag==0))
		 {
			obj=calendar.sec;
			OLED_ShowNum(4,1,calendar.hour,2);									  
			OLED_ShowNum(4,4,calendar.min,2);									  
			OLED_ShowNum(4,7,calendar.sec,2);
			 
			if((Mode_Change ==1)&&(calendar.hour==calendar .AlarmHour &&calendar.min==calendar .AlarmMinute &&calendar.sec==calendar .AlarmSecond ))
			{
//				BEEP =0;
				WATER = WATER_ON ;
			}
		 }
		 delay_ms(10);
}

void DHTII_Get(void)//温湿度数据采集函数
{
	
	u8 t=0;
	
	if(t%10==0)			//每100ms读取一次
		{									  
			DHT11_Read_Data(&humidity,&temperature);	//读取温湿度值		
			OLED_ShowNum (2,6,humidity,2);//显示湿度
			OLED_ShowNum (3,6,temperature,2);//显示温度
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
		}
}

void key_Set(void)//按键设置(参数)
{
	unsigned char i=0;//模式标志位：自动 手动 定时
	unsigned  char t=0;
	u8 flag;//标志位
	
	u16 Set_Hum = Start_Hum ;//设置的湿度阈值
	u32 hour1=calendar.hour,min1=calendar.min,sec1=calendar.sec;//时分秒
	if((KEY0==0)&&(oled_flag==0))
	{
		while(KEY0==0);
		OLED_Clear();
		my_oled_display_mode();
		while(KEY4==1)
	{
				
				if(KEY0==0)
				{
					while(KEY0==0);
					i++;
					if(i>3)
						i=1;
				}
		
		if(i==1)
		{
				OLED_ShowString(1,1," ");
				OLED_ShowString(2,1,">");
				OLED_ShowString(3,1," ");
				OLED_ShowString(4,1," ");
		}
		if(i==2)
		{
				OLED_ShowString(1,1," ");
				OLED_ShowString(2,1," ");
				OLED_ShowString(3,1,">");
				OLED_ShowString(4,1," ");
		}
		if(i==3)
		{
				OLED_ShowString(1,1," ");
				OLED_ShowString(2,1," ");
				OLED_ShowString(3,1," ");
				OLED_ShowString(4,1,">");
		}
		if(i==1)//自动
		{
			flag=0;
			if((KEY1==0)&&(flag==0))
			{
				while(KEY1==0);
				OLED_Clear ();
				my_oled_disply_yuzhi();
				OLED_ShowNum(2,12,Start_Hum,2);
				while(KEY4==1)
				{
					if(KEY2==0)
					{
						while(KEY2==0);
						Set_Hum++;
					}
					if(KEY3==0)
					{
						while(KEY3==0);
						Set_Hum--;
					}
					Start_Hum = Set_Hum ;
					OLED_ShowNum(2,12,Start_Hum,2);
				
					if(KEY4==0)
					{
						while(KEY4==0);
						OLED_Clear ();
						my_oled_display_mode();
						Mode_Change=0;
						break;
					}	
				}
			}
		}
		if(i==2)//手动
		{
			if(KEY2==0)
			{
				while(KEY2==0);
				WATER=WATER_ON ;
				OLED_ShowChinese(3,13,20);
			}
			if(KEY3==0)
			{
				while(KEY3==0);
				WATER=WATER_OFF;
				OLED_ShowChinese(3,13,21);
			}			
		}
		if(i==3)//定时
		{
			flag=1;
			if((KEY1==0)&&(flag==1))
			{
				while(KEY1==0);
				OLED_Clear ();
				my_oled_Alarm();//显示定时界面
				while(KEY4==1)
				{
					if(KEY1==0)         
					{
						while(KEY1==0);		
						t++;
						if(t>2)
						t= 0;
					}
					if(t==0)//时				
					{
						OLED_ShowString(3,2,"--");
						delay_ms(100);
						OLED_ShowString(3,2,"  ");
						if(KEY2==0)
						{
							while(KEY2==0);				
							hour1++;
							if(hour1>23)
								hour1 = 0;
						}
						if(KEY3==0)
						{
							while(KEY3==0);
							if(hour1>0)
								hour1--;
						}
						calendar .AlarmHour = hour1;
						OLED_ShowNum(2,2,calendar .AlarmHour,2);			
					}
					if(t==1)//分
					{
						OLED_ShowString(3,5,"--");
						delay_ms(100);
						OLED_ShowString(3,5,"  ");
						if(KEY2==0)
						{
							while(KEY2==0);
							min1 ++;
							if(min1>59)
								min1=0;
						}
						if(KEY3==0)
						{
							while(KEY3==0);
							if(min1>0)
							min1 --;
						}
						calendar .AlarmMinute = min1;
						OLED_ShowNum(2,5,calendar.AlarmMinute,2);
					}
					if(t==2)//秒
					{
						OLED_ShowString(3,8,"--");
						delay_ms(100);
						OLED_ShowString(3,8,"  ");
						if(KEY2==0)
						{
							while(KEY2==0);
							sec1  ++;
							if(sec1 >59)
								sec1 =0;
						}
						if(KEY3==0)
						{
							while(KEY3==0);
							if(sec1 >0)
							sec1 --;
						}
						calendar .AlarmSecond = sec1;
						OLED_ShowNum(2,8,calendar .AlarmSecond,2);
					}
					if(KEY4==0)
					{
						while(KEY4==0);
						OLED_Clear ();
						my_oled_display_mode();
						Mode_Change=1;
						break;
					}	
				}
			}
		}
		if(KEY4==0)
		{
			while(KEY4==0);
			OLED_Clear ();
			my_oled_display1();
			break;
		}
	}
 }
}


