#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"


/**
PSC:获取：TIM_GetPrescaler(TIM2);
		设置:	TIM_PrescalerConfig();
ARR:获取：TIM2->ARR;
		设置：TIM_SetAutoreload(TIM2,1000);
CNT:TIM_GetCounter(TIM2);
		TIM_SetCounter();
*/
uint8_t num = 0;
int main()
{
	OLED_Init();
	Tim2_Init();
	OLED_ShowString(1,1,"NUM");
	OLED_ShowString(2,1,"PSC");
	OLED_ShowString(3,1,"ARR");
	OLED_ShowString(4,1,"CNT");
	while(1)
	{
		OLED_ShowNum(1,1,num,4);
		OLED_ShowNum(2,5,TIM_GetPrescaler(TIM2),4);
		OLED_ShowNum(3,5,TIM2->ARR,4);
		OLED_ShowNum(4,5,TIM_GetCounter(TIM2),4);
	}
}

//7.中断函数
void TIM2_IRQHandler(void)
{
	//判断中断来源
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		num++;
		//清除中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}

}
