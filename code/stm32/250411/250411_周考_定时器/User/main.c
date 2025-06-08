#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"

int main()
{
	OLED_Init();
	Tim_Init();
	Key_Init();
	
	OLED_ShowString(1,4,":");
	OLED_ShowString(1,7,":");
	
	while(1)
	{
		//错误6：显示有符号整数时，应该使用带符号显示的格式
		OLED_ShowNum(1,2,hour,2);
		OLED_ShowNum(1,5,min,2);
		OLED_ShowNum(1,8,sec,2);
	}
	
//	OLED_ShowString(1,1,"NUM:");
//	OLED_ShowString(2,1,"ARR:");
//	OLED_ShowString(3,1,"PSC:");
//	OLED_ShowString(4,1,"CNT:");
//	
//	while(1)
//	{
//		OLED_ShowNum(1,5,num,4);
//		//错误点2：获得ARR的值，直接使用TIM2->ARR
//		//OLED_ShowNum(2,5,TIM_GetFlagStatus(TIM2,TIM_FLAG_Update),4);
//		OLED_ShowNum(2,5,TIM2->ARR,4);
//		//错误点3：获得PSC的值使用TIM_GetPrescaler函数
//		//OLED_ShowNum(3,5, ,4);
//		OLED_ShowNum(3,5,TIM_GetPrescaler(TIM2),4);
//		OLED_ShowNum(4,5,TIM_GetCounter(TIM2),5);
//	}
}
