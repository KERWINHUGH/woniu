#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Motor.h"

int main()
{
	Motor_Init();
	Left_SetSpeed(0);
	Right_SetSpeed(0);

	while(1)
	{
		
	}
}
