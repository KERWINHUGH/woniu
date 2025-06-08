#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Motor.h"
#include "InputCapture.h"

int main()
{
	OLED_Init();
	Motor_Init();
	PWM_Init();//TIM2生成1000Hz波形
	TIM3_InputCaptureInit();
	
	OLED_ShowString(1,1,"fre:    Hz");
	OLED_ShowString(2,1,"duty:   %");
	while(1)
	{
//		OLED_ShowNum(1,1,TIM_GetCounter(TIM3),4);//0~999
//		OLED_ShowNum(2,1,1000000/(TIM_GetCapture1(TIM3)+1),4);//TIM3的CNT的频率/TIM2的频率
//		OLED_ShowNum(3,1,(TIM_GetCapture2(TIM3)+1),4);//TIM3的CNT的频率/TIM2的频率
		
		OLED_ShowNum(1,5,1000000/(TIM_GetCapture1(TIM3)+1),4);//TIM3的CNT的频率/TIM2的频率
		OLED_ShowNum(2,6,((TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1)),3);//TIM3的CNT的频率/TIM2的频率
	}
}
