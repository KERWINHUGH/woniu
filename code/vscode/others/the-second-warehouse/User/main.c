#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "RTC_MOD.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
uint8_t CLOCKFLAG = 0;
int main(void)
{
	uint32_t clocknow = 0;
	uint32_t clocklast = 0;
	/*模块初始化*/
	OLED_Init();									// OLED初始化
	RTC_Config();									// RTC初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级组2
	RCT_CLOCK_Config(RTC_GetCounter() + 10);
	clocklast = RTC_GetCounter();
	while (1)
	{
		if (CLOCKFLAG == 1)
		{
			clocknow= RTC_GetCounter();
			if (clocknow - clocklast >5)
			{
				OLED_ShowNum(4, 1, clocknow, 10);
				OLED_ShowNum(3,1,clocklast,10);
				//OLED_ClearLine(4);
				
				clocklast = clocknow;
			}
			CLOCKFLAG=0;
		}
		
		time_t now = RTC_GetCounter() + 8 * 3600;
		struct tm *p = localtime(&now);
		OLED_ShowNum(1, 1, p->tm_hour, 2);
		OLED_ShowChar(1, 3, ':');
		OLED_ShowNum(1, 4, p->tm_min, 2);
		OLED_ShowChar(1, 6, ':');
		OLED_ShowNum(1, 7, p->tm_sec, 2);
		OLED_ShowChar(2, 1, ' ');
		OLED_ShowNum(2, 2, p->tm_mday, 2);
		OLED_ShowChar(2, 4, '/');
		OLED_ShowNum(2, 5, p->tm_mon + 1, 2);
		OLED_ShowChar(2, 7, '/');
		OLED_ShowNum(2, 8, p->tm_year + 1900, 2);
		Delay_ms(1000);
	}
}
void RTC_IRQHandler(void)
{

	if (RTC_GetITStatus(RTC_IT_ALR) == SET)
	{
		OLED_ShowString(4, 4, "RTC Alarm");
		CLOCKFLAG = 1;
		RCT_CLOCK_Config(RTC_GetCounter() + 10);

		RTC_ClearITPendingBit(RTC_IT_ALR);
	}
}