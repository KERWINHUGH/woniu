#include "stm32f10x.h"                  // Device header
#include "InputCapture.h"

void TIM3_InputCaptureInit(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//2.配置时钟来源
	TIM_InternalClockConfig(TIM3);
	//3.配置时基结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536-1;//ARR,设置值为最大，不让计数器有机会清零，输入捕获跟ARR只有这一点影响，测试频率不能太小
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	//4.输入捕获结构体
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;//使用通道1，TIM_CH1 = PA6
	TIM_ICInitStruct.TIM_ICFilter =0xF;//滤波
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;//外部波形在上升沿触发
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;//不分频
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;//直连到当前通道CH1
//	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
//	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;//使用通道2，TIM_CH2 = PA7
//	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;//外部波形在下降沿触发
//	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;//交叉连到通道CH1通道1
//	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);//取代上面五行代码，内部就是执行上面的代码

	//5.清零CNT,官方提供TI1FP1会自动触发从模式，从模式去清零计数器
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);//选择TIFP1作为从模式的输入
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//把TIM3的CNT清零
	//6.开启定时器
	TIM_Cmd(TIM3,ENABLE);
}
