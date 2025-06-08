#include "stm32f10x.h"                  // Device header

void Delay(int ms)
{
	while(ms--);
}

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//int regester = 0x00000001;
		while(1)
	{
		for(uint8_t i = 0 ; i <5 ; i++)
		{
				GPIO_Write(GPIOA,0x0001 << i);
				Delay(5000000);
		}
	}
	
//	while(1)
//	{
//		GPIO_Write(GPIOA,0x00000001);
//		Delay(5000000);
//		GPIO_Write(GPIOA,0x00000002);
//		Delay(5000000);
//		GPIO_Write(GPIOA,0x00000004);
//		Delay(5000000);
//		GPIO_Write(GPIOA,0x00000008);
//		Delay(5000000);
//		GPIO_Write(GPIOA,0x00000010);
//		Delay(5000000);
//	}
}
