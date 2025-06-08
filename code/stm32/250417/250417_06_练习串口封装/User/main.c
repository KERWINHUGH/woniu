#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"


int main()
{
	OLED_Init();
	USART_Config();
	printf("%d,%s",123,"abc");
	//SendByte('A');
//	uint8_t arr[3] ={0x30,0x31,0x32};
//	SendArr(arr,3);
	SendStr("abCD");
	SendNumber(12345);

	while(1)
	{

	}
}
