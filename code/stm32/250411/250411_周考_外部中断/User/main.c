#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Encoder.h"


int main()
{
	OLED_Init();//初始化屏幕
	LED_Init();
	Encoder_Init();//初始化编码器

	while(1)
	{
		OLED_ShowSignedNum(1,1,num,4);
		if(num > 5 || num < -5)
		{
			num = 0;
		}
		if(num == 0)
		{
			LED1_On();
			LED2_On();
			LED3_On();
		}else if(num > 0)
		{
			if(num == 1)
			{
				LED_negative_ms(500);
			}else if(num == 2)
			{
				LED_negative_ms(400);
			}else if(num == 3)
			{
				LED_negative_ms(300);
			}else if(num == 4)
			{
				LED_negative_ms(200);
			}else if(num == 5)
			{
				LED_negative_ms(100);
			}
		}else if(num < 0)
		{
			if(num == -1)
			{
				LED_negative_ms(500);
			}else if(num == -2)
			{
				LED_negative_ms(400);
			}else if(num == -3)
			{
				LED_negative_ms(300);
			}else if(num == -4)
			{
				LED_negative_ms(200);
			}else if(num == -5)
			{
				LED_negative_ms(100);
			}
		}
	}
}

