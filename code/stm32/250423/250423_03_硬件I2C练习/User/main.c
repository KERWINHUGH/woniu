#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "MPU6050.h"
#include "IMU.h"

int main()
{
	OLED_Init();
	MPU6050_Init();
	
	while(1)
	{
		IMU_getEuleranAngles();
		OLED_ShowSignedNum(1,1,imu_Angle.Pitch,4);
		OLED_ShowSignedNum(2,1,imu_Angle.Yaw,4);
		OLED_ShowSignedNum(3,1,imu_Angle.Roll,4);//只有六轴，算出来的翻滚叫会产生漂移
	}
}
