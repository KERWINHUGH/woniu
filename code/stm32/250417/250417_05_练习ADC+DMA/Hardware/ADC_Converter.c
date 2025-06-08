#include "stm32f10x.h"                  // Device header
#include "ADC_Converter.h"

//错误点6：DMA用于存放通道采集数据的数组应该是16位的，和源目标大小保持一致
uint16_t arr[3] = {0};

//错误点1：DMA配置应该放到专门的一个函数中
void DMA_Config(void)
{
		//6.DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	//7.DMA结构体
	DMA_InitTypeDef DMA_InitStruct;
	//错误点5：每个基地址都需要强转为32位数值，地址就是32位，DR寄存器是12位
	//错误点7：ADC1->DR寄存器的地址需要取地址符取出来再进行强制转换
	DMA_InitStruct.DMA_MemoryBaseAddr =(uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc =DMA_MemoryInc_Disable;
	
	DMA_InitStruct.DMA_PeripheralBaseAddr =(uint32_t)arr;
	DMA_InitStruct.DMA_PeripheralDataSize =DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc =DMA_PeripheralInc_Enable;
	
	DMA_InitStruct.DMA_Mode =DMA_Mode_Circular;
	DMA_InitStruct.DMA_DIR =DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M =DMA_M2M_Disable;
	DMA_InitStruct.DMA_BufferSize =3;
	DMA_InitStruct.DMA_Priority =DMA_Priority_High;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//8.DMA启动
	DMA_Cmd(DMA1_Channel1,ENABLE);
}
void ADC_ConvertInit(void)
{
	//1.时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.12次逐次逼近时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.规则组
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_13Cycles5);
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitSrtuct;
	ADC_InitSrtuct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitSrtuct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitSrtuct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	//错误点3：使用多个ADC通道时，这个结构体成员应该设为对应通道个数
	//ADC_InitSrtuct.ADC_NbrOfChannel = 1;
	ADC_InitSrtuct.ADC_NbrOfChannel = 3;
	ADC_InitSrtuct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitSrtuct.ADC_ScanConvMode = ENABLE;
	
	ADC_Init(ADC1,&ADC_InitSrtuct);
	
	
	//错误点4：初始化ADC结构体之后，应该启动DMA
	DMA_Config();
	ADC_DMACmd(ADC1,ENABLE);
//	//6.DMA时钟
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
//	
//	//7.DMA结构体
//	DMA_InitTypeDef DMA_InitStruct;
//	DMA_InitStruct.DMA_MemoryBaseAddr =ADC1->DR;
//	DMA_InitStruct.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord;
//	DMA_InitStruct.DMA_MemoryInc =DMA_MemoryInc_Disable;
//	
//	DMA_InitStruct.DMA_PeripheralBaseAddr =(uint32_t)arr;
//	DMA_InitStruct.DMA_PeripheralDataSize =DMA_PeripheralDataSize_HalfWord;
//	DMA_InitStruct.DMA_PeripheralInc =DMA_PeripheralInc_Enable;
//	
//	DMA_InitStruct.DMA_Mode =DMA_Mode_Circular;
//	DMA_InitStruct.DMA_DIR =DMA_DIR_PeripheralDST;
//	DMA_InitStruct.DMA_M2M =DMA_M2M_Disable;
//	DMA_InitStruct.DMA_BufferSize =3;
//	DMA_InitStruct.DMA_Priority =DMA_Priority_High;
//	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
//	
//	//8.DMA启动
//	DMA_Cmd(DMA1_Channel1,ENABLE);

	//错误点2：ADC初始化结束后，应该开启ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//9.校验
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	//10.推动
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

