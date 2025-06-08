## ADC 

* analog digital convert 模拟到数字信号的转换
* 12位ADC是一种逐次逼近型模拟数字转换器

* ADC1和ADC2
* 只有10个外部通道，和2个内部通道

### 1.12次逐次逼近和运算

12次逐次逼近最终的值是从0-4095，对应的电压0-3.3V



### 2.CONVERT 时间

ADCCLK频率=14MHz    1.5周期+12.5=14周期

* 总ADC转换时间=采样时间+12.5个周期的逐次逼近时间
* 电容采样：采样时间可选的，1.5周期---239.5周期
* 12次计算时间+0.5周期处理时间
* ADC的输入时钟不得超过14MHz，它是由PCLK2经分频产生



![image-20250416100114184](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504161001462.png)

![image-20250416104108438](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504161041731.png)

### 3.对齐方式

因为存储转换数据的寄存器是16位，转换的值只有12位，我们选择右对齐

### 校准

ADC有一个内置自校准模式。校准可大幅减小因内部电容器组的变化而造成的准精度误差

建议在每次上电后执行一次校准

启动校准前，ADC必须处于关电状态(ADON=’0’)超过至少两个ADC时钟周期。

### 模拟看门狗





## 代码1：单通道规则组转换

````c
#include "stm32f10x.h"                  // Device header
/**
   测试外部可变电阻的电压值，所以使用ADC12逐次逼近 0-4095
   引脚连在PA0--ADC1_IN0
*/
void AD_ConvertInit(void)
{
	//1.开启ADC1和GPIO的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.选择推动ADC逐次逼近时钟 APB2总线是72M，官方要求ADC最大频率不超过14，所以我们选择6分频 72M/6=12M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.配置规则组通道,把要转换的规则通道0，放在要转换的序列1的位置
	//ADC_SampleTime_41Cycles5 采样
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//只使用ADC1进行转换 
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //自己写代码触发转换  Externa外部 trigger触发  Convert 转换
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//规则组通道中，如果只接了一个通道，不要扫描，接了多个就要扫描
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//连续转换模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//number of channel
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//6.启动ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//7.校准--固定代码，不用记
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//等待校准完成为止
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);	
}

uint16_t getConvertValue(void)
{
	    //1.使用代码推动一次转换
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		
		//2.等待转换完成 end of convert
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	
		//3.获取转换之后的值
		return ADC_GetConversionValue(ADC1);
}











````



````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADConvert.h"
//0-3.3
//0-4095 
float v = 0;
int main()
{
	OLED_Init();//初始化屏幕
	AD_ConvertInit();
	
	while(1)
	{	
		uint16_t value = getConvertValue();//2000
		//获取电压整数
		v = (float)value*3.3/4096;//1.19
		OLED_ShowNum(2,1,v,1);
		OLED_ShowString(2,2,".");
		OLED_ShowNum(2,3,(uint32_t)(v*100)%100,2);
		OLED_ShowNum(1,1,value,4);//0-4095
	}
	
}

````



## 代码2：单通道连续转换

````c
#include "stm32f10x.h"                  // Device header
/**
   测试外部可变电阻的电压值，所以使用ADC12逐次逼近 0-4095
   引脚连在PA0--ADC1_IN0
*/
void AD_ConvertInit(void)
{
	//1.开启ADC1和GPIO的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.选择推动ADC逐次逼近时钟 APB2总线是72M，官方要求ADC最大频率不超过14，所以我们选择6分频 72M/6=12M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.配置规则组通道,把要转换的规则通道0，放在要转换的序列1的位置
	//ADC_SampleTime_41Cycles5 采样
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//只使用ADC1进行转换 
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //自己写代码触发转换  Externa外部 trigger触发  Convert 转换
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//规则组通道中，如果只接了一个通道，不要扫描，接了多个就要扫描
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//连续转换模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//number of channel
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//6.启动ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//7.校准--固定代码，不用记
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//等待校准完成为止
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);	
	
	//启动转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}












````

## 代码3：使用定时器推动转换

````c
#include "stm32f10x.h"                  // Device header

//定时器触发规则组的ADC转换，只能用定时器3,1秒触发一次
void TIM3_Init(void)
{
	//1.时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//2.来源
	TIM_InternalClockConfig(TIM3);
	
	//3.时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period = 10000 - 1 ;
	TIM_TimeBaseStruct.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);
	//4.设置成主模式+输出触发
	TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);//更新事件
	
	//5.启动
	TIM_Cmd(TIM3,ENABLE);
}
````



````c
#include "stm32f10x.h"                  // Device header
/**
   测试外部可变电阻的电压值，所以使用ADC12逐次逼近 0-4095
   引脚连在PA0--ADC1_IN0
*/
void AD_ConvertInit(void)
{
	//1.开启ADC1和GPIO的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.选择推动ADC逐次逼近时钟 APB2总线是72M，官方要求ADC最大频率不超过14，所以我们选择6分频 72M/6=12M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.配置规则组通道,把要转换的规则通道0，放在要转换的序列1的位置
	//ADC_SampleTime_41Cycles5 采样
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//只使用ADC1进行转换 
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;//使用定时器3来做更新事件，触发转换
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//规则组通道中，如果只接了一个通道，不要扫描，接了多个就要扫描
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//连续转换模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//number of channel
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//6.启动ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//7.校准--固定代码，不用记
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//等待校准完成为止
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);	
	
	//启动转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}












````

## 代码4：单通道看门狗中断

AWD：analog watch dog

![image-20250416152746092](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504161527319.png)



