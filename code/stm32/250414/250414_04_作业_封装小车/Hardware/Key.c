#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "Delay.h"

void Key_Init(void)
{
		//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//2.配置PB1
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，默认输入高电平
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1  | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

//判断哪一个按键被按下，如果有按键被按下，返回对应数字，如果没有任何按键按下，返回0
uint8_t getKeyPressNum(void)
{
	uint8_t num = 0;
	
	//按键B1被按下，读取到一个0
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
	{
		Delay_ms(20);//第一次按下后，防止抖动
		//按键稳定时，一直等待按键松开
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
		Delay_ms(20);//防止松开后的抖动
		num = 1;
	}
		//按键B11被按下，读取到一个0
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
	{
		Delay_ms(200);//第一次按下后，防止抖动
		//按键稳定时，一直等待按键松开
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
		Delay_ms(50);//防止松开后的抖动
		num = 2;
	}
	
	return num;
}
