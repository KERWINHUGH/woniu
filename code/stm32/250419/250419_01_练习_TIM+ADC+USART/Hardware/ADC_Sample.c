#include "stm32f10x.h"                  // Device header
#include "ADC_Sample.h"

uint16_t sample[2] = {0};

void DMA_Config(void)
{
	//1.开时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	
	//2.DMA结构体
	DMA_InitTypeDef DMA_InitStruct;
	
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&ADC1->DR;		//需要取DR寄存器的地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	
	DMA_InitStruct.DMA_PeripheralBaseAddr =  (uint32_t)sample;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_BufferSize = 2;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;	//外设是目标，从DR寄存器向数组中移动数据
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//3.开启DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

void ADC_SampleInit(void)
{
	//1.开启ADC和GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.ADC12ci逐次逼近的时钟,使用6预分配，72MHz/6 = 12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.规则组
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_NbrOfChannel = 2;		//对应规则组通道
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//6.配置DMA
	DMA_Config();
	
	//7.开启DMA
	ADC_DMACmd(ADC1,ENABLE);
	
	//8.开启ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//9.校验
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	//10.推动一次ADC采样
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

