#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "I2C_SoftSimulate.h"

void MPU6050_Init(void)
{
	IIC_ModeInit();
}
//错误点1：写入数据需要传入参数
//0xD0是设备地址不用传
//需要传入的参数是要写入的寄存器地址和数据
void MPU6050_Write(uint8_t regArr,uint8_t data)
{
	IIC_Strat();
	IIC_SendData(0xD0);
	IIC_ReceiveAck();
	
	IIC_SendData(regArr);
	IIC_ReceiveAck();
	
	IIC_SendData(data);
	IIC_ReceiveAck();
	IIC_Stop();
}
//错误点2：读取数据需要传入参数
//0xD0和0xD1中0xD是设备地址；0和1读写方式，这两个参数不用传
//需要传入的参数是要读取的寄存器地址
uint8_t MPU6050_Read(uint8_t regArr)
{
	IIC_Strat();
	IIC_SendData(0xD0);
	IIC_ReceiveAck();
	
	IIC_SendData(regArr);
	IIC_ReceiveAck();
	
	IIC_Strat();
	IIC_SendData(0xD1);
	IIC_ReceiveAck();
	
	uint8_t data = IIC_ReceiveData();
	IIC_SendAck(1);
	IIC_Stop();
	return data;
}
