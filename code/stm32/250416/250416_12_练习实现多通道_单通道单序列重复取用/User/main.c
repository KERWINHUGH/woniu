#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADC_Converter.h"
#include "Timer.h"



int main()
{
	OLED_Init();
	ADC_Converter_Init();
	

	while(1)
	{
		uint16_t v0 =getConverval(ADC_Channel_0);
		uint16_t v1 =getConverval(ADC_Channel_1);
		uint16_t v2 =getConverval(ADC_Channel_2);
		OLED_ShowNum(1,1,v0,4);
		OLED_ShowNum(2,1,v1,4);
		OLED_ShowNum(3,1,v2,4);	
	}
}

//void ADC1_2_IRQHandler()
//{
//	//错误点3（看门狗中断）：获取中断状态和清除中断状态的参数都不是ADC_IT_EOC，而是ADC_IT_AWD
//	//if(ADC_GetITStatus(ADC1,ADC_IT_EOC) == SET)
//	if(ADC_GetITStatus(ADC1,ADC_IT_AWD) == SET)
//	{
//		//val = ADC_GetConversionValue(ADC1);
//		OLED_ShowString(4,1,"WARNING");
//		
//		//ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
//		ADC_ClearITPendingBit(ADC1,ADC_IT_AWD);
//	}
//}

