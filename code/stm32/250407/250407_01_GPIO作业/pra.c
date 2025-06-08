#include "stm32f10x.h"                  // Device header


void Delay(int ms)
{
	while(ms--);
}

/*
设置GPIOA0
*/
int main()
{
	//1.开时钟GPIO---APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.如果要使用GPIO,第一步先定义并初始化结构体，第二部调用GPIO Init初始化
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	while(1)
	{
		//3.操作GPIOA0
//		GPIO_SetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1);
//		Delay(5000000);
//		
//		GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1);
//		Delay(5000000);
		//点亮PA0
		GPIO_SetBits(GPIOA,GPIO_Pin_0 );
		Delay(5000000);
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_0 );
		Delay(5000000);
		
		//点亮PA1
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		Delay(5000000);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		Delay(5000000);
		//点亮PA2
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		Delay(5000000);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		Delay(5000000);
		//点亮PA3
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		Delay(5000000);
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		Delay(5000000);
		//点亮PA4
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		Delay(5000000);
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		Delay(5000000);
		
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
//		Delay(1000000);
//		
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
//		Delay(5000000);
	}
}
