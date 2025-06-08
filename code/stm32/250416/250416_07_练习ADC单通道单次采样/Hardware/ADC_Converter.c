#include "stm32f10x.h"
#include "ADC_Converter.h"


void ADC_Converter_Init(void)
{
	//1.开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//错误点1：ADC挂载在PAB2总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//2.GPIO配置
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//3.开启ADC逐次逼近的时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//4.配置规则组
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);
	//5.配置ADC
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	//6.开启ADC
	ADC_Cmd(ADC1,ENABLE);
	//7.清除ADC
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
}
uint32_t getConverval(void)
{
	//8.驱动ADC进行一次采样
	//错误点2：使用代码推动的函数是ADC_SoftwareStartConvCmd
	//ADC_GetSoftwareStartConvStatus(ADC1);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//9.不用清除标志,应该是等待采样完成
	//ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	//10.返回获取到的ADC转换后的数据
	return ADC_GetConversionValue(ADC1);
}

