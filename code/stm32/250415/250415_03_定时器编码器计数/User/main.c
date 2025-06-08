#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "EncoderInterface.h"
/**
获取PSC:TIM_GetPrescaler(TIM2);
设置PSC:TIM_PrescalerConfig(TIM2,3600,TIM_PSCReloadMode_Immediate);
获取ARR：TIM->ARR
设置ARR:TIM_SetAutoreload(TIM2,5000);
获取CNT：TIM_GetCounter(TIM2);
设置CNT:TIM_Setcounter(TIM2);
*/



int16_t speed = 0;

int main()
{
	OLED_Init();
	Timer_Init();
	TIM3EncoderInit();
		
	while(1)
	{
		OLED_ShowSignedNum(1,1,speed,4);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		speed = TIM_GetCounter(TIM3);
		TIM_SetCounter(TIM3,0);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
