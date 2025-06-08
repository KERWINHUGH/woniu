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
		uint16_t  value0 = getConvertVal(ADC_Channel_0);
		uint16_t  value1 = getConvertVal(ADC_Channel_1);
		uint16_t  value2 = getConvertVal(ADC_Channel_2);

		OLED_ShowNum(1,1,value0,4);
		OLED_ShowNum(2,1,value1,4);
		OLED_ShowNum(3,1,value2,4);
	}
}

