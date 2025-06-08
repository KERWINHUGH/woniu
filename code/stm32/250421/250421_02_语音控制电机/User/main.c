#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Motor.h"
#include "Serial.h"

int main()
{
	OLED_Init();
	Motor_Init();
	Serial_Init();
	
	

	while(1)
	{

	}
}
