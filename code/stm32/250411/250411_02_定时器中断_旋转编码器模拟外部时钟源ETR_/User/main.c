#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"

/**
获取PSC:TIM_GetPrescaler(TIM2);
设置PSC:TIM_PrescalerConfig(TIM2,3600,TIM_PSCReloadMode_Immediate);
获取ARR：TIM->ARR
设置ARR:TIM_SetAutoreload(TIM2,5000);
获取CNT：TIM_GetCounter(TIM2);
设置CNT:TIM_Setcounter(TIM2);
*/



uint8_t num = 0;

int main()
{
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1,1,"NUM:");
	OLED_ShowString(2,1,"PSC:");
	OLED_ShowString(3,1,"ARR:");
	OLED_ShowString(4,1,"CNT:");
	
	while(1)
	{
		OLED_ShowNum(1,5,num,4);
		OLED_ShowNum(2,5,TIM_GetPrescaler(TIM2),4);
		OLED_ShowNum(3,5,TIM2->ARR,4);
		OLED_ShowNum(4,5,TIM_GetCounter(TIM2),4);
	}
}
