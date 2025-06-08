#include "stm32f10x.h"                  // Device header
#include "Timer.h"

extern int16_t Left_Speed;
extern int16_t Right_speed;

void Timer2_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//2配置时钟来源
	TIM_InternalClockConfig(TIM2);
	//3.配置时基单元
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 10000 - 1;			//1s产生一个定时器中断
	TIM_InitStruct.TIM_Prescaler = 7200 - 1;
	TIM_InitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);
	
	//3.5清除配置定时器开启后自动重装载溢出的定时器标志
	//清除的是这个标志	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//TIM_ClearFlag(TIM2,TIM_IT_Update);
	
	//4.配置定时器中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//5.配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	//6.开启定时器
	TIM_Cmd(TIM2,ENABLE);
}

