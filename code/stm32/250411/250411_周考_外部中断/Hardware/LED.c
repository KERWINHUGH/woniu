#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"

/**
	PA0--LED1
	PA1--LED2
	高电平点亮(做产品用低电平点亮，不要使用单片机输出高电平)
*/
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}
void LED1_On(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2 );
}
void LED1_Off(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2 );
}
void LED1_Turn(void)
{
	//读取当前GPIOA的0号引脚输出的电平,如果是高返回1；如果是低，返回0
	uint8_t data = GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2);
	if(data)
	{
		LED1_Off();
	}else
	{
		LED1_On();
	}
}

void LED2_On(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3 );
}
void LED2_Off(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3 );
}
void LED2_Turn(void)
{
	//读取当前GPIOA的1号引脚输出的电平,如果是高返回1；如果是低，返回0
	if( GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_3))
	{
		LED2_Off();
	}else
	{
		LED2_On();
	}
}

void LED3_On(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4 );
}
void LED3_Off(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4 );
}
void LED3_Turn(void)
{
	//读取当前GPIOA的1号引脚输出的电平,如果是高返回1；如果是低，返回0
	if( GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_4))
	{
		LED3_Off();
	}else
	{
		LED3_On();
	}
}


void LED_Positive_ms(uint16_t ms)
{
			LED1_On();
			Delay_ms(ms);
			LED1_Off();
			LED2_On();
			Delay_ms(ms);
			LED2_Off();
			LED3_On();
			Delay_ms(ms);
			LED3_Off();
}

void LED_negative_ms(uint16_t ms)
{
			LED3_On();
			Delay_ms(ms);
			LED3_Off();
			LED2_On();
			Delay_ms(ms);
			LED2_Off();
			LED1_On();
			Delay_ms(ms);
			LED1_Off();
}