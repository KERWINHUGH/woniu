#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Motor.h"
#include "Timer.h"
#include "EncoderInterface.h"

int16_t speed = 0;
int main()
{	
	OLED_Init();
	TIM3EncoderInit();
	
	Motor_Init();
	Timer4_Init();
	Left_SetSpeed(50);
	Right_SetSpeed(-50);
		
	while(1)
	{
		OLED_ShowSignedNum(1,1,speed,4);
	}
}
