#include "stm32f10x.h"                  // Device header


void TIM3_Init(void)
{
	//1.时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//2.定时器时钟来源
	TIM_InternalClockConfig(TIM3);
	//3.时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	//4.设置主模式+输出触发
	TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);//更新事件
	//5.启动定时器
	TIM_Cmd(TIM3,ENABLE);
}