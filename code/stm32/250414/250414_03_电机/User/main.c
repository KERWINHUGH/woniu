#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"
#include "Encoder.h"



int main()
{
	OLED_Init();
	PWM_Init();
	Encoder_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitSTruct;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTruct.GPIO_Pin = GPIO_Pin_2  | GPIO_Pin_1;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitSTruct);
	//调整电机转动方向
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	TIM_SetCompare1(TIM2,30);	//设置捕获比较寄存器	调整电机速度
	
	while(1)
	{
	
	}
}
