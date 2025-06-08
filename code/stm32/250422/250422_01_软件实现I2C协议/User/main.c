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
	
	uint8_t acc_z_h = MPU6050_Read(0x3F);
	uint8_t acc_z_l = MPU6050_Read(0x40);
	
	//C语言的移位操作，默认先转换为32位
	int16_t acc_z = acc_z_h << 8 | acc_z_l;

	OLED_ShowSignedNum(1,1,acc_z,8);
	

	while(1)
	{

	}
}
