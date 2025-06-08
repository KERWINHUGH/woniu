#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADCConverter.h"

//			0 -- 3.3V
//对应  0 -- 4095
float v = 0;
int main()
{
	OLED_Init();
	ADCConverter_Init();

	while(1)
	{
		uint16_t  value = ADC_GetConversionValue(ADC1);
		//获取电压整数
		v = (float)value * 3.3/4096;
		OLED_ShowNum(2,1,v,1);

		OLED_ShowString(2,2,".");
				OLED_ShowNum(2,3,(uint32_t)(v*100)%100,2);
		OLED_ShowNum(1,1,getConvertVal(),4);
	}
}

