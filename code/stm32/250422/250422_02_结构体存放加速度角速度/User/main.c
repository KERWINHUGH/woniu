#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "IIC_Mode.h"
#include "MPU6050.h"

//MPU6050		VCC GND  SCL = PB10  SDA = PB11

int main()
{
	OLED_Init();
	
	MPU6050_Init();
	
	SpeedRegData speedRegdata = {0};

	while(1)
	{
		//C语言的移位操作，默认先转换为32位
		speedRegdata.ACCEL_XOUT =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
		speedRegdata.ACCEL_YOUT =  MPU6050_Read(ACCEL_YOUT_H) << 8 | MPU6050_Read(ACCEL_YOUT_L);
		speedRegdata.ACCEL_ZOUT =  MPU6050_Read(ACCEL_ZOUT_H) << 8 |  MPU6050_Read(ACCEL_ZOUT_L);

		OLED_ShowSignedNum(1,1,speedRegdata.ACCEL_XOUT,4);
		OLED_ShowSignedNum(1,9,speedRegdata.ACCEL_YOUT,4);
		OLED_ShowSignedNum(2,1,speedRegdata.ACCEL_ZOUT,4);
		
		speedRegdata.GYRO_XOUT =  MPU6050_Read(GYRO_XOUT_H) << 8 | MPU6050_Read(GYRO_XOUT_L);
		speedRegdata.GYRO_YOUT =  MPU6050_Read(GYRO_YOUT_H) << 8 | MPU6050_Read(GYRO_YOUT_L);
		speedRegdata.GYRO_ZOUT =  MPU6050_Read(GYRO_ZOUT_H) << 8 | MPU6050_Read(GYRO_ZOUT_L);

		OLED_ShowSignedNum(3,1,speedRegdata.ACCEL_XOUT,4);
		OLED_ShowSignedNum(3,9,speedRegdata.ACCEL_YOUT,4);
		OLED_ShowSignedNum(4,1,speedRegdata.ACCEL_ZOUT,4);
	}
}
