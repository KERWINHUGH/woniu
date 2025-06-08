#include "stm32f10x.h"                  // Device header
#include "ADC_Converter.h"

uint16_t array[3] = {0x00};

void DMA_Config(void)
{
	//1.开时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//2.配置DM结构体
	DMA_InitTypeDef DMA_InitStruct;
	
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//ADC的DR寄存器不能自增，是写死的
	
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)array;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//数组中的数据地址要自增
	
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_BufferSize = 3;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);//外设使用哪个通道，需要参考芯片参考手册的10.3.7
	//3.开启DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
}


void AD_ConverterInit(void)
{
	//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.开启ADC12次时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.配置规则组
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_41Cycles5);
	
	//5.配置ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel =3;//PA0,PA1,PA2
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//5.5使能ADC-DMA
	DMA_Config();
	//5.5使能ADC-DMA
	ADC_DMACmd(ADC1,ENABLE);
	
	//6.开启ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//7.校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	//8.推动ADC进行一次转换
	//ADC_GetSoftwareStartConvStatus(ADC1);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

