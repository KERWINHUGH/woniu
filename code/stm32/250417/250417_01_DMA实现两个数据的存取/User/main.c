#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"

//单片机中奖全局变量全部赋初值
//使用DMA,将arr1的值，自动移动到arr2中
//SRAM内部互相传输使用DMA，可以使用任意通道；SRAM和外设之间传输，使用通道需要参考芯片参考手册10.3.7
uint8_t arr1[4] = {0x01,0x02,0x03,0x04};
uint8_t arr2[4] = {0x00};

void DMA_Config(void)
{
	//1.启动DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//2.配置DMA结构体
	DMA_InitTypeDef DMA_InitStruct;

	//指定DMAy通道的内存基址。
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)arr1;
		//DMA存储器数据大小。该参数设定DMA内存数据大小
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		//指定内存地址寄存器是否递增。该参数设定DMA内存递增模式是否使用
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	//指定DMAy通道的外设基址
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)arr2;
		//指定外设数据宽度。该参数设定DMA外设数据大小
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		//指定外设地址寄存器是否递增。该参数设定DMA外设递增模式是否使用
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	//指定DMAy通道的工作模式。该参数可以设定为循环模式或者普通模式。
	//@注意：如果内存对内存已经被配置并选择为Channel，这时循环缓冲模式不能使用。
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;//数据全部拷贝完一次后结束DMA_BufferSize = 0
	//DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//数据全部拷贝完后继续拷贝，DMA_BufferSize返回等于4
		//指定DMA通道大小，以数据单元作为缓冲区大小，以传输方式决定数据单元是DMA内存数据大小或DMA外设数据大小
	DMA_InitStruct.DMA_BufferSize = 4;
			//指定外设是源source----SRC	还是目标destination----DST	该参数设定DMA数据传输方向
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
		//指定是否在内存到内存的传输中使用DMAy通道。该参数设定内存到内存方式是否使用
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	//指定DMAy通道的软件优先级。该参数设定DMA的优先级
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;

	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//3.开启DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

int main()
{
	OLED_Init();
	DMA_Config();
		
	while(1)
	{
		//使用普通模式下，再循环中每次设置DMA_BufferSize的值都需要先关闭DMA，再开启DMA
		//因为开启DMA后DMA_BufferSize值被设为只读
		DMA_Cmd(DMA1_Channel1,DISABLE);
		DMA_SetCurrDataCounter(DMA1_Channel1,4);
		DMA_Cmd(DMA1_Channel1,ENABLE);
		
		arr1[0]++;
		arr1[1]++;
		arr1[2]++;
		arr1[3]++;
		
		OLED_ShowHexNum(1,1,arr1[0],2);
		OLED_ShowHexNum(2,1,arr1[1],2);
		OLED_ShowHexNum(3,1,arr1[2],2);
		OLED_ShowHexNum(4,1,arr1[3],2);
		
		OLED_ShowHexNum(1,5,arr2[0],2);
		OLED_ShowHexNum(2,5,arr2[1],2);
		OLED_ShowHexNum(3,5,arr2[2],2);
		OLED_ShowHexNum(4,5,arr2[3],2);
		Delay_s(1);
	}
}
