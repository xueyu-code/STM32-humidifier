#include "stm32f10x.h"                  // Device header


void AD_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1 ,ENABLE );
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA ,ENABLE );//配置rcc
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//配置ADCCLK的分频
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
	
	//初始化ADC
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//单通道或双通道，这里是单通道
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//对齐模式 ：右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发源选择：不使用
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE ;//转换模式：单次
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;//非扫描模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;//通道数目
	ADC_Init(ADC1 ,&ADC_InitStructure);
	
	ADC_Cmd (ADC1 ,ENABLE );//开启ADC
	
	ADC_ResetCalibration(ADC1 );//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET );//等待复位校准完成 读取这一位
	ADC_StartCalibration(ADC1 );//开始校准
	while(ADC_GetCalibrationStatus(ADC1 ) == SET );//等待校准完成
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1 ,ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd (ADC1 ,ENABLE );//启动
	while(ADC_GetFlagStatus (ADC1 ,ADC_FLAG_EOC ) == RESET  );//等待
	return ADC_GetConversionValue(ADC1);//读取
	
}
