#include "stm32f10x.h"
#include "Timer.h"

//错误点1：定时器触发规则组的ADC转换，只能使用定时器3
void TIM3_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//定时器触发规则组，不需要设置GPIO
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.设置时钟源
	TIM_InternalClockConfig(TIM3);
	//3.设置时基结构体
	TIM_TimeBaseInitTypeDef TimeBaseInitStruct;
	TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStruct.TIM_Period = 10000-1;
	TimeBaseInitStruct.TIM_Prescaler = 7200-1;
	TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TimeBaseInitStruct);
	//3.5清除开启定时器自动加载的一次
	//TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//4.设置定时器主模式和输出模式
	//错误点2：定时器触发规则组不需要定时器中断，需要设置定时器为主模式输出
	TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);

	//5.开启定时器
	TIM_Cmd(TIM3,ENABLE);
}
