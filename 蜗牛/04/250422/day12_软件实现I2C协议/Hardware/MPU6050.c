#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"

void MPU6050_Write(uint8_t registerAddress,uint8_t data)
{
	I2C_ModelStart();
    
	I2C_ModelSendData(0xD0);//寻找设备+写
	I2C_ModelReceiveAck();
	
	I2C_ModelSendData(registerAddress);//配置寄存器地址
	I2C_ModelReceiveAck();
	
	I2C_ModelSendData(data);//发送数据
	I2C_ModelReceiveAck();
	
	I2C_ModelStop();
}

uint8_t MPU6050_Read(uint8_t registerAddress)
{
	//先写是为了固定寄存器地址
	I2C_ModelStart();
	I2C_ModelSendData(0xD0);//寻找设备+写W=0
	I2C_ModelReceiveAck();

	//配置寄存器地址，MPU 6050的寄存器指针会指向相应的寄存器地址的位置。等会读的时候，会直接从这个地址返回数据
	I2C_ModelSendData(registerAddress);//配置寄存器地址
	I2C_ModelReceiveAck();
	
	//重新开始
	I2C_ModelStart();
	I2C_ModelSendData(0xD1);//寻找设备+读R=1
	I2C_ModelReceiveAck();
	
	//直接从之前写入的地址的位置，开始返回数据
	uint8_t data = I2C_ModeReceiveData();
	I2C_ModelSendAck(1);//发1表示非应答  发0表示应答，而且会继续发送数据
	
	I2C_ModelStop();
	return data;
}

void MPU6050_Init(void)
{
	I2C_ModelInit();
	//配置MPU6050相关寄存器的值
	MPU6050_Write(PWR_MGMT_1,0x01);
	MPU6050_Write(PWR_MGMT_2,0x00);
	MPU6050_Write(SMPLRT_DIV,0x02);
	MPU6050_Write(CONFIG,0x06);
	MPU6050_Write(GYRO_CONFIG,0x18);
	MPU6050_Write(ACCEL_CONFIG,0x18);
}










