#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//2.配置
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，默认就是输入的高电平
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

//判断哪一个按键被按了，如果被按了，就返回对应的数字，如果没有任何按键被按，返回0
uint8_t getKeyPressNum(void)
{
	uint8_t num = 0;
	
	//如果按键B1被按下了，读到一个0
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		//第一次按下之后，防止抖动
		Delay_ms(20);
		//按键已经稳定了，等待第一次松手为止
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		//防止松开后的抖动
		Delay_ms(20);
		
		num = 1;
	}
	
	//如果按了B11上的Key，返回2
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		//第一次按下之后，防止抖动
		Delay_ms(20);
		//按键已经稳定了，等待第一次松手为止
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		//防止松开后的抖动
		Delay_ms(20);
		
		num = 2;
	}
	
	
	return num;
}
