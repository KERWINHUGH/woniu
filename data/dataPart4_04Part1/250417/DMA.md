## DMA简介 

* 直接存储器存取(DMA)用来提供在外设和存储器之间或者存储器和存储器之间的高速数据传 输。无须CPU干预，数据可以通过DMA快速地移动，这就节省了CPU的资源来做其他操作。 两个DMA控制器有12个通道(DMA1有7个通道，DMA2有5个通道)，每个通道专门用来管理来自 于一个或多个外设对存储器访问的请求。还有一个仲裁器来协调各个DMA请求的优先权。
* STM32F103C8T6只有DMA1，DMA2仅存在于大容量产品和互联型产品。
* 闪存、SRAM、外设设均可作为访问的源和目标
* 一般不允许直接往闪存写入
* DMA挂在AHB总线上
* DMA1有7个通道，
* SRAM内部的互相传输，可以使用任意的通道，如果外设和SRAM之间传输，参考手册手册10.3.7
* Byte 字节8位   HalfWord 16位  Word32位

![image-20250417100436835](C:%5CUsers%5CAdministrator%5CAppData%5CRoaming%5CTypora%5Ctypora-user-images%5Cimage-20250417100436835.png)



### 1.数组到数组的DMA拷贝代码

````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

//单片机中，建议全局变量全部赋初值
//使用DMA，将arr1的值，自动移动到arr2中
//SRAM内部的互相传输，可以使用任意的通道，如果外设和SRAM之间传输，参考手册10.3.7
uint8_t arr1[4] = {0x01,0x02,0x03,0x04};
uint8_t arr2[4] = {0x00};

void DMA_Config(void)
{
	//1.启动DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//2.配置DMA结构体
	DMA_InitTypeDef DMA_InitStruct;
	
	//arr1
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)arr1;//地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//数据宽度
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; //是否自增
	
	//arr2
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)arr2;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	//公共配置
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Normal,只传输BufferSize次    DMA_Mode_Circular-每次传输完成后，又把BufferSize=4
	DMA_InitStruct.DMA_BufferSize = 4;//一共要传输的数据个数
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;//memory to memroy     2 to   4 for
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//3.启动DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

int main()
{
	OLED_Init();//初始化屏幕
	
	DMA_Config();

	while(1)
	{
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
		
		Delay_ms(1000);
	}
	
}

````

### 2.ADC+DMA的代码

![image-20250417141121346](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504171411560.png)

ADConvert.c

````c
#include "stm32f10x.h"                  // Device header

uint16_t array[3] = {0x00};

void DMA_Config(void)
{
	//1.时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//2.结构体
	DMA_InitTypeDef DMA_InitStruct;
	
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//因为寄存器是16位，所以选半字
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//DR寄存器是出厂就定好的，不能自增
	
	DMA_InitStruct.DMA_MemoryBaseAddr =(uint32_t)array;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//数组要自增
	
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_BufferSize = 3;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);//使用哪个通道，参考10.3.7 DMA请求映像
	//3.启动
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
}

void AD_ConvertInit(void)
{
	//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//3.ADCCLK
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.规则组通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,31,ADC_SampleTime_13Cycles5);
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//ADC1的独立转换模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//使用软件推动一次
	ADC_InitStruct.ADC_NbrOfChannel = 3;//PA0  PA1  PA2
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//转换完一次后，继续转换
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;//有多个通道要转换
	ADC_Init(ADC1,&ADC_InitStruct);
	
	DMA_Config();//启动DMA
	//这一行代码很容忘记，使能ADCDMA
	ADC_DMACmd(ADC1,ENABLE);//让ADC拥有DMA的功能
	
	//6.启动
	ADC_Cmd(ADC1,ENABLE);
	//7.校验
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	//8.软件推动第一次转换开始
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
````



ADConvert.h

````c
#ifndef __AD_CONVERT_H
#define __AD_CONVERT_H
extern uint16_t array[3] ;
void AD_ConvertInit(void);

#endif


````



main.c

```c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "ADConvert.h"
int main()
{
	OLED_Init();//初始化屏幕
	AD_ConvertInit();
	
	while(1)
	{
		OLED_ShowNum(1,1,array[0],4);
		OLED_ShowNum(2,1,array[1],4);
		OLED_ShowNum(3,1,array[2],4);
	}
	
}

```

