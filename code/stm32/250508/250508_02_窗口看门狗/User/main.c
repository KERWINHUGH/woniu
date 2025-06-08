#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/******************************************
* 1.�趨���ڿ��Ź���30-50ms֮��ι��
* 2.
* 3.
* 4.
******************************************/


void wwdg_config(void)
{
	//1.��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	//2.���ÿ��Ź�
	WWDG_SetPrescaler(WWDG_Prescaler_8);//WWDG counter clock = (PCLK1/4096)/8  PCLK1 = 36MHz
	//3.���ô��ڿ��Ź������ڿ��Ź������ڼ���������0��û��ι�����趨�ļ�����ֵ֮ǰι�˹����������������ϵͳ��λ
	WWDG_SetWindowValue(0x40 + 21);
	//3.�������Ź�
//	WWDG_Enable(0x40 + 32);
	WWDG_Enable(0x40 + 54);//Ҫ�����������ֵ����0x40��0x7F֮��
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
