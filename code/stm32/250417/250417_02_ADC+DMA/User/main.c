#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADC_Converter.h"

int main()
{
	OLED_Init();
	AD_ConverterInit();

	while(1)
	{
		OLED_ShowNum(1,1,array[0],4);
		OLED_ShowNum(2,1,array[1],4);
		OLED_ShowNum(3,1,array[2],4);
	}
}
