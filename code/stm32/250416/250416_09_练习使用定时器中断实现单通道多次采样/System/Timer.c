#include "stm32f10x.h"
#include "Timer.h"

void TIM2_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.设置时钟源
	TIM_InternalClockConfig(TIM2);
	//3.设置时基结构体
	TIM_TimeBaseInitTypeDef TimeBaseInitStruct;
	TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStruct.TIM_Period = 10000-1;
	TimeBaseInitStruct.TIM_Prescaler = 7200-1;
	TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStruct);
	//3.5清除开启定时器自动加载的一次
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//4.开启定时器中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//5.配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	//6.开启定时器
	TIM_Cmd(TIM2,ENABLE);
}
