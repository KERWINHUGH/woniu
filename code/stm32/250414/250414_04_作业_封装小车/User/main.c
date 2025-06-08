#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"
#include "Encoder.h"
#include "Car_Dsc.h"


int main()
{
	OLED_Init();
	PWM1_Init();
	PWM2_Init();
	

//	Left_Forward();
	Left_Backward();
	Left_Speed(30);
	
	Right_Forward();
//	Right_Backward();
	Right_Speed(30);
	
	while(1)
	{
	
	}
}
