#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"

int main()
{
	OLED_Init();
	LED_Init();
	Key_Init();

	while(1)
	{
		uint8_t keyNum = getKeyPressNum();
		if(keyNum == 1)
		{
			LED1_Turn();
			//OLED_ShowBinNum(1,1,keyNum,1);
		}else if(keyNum == 2)
		{
			LED2_Turn();
		}		
	}
}
