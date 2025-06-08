#include "stm32f10x.h"                  // Device header
#include "Timer.h"


/**
	使用定时器2，每秒产生一次中断
*/
//初始化定时器2
void Tim2_Init(void)
{
	//1.开TIM2的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//2.配置时钟来源，来自内部时钟TIMxCLK = 72MHz（因为时钟来源可能有多个）
	TIM_InternalClockConfig(TIM2);
	//3.配置时基单元的结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;//在进入预分配器之前，要不要先分屏DIV1，分频1不分频
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period = 10000 - 1;	//ARR	自动重装载寄存器0~65535，系统会将配置的值自动+1
	TIM_TimeBaseStruct.TIM_Prescaler = 7200 - 1;//PSC	预分频系数，系统会将配置的值自动+1
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	
	//因为定时器一启动,CNT就会产生产生一次溢出，这里提前把这个标志位清除掉
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
	//6.启动定时器
	TIM_Cmd(TIM2,ENABLE);
}
////7.中断函数
//void TIM2_IRQHandler(void)
//{
//	//判断中断来源
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//	{
//		num++;
//		//清除中断标志位
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}

//}




