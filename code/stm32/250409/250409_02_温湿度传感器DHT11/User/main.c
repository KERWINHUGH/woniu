#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "DHT11.h"


TemHum NowTemHum={0};
int main()
{
	OLED_Init();//初始化屏幕
	DHT11_Init();
	
	OLED_ShowString(1,1,"Humi:");
	OLED_ShowString(1,8,".");
	OLED_ShowString(2,1,"Tem:");
	OLED_ShowString(2,7,".");
	OLED_ShowString(3,1,"check:");
	
	while(1)
	{
		DHT11_GetTemperAndHumidity(&NowTemHum);
		OLED_ShowNum(1,6,NowTemHum.Hum_Integer,2);
		OLED_ShowNum(1,9,NowTemHum.Hum_decimal,2);
		OLED_ShowNum(2,5,NowTemHum.Tem_Integer,2);
		OLED_ShowNum(2,8,NowTemHum.Tem_decimal,2);
		OLED_ShowNum(3,7,NowTemHum.checksum,3);
		//DHT11一次通讯时间最大3ms，主机连续采样间隔建议不小于100ms。
		//延迟200ms让给与采样间隔
		Delay_ms(200);
	}
	
}
