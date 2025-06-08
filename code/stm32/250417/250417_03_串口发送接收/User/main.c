#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"

/**
**
**
**
*/
uint8_t data =0;
int main()
{
	OLED_Init();
	Serial_Init();
	LED_Init();
	
	printf("%d",data);
	Send_Numbers(12345);
	while(1)
	{
		//uint8_t data = USART_ReceiveData(USART1);
		OLED_ShowNum(1,1,data,4);
		
	}
}
