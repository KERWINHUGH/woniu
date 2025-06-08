#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "DHT11.h"


TemHum NowTemHum = {0};
int main()
{
	OLED_Init();//初始化屏幕
	DHT11_Init();
	LED_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"Tem:");
	OLED_ShowString(2,1,"NUM:000");
	
	while(1)
	{
		DHT11_GetTemperAndHumidity(&NowTemHum);

		OLED_ShowSignedNum(1,5,NowTemHum.Tem_Integer,2);
		
		//OLED_ShowSignedNum(2,5,num,3);
		

		//DHT11一次通讯时间最大3ms，主机连续采样间隔建议不小于100ms。
		//延迟200ms让给与采样间隔
		Delay_ms(200);
	}
	
}
