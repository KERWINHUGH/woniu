#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"

int main()
{
	OLED_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	
	while(1)
	{
		OLED_ShowString(1,1,"A:");
		OLED_ShowString(2,1,"B:");
		
		OLED_ShowNum(1,3,GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0),1);
		OLED_ShowNum(2,3,GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1),1);
	}
}
