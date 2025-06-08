#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"
int main()
{

	OLED_Init();//³õÊ¼»¯ÆÁÄ»
	DHT11_Init();
	DHT11_Req();
	DHT11_Resp();
	
	uint8_t data1 = DHT11_GetByteData();
	uint8_t data2 = DHT11_GetByteData();
	uint8_t data3 = DHT11_GetByteData();
	uint8_t data4 = DHT11_GetByteData();
	uint8_t data5 = DHT11_GetByteData();
	OLED_ShowNum(1,1,data1,3);
	OLED_ShowNum(1,6,data2,3);
	OLED_ShowNum(2,1,data3,3);
	OLED_ShowNum(2,6,data4,3);
	OLED_ShowNum(3,1,data5,3);
	while(1)
	{
		
	}
	
}
