#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "IIC_Mode.h"

void MPU6050_Init(void)
{
	I2C_ModeInit();
	MPU6050_Write(PWR_MGMT_1,0x01);
	MPU6050_Write(PWR_MGMT_2,0x00);
	MPU6050_Write(SMPLRT_DIV,0x02);
	MPU6050_Write(CONFIG,0x06);
	MPU6050_Write(GYRO_CONFIG,0x18);
	MPU6050_Write(ACCEL_CONFIG,0x18);
}

void MPU6050_Write(uint8_t regAdd, uint8_t data)
{
	//MPU6050写的时序
	I2C_ModeStart();
	I2C_ModeSendData(0xD0);//寻找设备+写操作（需要的读写操作）
	I2C_ModeReceiverACK();
	
	I2C_ModeSendData(regAdd);//选择要配置的寄存器地址
	I2C_ModeReceiverACK();
	
	I2C_ModeSendData(data);//发送数据配置电源
	I2C_ModeReceiverACK();
	
	I2C_ModeStop();
}

uint8_t MPU6050_Read(uint8_t regAdd)
{
	//MPU6050读的时序
	//前半部分先设置写的时序，将寄存器指针指向要读的寄存器
	I2C_ModeStart();
	I2C_ModeSendData(0xD0);//寻找设备+写操作（需要的读写操作）
	I2C_ModeReceiverACK();
	
	I2C_ModeSendData(regAdd);//选择要配置的寄存器地址
	I2C_ModeReceiverACK();
	
	//后半部分设置读的时序,直接去读寄存器，不用去发要读的寄存器地址
	I2C_ModeStart();
	I2C_ModeSendData(0xD1);//寻找设备+读操作（需要的读写操作）
	I2C_ModeReceiverACK();
	
	uint8_t data = I2C_ModeReceiveData();//发送数据配置电源
	I2C_ModeSendACK(1);//发1表示非应答，发0表示应答，如果应答为0，从机指针会向后移动继续发送数据
	
	I2C_ModeStop();
	
	return data;
}

