#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "MPU6050.h"

int main()
{
	OLED_Init();

	MPU6050_Init();
	
	int16_t data = MPU6050_Read(ACCEL_ZOUT_H) <<8 | MPU6050_Read(ACCEL_ZOUT_L);
	
	OLED_ShowSignedNum(1,1,data,8);
	while(1)
	{
			
	}
}
