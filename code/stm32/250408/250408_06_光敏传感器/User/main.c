#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"


/*
4.找到光敏传感器，按照引脚降VCC，GND接好，，然后将DO引脚接入到单片机的A4上，
	遮挡光敏传感器和松开光敏传感器，会读取到0和1，
	然后根据做一个案例，根据光线的强弱，控制蜂鸣器的发生，比如光线弱的时候，蜂鸣器就响。
*/
int main()
{
	OLED_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct1;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStruct1.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct1);
	
	
	while(1)
	{
		uint8_t data = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
		if(data == 0)
		{
			OLED_ShowChar(1,1,'Y');
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
		}else if(data == 1)
		{
			OLED_ShowChar(1,1,'N');
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		}
	
	}
}
