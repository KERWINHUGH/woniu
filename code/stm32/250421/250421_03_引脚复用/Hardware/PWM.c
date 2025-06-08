#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
	目标：生成一个PWM波形，频率为10000，占空比为20%
*/

void PWM_Init(void)
{
	//1.开启RCC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//引脚复用功能AFIO的功能（引脚复用）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//PA0------->PA15
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//解除PA15占用
	
	//2.配置TIM的输入来源
	TIM_InternalClockConfig(TIM2);
	//3.配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1 ;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	//4.配置输出比较单元----OC: Output Compare 
	//因为输出比较单元结构有4个成员是给高级定时器使用的，所以有一个专门的OC结构体初始化函数TIM_OCInitStruct，用来给结构体中所有成员赋初值
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	//TIM_OCMode_PWM1  模式1：CNT < CCR时，输出高电平，CNT >= CCR时，输出低电平
	//TIM_OCMode_PWM2  模式2：CNT > CCR时，输出高电平，CNT <= CCR时，输出低电平
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;	
	//TIM_OCPolarity_High  = 0x0000 ,在输出时不对产生的波形翻转
	//TIM_OCPolarity_Low  = 0x0002 ,在输出时对产生的波形翻转
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;	//输出波形的极性不变
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
	TIM_OCInitStruct.TIM_Pulse = 95;	//设置占空比
	
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);	//给TIM2的OC1配置输出比较
	//5.配置GPIO----使用TIM2_CH1 = PA0
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出，片上外设（定时器）帮输出高低电平，不是手动使用write或GPIO_SetBits设置
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//6.启动定时器
	TIM_Cmd(TIM2,ENABLE);
}
