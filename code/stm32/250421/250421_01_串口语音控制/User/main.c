#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"


int main()
{
	OLED_Init();
	Serial_Init();
	LED_Init();
	
	//Serial_Byte(0x31);
//	uint8_t arr[3] = {0x31,0x32,0x33};
//	Serial_Arr(arr,3);
//	Serial_String("abCD");
//	Serial_Number(123456);
//	printf("%d,%s",7890,"ASDFHJ");
//	printf("\n");
	uint16_t sam[2] = {2299};
//	
	OLED_ShowHexNum(1,1,sam[0],4);
	uint8_t h = (sam[0]>>8)&0xFF;
	uint8_t l = sam[0]&0xFF;
//	
	OLED_ShowHexNum(2,1,h,4);
	OLED_ShowHexNum(3,1,l,4);
	
	//Serial_Byte(sam[0]);
	
	Serial_Byte(h);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	Serial_Byte(l);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	
	while(1)
	{
		
	}
}
