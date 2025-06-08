#include "stm32f10x.h"                  // Device header

/**
   PA0--LED1
   PA1--LED2
   高电平点亮（做产品尽量用低电平点亮，不要使用单片机输入高电平）
*/
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void LED1_On(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

void LED1_Off(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

//LED1灯翻转电平
void LED1_Turn(void)
{
	//读取当前GPIOA的0号引脚输出的电平,如果是高，返回1，低返回0
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0))
	{
		LED1_Off();
	}
	else
	{
		LED1_On();
	}
}

void LED2_On(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
void LED2_Off(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1))
	{
		LED2_Off();
	}
	else
	{
		LED2_On();
	}
}