````c
#include "stm32f10x.h"                  // Device header
/**
   测试外部可变电阻的电压值，所以使用ADC12逐次逼近 0-4095
   引脚连在PA0--ADC1_IN0
*/
void AD_ConvertInit(void)
{
	//1.开启ADC1和GPIO的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.选择推动ADC逐次逼近时钟 APB2总线是72M，官方要求ADC最大频率不超过14，所以我们选择6分频 72M/6=12M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.配置规则组通道,把要转换的规则通道0，放在要转换的序列1的位置
	//ADC_SampleTime_41Cycles5 采样
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//只使用ADC1进行转换 
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;//使用定时器3来做更新事件，触发转换
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//规则组通道中，如果只接了一个通道，不要扫描，接了多个就要扫描
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//连续转换模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//number of channel
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//********************* 添加一个看门狗中断的功能********************
	//配置看门狗
	ADC_AnalogWatchdogThresholdsConfig(ADC1, 4000, 1000);
	ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_0);
	ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_SingleRegEnable);
	
	
	//ADC看门狗中断
	ADC_ITConfig(ADC1,ADC_IT_AWD,ENABLE);
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//0-3   0-3
	NVIC_InitTypeDef NVIC_InitStruct; 
	NVIC_InitStruct.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	//********************* 看门狗中断的功能结束********************
	
	//6.启动ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//7.校准--固定代码，不用记
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//等待校准完成为止
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);	
	
	//启动转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}












````



````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADConvert.h"
#include "Timer.h"
//0-3.3
//0-4095 
float v = 0;
int main()
{
	OLED_Init();//初始化屏幕
	TIM3_Init();
	AD_ConvertInit();
	
	while(1)
	{	
		uint16_t value = ADC_GetConversionValue(ADC1);//2000
		//获取电压整数
		v = (float)value*3.3/4096;//1.19
		OLED_ShowNum(2,1,v,1);
		OLED_ShowString(2,2,".");
		OLED_ShowNum(2,3,(uint32_t)(v*100)%100,2);
		OLED_ShowNum(1,1,value,4);//0-4095
	}
	
}

//汇编
void ADC1_2_IRQHandler()
{
	//判断中断来源
	if(ADC_GetITStatus(ADC1,ADC_IT_AWD) == SET)
	{
		OLED_ShowString(4,1,"WARRING");
		//清除中断标志位
		ADC_ClearITPendingBit(ADC1,ADC_IT_AWD);		
	}
	
	
}

````

## 代码5：多通道

````c
#include "stm32f10x.h"                  // Device header
/**
   测试外部可变电阻的电压值，所以使用ADC12逐次逼近 0-4095
   引脚连在PA0--ADC1_IN0
*/
void AD_ConvertInit(void)
{
	//1.开启ADC1和GPIO的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.选择推动ADC逐次逼近时钟 APB2总线是72M，官方要求ADC最大频率不超过14，所以我们选择6分频 72M/6=12M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//4.配置规则组通道,把要转换的规则通道0，放在要转换的序列1的位置
	//ADC_SampleTime_41Cycles5 采样
	
	//5.ADC结构体
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//只使用ADC1进行转换 
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //自己写代码触发转换  Externa外部 trigger触发  Convert 转换
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//规则组通道中，如果只接了一个通道，不要扫描，接了多个就要扫描
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//连续转换模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//number of channel
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//6.启动ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//7.校准--固定代码，不用记
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//等待校准完成为止
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);	
}

uint16_t getConvertValue(uint8_t ADC_Channel)
{
	   ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_41Cycles5);
	    //1.使用代码推动一次转换
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		
		//2.等待转换完成 end of convert
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	
		//3.获取转换之后的值
		return ADC_GetConversionValue(ADC1);
}

````



````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADConvert.h"
//0-3.3
//0-4095 
float v = 0;
int main()
{
	OLED_Init();//初始化屏幕
    AD_ConvertInit();
	
	while(1)
	{	
		uint16_t value0 = getConvertValue(ADC_Channel_0);//2000
		uint16_t value1 = getConvertValue(ADC_Channel_1);//2000
		uint16_t value2 = getConvertValue(ADC_Channel_2);//2000
		
		OLED_ShowNum(1,1,value0,4);//0-4095
		OLED_ShowNum(2,1,value1,4);//0-4095
		OLED_ShowNum(3,1,value2,4);//0-4095
	}
	
}

````





# DMA

## 1.存储器映像

````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"

//SRAM的地址：从0x20000000开始的
//FLASH的地址：从0x08000000开始的，程序从这里开始的
//外设地址：PERIPH_BASE=0x40000000


//ADC1_BASE = APB2PERIPH_BASE + 0x2400  //0x40012400
//APB2PERIPH_BASE = PERIPH_BASE + 0x10000  0x40010000
//PERIPH_BASE = 0x40000000

//ADC1->DR外设寄存器  0x4001244C
//ADC1起始地址0x4001 2400

//ADC+DMA

uint8_t a = 0;
uint8_t b = 1;
const uint8_t c = 10;

int main()
{
	OLED_Init();//初始化屏幕
	OLED_ShowHexNum(1,1,(uint32_t)&a,8);//0x20000000---->byte
	OLED_ShowHexNum(2,1,(uint32_t)&b,8);//0x20000001---->byte
	OLED_ShowHexNum(3,1,(uint32_t)&c,8);//0x08000740
	OLED_ShowHexNum(4,1,(uint32_t)&ADC1->DR,8);
	
	while(1)
	{
		
	}
	
}

````

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

