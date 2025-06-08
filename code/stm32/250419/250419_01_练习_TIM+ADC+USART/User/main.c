#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "TIMER.h"
#include "ADC_Sample.h"
#include "USART.h"

int main()
{
	OLED_Init();
	TIM23_Init();
	ADC_SampleInit();
	Serial_Init();
//	uint8_t arr[2] = {0x33,0x34};
//	Serial_SendArr(arr,2);
//	Serial_SendStr("hello");
//	Serial_SendNum(12345678);
//	printf("%d:%s",1234,"one,two,t,f");
	
	while(1)
	{	
		OLED_ShowNum(4,1,num,3);
		
	}
}
