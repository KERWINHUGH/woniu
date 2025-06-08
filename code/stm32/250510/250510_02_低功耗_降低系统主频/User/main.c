#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"

uint16_t num=0;
int main()
{
	OLED_Init();
	LED_Init();
	Key_Init();

	
	while(1)
	{
		OLED_ShowNum(1,1,num++,3);	
		Delay_ms(1000);
	}
}
