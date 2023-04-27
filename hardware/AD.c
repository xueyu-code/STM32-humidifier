#include "stm32f10x.h"                  // Device header


void AD_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1 ,ENABLE );
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA ,ENABLE );//����rcc
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//����ADCCLK�ķ�Ƶ
	
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
	
	//��ʼ��ADC
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//��ͨ����˫ͨ���������ǵ�ͨ��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//����ģʽ ���Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ⲿ����Դѡ�񣺲�ʹ��
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE ;//ת��ģʽ������
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;//��ɨ��ģʽ
	ADC_InitStructure.ADC_NbrOfChannel = 1;//ͨ����Ŀ
	ADC_Init(ADC1 ,&ADC_InitStructure);
	
	ADC_Cmd (ADC1 ,ENABLE );//����ADC
	
	ADC_ResetCalibration(ADC1 );//��λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1) == SET );//�ȴ���λУ׼��� ��ȡ��һλ
	ADC_StartCalibration(ADC1 );//��ʼУ׼
	while(ADC_GetCalibrationStatus(ADC1 ) == SET );//�ȴ�У׼���
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1 ,ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd (ADC1 ,ENABLE );//����
	while(ADC_GetFlagStatus (ADC1 ,ADC_FLAG_EOC ) == RESET  );//�ȴ�
	return ADC_GetConversionValue(ADC1);//��ȡ
	
}
