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
	LED_Init();
	Key_Init();

	OLED_ShowString(1,1,"Tem:");
	OLED_ShowString(2,1,"Sign:");
	uint8_t num = 20;
	while(1)
	{

		DHT11_GetTemperAndHumidity(&NowTemHum);

		OLED_ShowSignedNum(1,5,NowTemHum.Tem_Integer,2);
		//OLED_ShowSignedNum(2,6,keyNum,3);
		
		uint8_t keyNum = getKeyPressNum();
		if(keyNum == 1)
		{
			//LED2_Turn();
			OLED_ShowSignedNum(2,6,num++,4);
		}else if(keyNum == 2)
		{
			//LED2_Turn();
			OLED_ShowSignedNum(2,6,num--,4);
		}
		
		if(NowTemHum.Tem_Integer > num)
		{
			LED2_On();
		}else
		{
			LED2_Off();
		}
		//DHT11一次通讯时间最大3ms，主机连续采样间隔建议不小于100ms。
		//延迟200ms让给与采样间隔
		Delay_ms(200);
	}
}
