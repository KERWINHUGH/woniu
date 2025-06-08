#include "stm32f10x.h"
#include "DMA_M2M.h"

uint8_t arr0[4];
uint8_t arr1[4];
void DMA_M2MInit(void)
{
	//1.开时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	//2.配置DMA结构体
	DMA_InitTypeDef DMA_InitStruct;
	//错误点1：用数组首元素作为基地址需要强转成32位的数据
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)arr0;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)arr1;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	DMA_InitStruct.DMA_BufferSize = 4;
	DMA_InitStruct.DMA_Priority  = DMA_Priority_High;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	//3.开启DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

