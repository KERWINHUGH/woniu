#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "DHT.h"

TemHumi NowTemHumi = {0};

int main()
{
	OLED_Init();
	DHT_Init();
	//TemHumi NowTemHumi = {0};

	OLED_ShowString(1,1,"Humi:");
	OLED_ShowString(1,8,".");
	OLED_ShowString(2,1,"Tem:");
	OLED_ShowString(2,7,".");
	OLED_ShowString(3,1,"CheckSum:");
	
	while(1)
	{
		DHT_GetNowTemHumi(&NowTemHumi);
		OLED_ShowNum(1,6,NowTemHumi.Humi_int,2);
		OLED_ShowNum(1,9,NowTemHumi.Humi_deci,2);
		OLED_ShowNum(2,5,NowTemHumi.Tem_int,2);
		OLED_ShowNum(2,8,NowTemHumi.Tem_deci,2);
		OLED_ShowNum(3,11,NowTemHumi.CheckSum,3);
		Delay_ms(200);
	}
}
