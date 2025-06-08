#include "stm32f10x.h" 
#include "Timer.h"


//uint8_t num = 0;
void Tim_Init(void)
{
	//1.配置定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//2.配置定时器时钟源,配置内部时钟
	TIM_InternalClockConfig(TIM2);
	//3.配置时基结构体
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//预分频之前不分频 == 除以1
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;//CNT----累加上升计数
	TIM_InitStruct.TIM_Period = 10000 - 1;//ARR
	TIM_InitStruct.TIM_Prescaler = 7200 - 1;//PSC
	TIM_InitStruct.TIM_RepetitionCounter = 0x00;
	//TIM_TimeBaseStructInit(&TIM_InitStruct);
	//错误点1：初始化结构体使用TIM_TimeBaseInit，而不是TIM_TimeBaseStructInit
	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);
	
	//加强点：因为定时器一启动,CNT就会产生产生一次溢出，这里提前把这个标志位清除掉
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	//4.配置定时器中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//5.配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	//6.开启定时器
	TIM_Cmd(TIM2,ENABLE);
}
//7.定时器中断处理函数
void TIM2_IRQHandler(void)
{
	//判断中断来源
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		//num++;
		//清除中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}	
}
