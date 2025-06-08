#include "stm32f10x.h"                  // Device header
#include "Timer.h"

extern uint8_t num;

void Timer_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//1.5配置GPIO,引脚必须使用PA0，因为引脚定义中：TIM2的ETR对应就是PA0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//2配置时钟来源旋转编码器模拟外部时钟源
	//TIM_InternalClockConfig(TIM2);
	//TIM_ExtTRGPSC_OFF：输入时钟源要不要分频
	//TIM_ExtTRGPolarity_NonInverted:输入时钟源要不要翻转电平
	//0x00~0x0F：0x00：不滤波，值越大滤波越狠，耗费时间越久
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);
	
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
