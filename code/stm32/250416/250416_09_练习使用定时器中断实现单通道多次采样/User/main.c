#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADC_Converter.h"
#include "Timer.h"


uint16_t val = 0;
float v = 0 ;
int main()
{
	OLED_Init();
	ADC_Converter_Init();
	TIM2_Init();

	while(1)
	{
		//错误点3：采集到的数据要放到while循环中
		//val = ADC_GetConversionValue(ADC1);//多次采样获取数据：步骤三
		v =(float)val*3.3/4096;
		OLED_ShowNum(2,1,v,1);
		OLED_ShowNum(2,3,(uint32_t)(v*100)%100,2);
		OLED_ShowString(2,2,".");
		OLED_ShowNum(1,1,val,4);
		
	}
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		val = ADC_GetConversionValue(ADC1);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
