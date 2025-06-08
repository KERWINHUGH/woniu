#include "stm32f10x.h"                  // Device header
#include "ADCConverter.h"

/**
**测试外部可变电阻的电压值，使用ADC的12次逐次逼近
**引脚连在PA0----对应ADC1_IN0
*/

void ADCConverter_Init(void)
{
	//1.开启ADC1和GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.GPIO结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//3.选择ADC逐次逼近的时钟，去驱动ADC采样，APB2总线是72MHz，官方要求ADC最大频率不超过14MHz，所有选择6分频，72M/6 = 12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//4.配置规则组通道，可以有十六个通道同时采样，但只有一个寄存器存储采样值，但使用DMA直接访问
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_41Cycles5);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_41Cycles5);
	//5.ADC结构体
	ADC_InitTypeDef ADCInitStruct;
	ADCInitStruct.ADC_ContinuousConvMode = DISABLE;//不需要连续转换
	ADCInitStruct.ADC_DataAlign = ADC_DataAlign_Right;//对齐方式
	//外部触发转换，ADC使能后需要一个事件触发，ADC才开始转换，NONE不适用外部转换，内部写代码实现
	ADCInitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;//使用定时器3		TIM3触发
	ADCInitStruct.ADC_Mode = ADC_Mode_Independent;//只使用ADC1进行转换
	ADCInitStruct.ADC_NbrOfChannel = 1;//指定要转换的ADC通道的数量
	ADCInitStruct.ADC_ScanConvMode = DISABLE;//规则组通道中，如果只接了一个通道，不需要扫描，接了多个通道需要扫描
	ADC_Init(ADC1,&ADCInitStruct);
	
	//************************添加一个模拟看门狗的功能***************************
	//配置看门狗

	ADC_AnalogWatchdogThresholdsConfig(ADC1,4000,1000);//设置高阈值和低阈值
	ADC_AnalogWatchdogSingleChannelConfig(ADC1,ADC_Channel_0);
	ADC_AnalogWatchdogCmd(ADC1,ADC_AnalogWatchdog_SingleRegEnable);//看门狗监视单规则组通道
	//ADC看门狗中断
	ADC_ITConfig(ADC1,ADC_IT_AWD,ENABLE);
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	//中断函数
	
	//6启动ADC
	ADC_Cmd(ADC1,ENABLE);
	//7.校准--固定代码，不用记
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);//获取校准状态，等待校准完成为止	SET = 1,开始校准，RESET = 0，校准完成
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) != RESET);//获取校准状态，等待校准完成为止	SET = 1,开始校准，RESET = 0，校准完成

	//1.使用代码推动一次转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//开启连续转换后，后续将连续转换
}
//获得采集到的值
uint16_t getConvertVal(void)
{
		//1.使用代码推动一次转换
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		
		//2.获取状态位
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//RESET = 0	转换完成
		//3.获取转换之后的值
		return ADC_GetConversionValue(ADC1);
}
