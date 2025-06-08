#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "DMA_M2M.h"
#include "ADC_Converter.h"



int main()
{
	OLED_Init();
	ADC_ConvertInit();

	while(1)
	{
		OLED_ShowNum(1,1,arr[0],4);
		OLED_ShowNum(2,1,arr[1],4);
		OLED_ShowNum(3,1,arr[2],4);

	}
}
