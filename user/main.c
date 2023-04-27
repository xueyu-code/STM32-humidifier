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

//olde��־λ
u8 oled_flag=0;
int Mode_Change=2;//ģʽת��
//��ʼ��ֵ
u16 Start_Temp = 35;//�¶���ֵ
u16 Start_Hum = 45;//ʪ����ֵ

u8 temperature;  	    
u8 humidity; 
u16 ADValue;//ADC����
float Voltage,High;

void DHTII_Get(void );//��ʪ�����ݲɼ�����
void Time_display(void);//ʵʱʱ����ʾ+��ʱ����
void key_Set(void);//��������(����)

int main(void)
{
	delay_init();	//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	  //���ڳ�ʼ��Ϊ115200
	
	BEEP_Init();            //��������ʼ��
	RELAY_Init();           //�̵�����ʼ��
	KEY_Init();							//������ʼ��
	while(RTC_Init())				//RTC��ʼ��
	{
		delay_ms(800);
	}
	while(DHT11_Init())     //DHT11ģ���ʼ��
	{
	 	delay_ms(600);
	};	
	BEEP=0;
	delay_ms(300);
	BEEP=1;//ȫ������ʼ����ɣ���������һ��
	OLED_Init ();//OLED��ʼ��
	AD_Init ();
	OLED_Clear();						//OLED����
	my_oled_display1();
	
			while(1)
			{
				DHTII_Get();
				Time_display();

				//ˮλ���
				ADValue = AD_GetValue (ADC_Channel_0);//adc����ֵ
				Voltage = (float )ADValue /4095 * 3.3;//ת����ѹ
				High =(1000*Voltage)/33;//ˮλ���
				if(High <20)
				{
					BEEP = 0;//��
				}
				else
				{
					BEEP=1;//����
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

void Time_display(void)//ʵʱʱ����ʾ+��ʱ����
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

void DHTII_Get(void)//��ʪ�����ݲɼ�����
{
	
	u8 t=0;
	
	if(t%10==0)			//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&humidity,&temperature);	//��ȡ��ʪ��ֵ		
			OLED_ShowNum (2,6,humidity,2);//��ʾʪ��
			OLED_ShowNum (3,6,temperature,2);//��ʾ�¶�
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
		}
}

void key_Set(void)//��������(����)
{
	unsigned char i=0;//ģʽ��־λ���Զ� �ֶ� ��ʱ
	unsigned  char t=0;
	u8 flag;//��־λ
	
	u16 Set_Hum = Start_Hum ;//���õ�ʪ����ֵ
	u32 hour1=calendar.hour,min1=calendar.min,sec1=calendar.sec;//ʱ����
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
		if(i==1)//�Զ�
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
		if(i==2)//�ֶ�
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
		if(i==3)//��ʱ
		{
			flag=1;
			if((KEY1==0)&&(flag==1))
			{
				while(KEY1==0);
				OLED_Clear ();
				my_oled_Alarm();//��ʾ��ʱ����
				while(KEY4==1)
				{
					if(KEY1==0)         
					{
						while(KEY1==0);		
						t++;
						if(t>2)
						t= 0;
					}
					if(t==0)//ʱ				
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
					if(t==1)//��
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
					if(t==2)//��
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


