#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/******************************************
* 1.设定窗口看门狗在30-50ms之间喂狗
* 2.
* 3.
* 4.
******************************************/


void wwdg_config(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	//2.设置看门狗
	WWDG_SetPrescaler(WWDG_Prescaler_8);//WWDG counter clock = (PCLK1/4096)/8  PCLK1 = 36MHz
	//3.设置窗口看门狗：窗口看门狗可以在计数器到达0后没有喂狗和设定的计数器值之前喂了狗，这两种情况会让系统复位
	WWDG_SetWindowValue(0x40 + 21);
	//3.启动看门狗
//	WWDG_Enable(0x40 + 32);
	WWDG_Enable(0x40 + 54);//要传入计数器的值，在0x40到0x7F之间
}

uint16_t num = 0;
int main()
{
	OLED_Init();
	wwdg_config();
	while(1)
	{
		OLED_ShowNum(1,1,num++,4);
		Delay_ms(30);
		WWDG_SetCounter(0x40 + 54);
	}
}
