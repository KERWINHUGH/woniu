#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "I2C_Model.h"

void MPU6050_Init(void)
{
	I2C_ModelInit();
	MPU6050_Write(PWR_MGMT_1,0x01);
	MPU6050_Write(PWR_MGMT_2,0x00);
	MPU6050_Write(SMPLRT_DIV,0x02);
	MPU6050_Write(CONFIG,0x06);
	MPU6050_Write(GYRO_CONFIG,0x18);
	MPU6050_Write(ACCEL_CONFIG,0x18);
	
}
void MPU6050_Write(uint8_t RegAdd,uint8_t data)
{
	I2C_ModelStart();
	I2C_ModelSendData(0xD0);
	I2C_ModelReceiveAck();
	
	I2C_ModelSendData(RegAdd);
	I2C_ModelReceiveAck();
	
	I2C_ModelSendData(data);
	I2C_ModelReceiveAck();
	I2C_ModelStop();
}
uint8_t MPU6050_Read(uint8_t RegAdd)
{
	I2C_ModelStart();
	I2C_ModelSendData(0xD0);
	I2C_ModelReceiveAck();
	
	I2C_ModelSendData(RegAdd);
	I2C_ModelReceiveAck();
	
	I2C_ModelStart();
	I2C_ModelSendData(0xD1);
	I2C_ModelReceiveAck();
	
	uint8_t data = I2C_ModelReceiveData();
	I2C_ModelSendAck(1);
	
	I2C_ModelStop();
	
	return data;
}
