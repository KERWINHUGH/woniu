#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Encoder.h"


int main()
{
	OLED_Init();//初始化屏幕
	Encoder_Init();//初始化编码器

	while(1)
	{
		OLED_ShowSignedNum(1,1,num,4);
	}
}

