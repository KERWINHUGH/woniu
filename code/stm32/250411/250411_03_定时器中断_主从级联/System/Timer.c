#include "stm32f10x.h"                  // Device header
#include "Timer.h"

extern uint8_t num;

/**
将定时器TIM3的输出作为另一个定时器TIM2的输入
*/
void Tim3_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//2配置时钟来源----内部72MHz
	TIM_InternalClockConfig(TIM3);
	//3.配置时基单元
	TIM_TimeBaseInitTypeDef TIM_InitStrcut;
	TIM_InitStrcut.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStrcut.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStrcut.TIM_Period = 10000-1;
	TIM_InitStrcut.TIM_Prescaler = 7200-1;
	TIM_InitStrcut.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_InitStrcut);
	//4.把定时器设置为主模式，作为其他定时器的输入
	TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
	//4.5将TIM3设置为输出触发模式----The update event is selected as the trigger output (TRGO).
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
	
	//5.开启定时器
	TIM_Cmd(TIM3,ENABLE);
}


void Tim2_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//2.配置时钟来源----其他定时器		TIM3
	TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_External1);
	TIM_SelectInputTrigger(TIM2,TIM_TS_ITR2);//参考芯片参考手册14.4.3最后表格
	
	//3.配置时基单元
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 5 - 1;
	TIM_InitStruct.TIM_Prescaler = 1 - 1;//0:不分频
	TIM_InitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);
	
	//3.5清除配置定时器开启后自动重装载溢出的定时器标志
	//清除的是这个标志	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//TIM_ClearFlag(TIM2,TIM_IT_Update);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
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
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
