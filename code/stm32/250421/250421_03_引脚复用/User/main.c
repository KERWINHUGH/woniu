#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"

int main()
{
	uint8_t i;
	PWM_Init();
	
	while(1)
	{
		for(i = 5; i < 100; i++)
		{
			TIM_SetCompare1(TIM2,i);	//设置捕获比较寄存器
			Delay_ms(10);
		}
		for(i = 99; i >= 5; i--)
		{
			TIM_SetCompare1(TIM2,i);	//设置捕获比较寄存器
			Delay_ms(10);
		}
	}
}
