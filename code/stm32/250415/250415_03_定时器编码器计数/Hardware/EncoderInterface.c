#include "stm32f10x.h"                  // Device header
#include "EncoderInterface.h"

/*
**旋转编码器A相接在TIM3_CH1 = PA6
**旋转编码器B相接在TIM3_CH2 = PA7
*/
void TIM3EncoderInit(void)
{
	//1.开启时钟，GPIOA,TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，默认输入高电平
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6  | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//3.输入捕获
	TIM_ICInitTypeDef TIM_ICInitStruct ;
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0xF;
//	TIM_ICInitStruct.TIM_ICPolarity = ;//不用设置
//	TIM_ICInitStruct.TIM_ICPrescaler = ;
//	TIM_ICInitStruct.TIM_ICSelection = ;
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
//	TIM_ICInitStruct.TIM_ICFilter = 0x0;
//	TIM_ICInitStruct.TIM_ICPolarity = ;
//	TIM_ICInitStruct.TIM_ICPrescaler = ;
//	TIM_ICInitStruct.TIM_ICSelection = ;
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	//4.配置编码器接口,TI1和TI2都计数，rising表示TIM2和TIM3不翻转电平
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	//5.时基单元
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 65536 - 1;
	TIM_InitStruct.TIM_Prescaler = 1-1;
	TIM_InitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_InitStruct);
	//6.开启定时器
	TIM_Cmd(TIM3,ENABLE);
}

