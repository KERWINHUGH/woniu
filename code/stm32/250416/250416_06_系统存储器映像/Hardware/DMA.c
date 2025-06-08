#include "stm32f10x.h"                  // Device header
#include "DMA.h"

void DMAInit(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	//指定DMAy通道的外设基址
	DMA_InitStruct.DMA_PeripheralBaseAddr = DMA1_Channel1_BASE;
	//指定DMAy通道的内存基址。
	DMA_InitStruct.DMA_MemoryBaseAddr = DMA1_Channel1_BASE;
	//指定外设是源source----SRC	还是目标destination----DST	该参数设定DMA数据传输方向
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	//指定DMA通道大小，以数据单元作为缓冲区大小，以传输方式决定数据单元是DMA内存数据大小或DMA外设数据大小
	DMA_InitStruct.DMA_BufferSize = DMA_MemoryDataSize_Word;
	//指定外设地址寄存器是否递增。该参数设定DMA外设递增模式是否使用
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	//指定内存地址寄存器是否递增。该参数设定DMA内存递增模式是否使用
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//指定外设数据宽度。该参数设定DMA外设数据大小
		DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//DMA存储器数据大小。该参数设定DMA内存数据大小
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	//指定DMAy通道的工作模式。该参数可以设定为循环模式或者普通模式。
	//@注意：如果内存对内存已经被配置并选择为Channel，这时循环缓冲模式不能使用。
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	//指定DMAy通道的软件优先级。该参数设定DMA的优先级
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	//指定是否在内存到内存的传输中使用DMAy通道。该参数设定内存到内存方式是否使用
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;

	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
}
