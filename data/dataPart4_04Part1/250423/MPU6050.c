#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
/**
1.硬件I2C要使用：I2C时钟开启-结构体配置
2.硬件I2C开始，结束，发送数据.....
*/
void MPU6050_WriteData(uint8_t registerData,uint8_t data)
{
	//1.开始
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);//等待EV5事件，Start完成的事件
	
	//发送地址
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS);//EV6事件，等待地址发送完成

	I2C_SendData(I2C2,registerData);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING)!=SUCCESS);//EV8事件..继续放数据
	
	I2C_SendData(I2C2,data);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS);//EV8_2事件，表示结束
	
	I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t MPU6050_ReadData(uint8_t registerData)
{
	//开始
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);//等待EV5事件，Start完成的事件
	
	//发送地址，Write
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS);//EV6事件，等待地址发送完成

	//发送寄存器地址
	I2C_SendData(I2C2,registerData);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS);//EV8事件..继续放数据
	
	//重新开始
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);//等待EV5事件，Start完成的事件
	
	//发送地址 Read EV6事件有两种，一种是发送模式，Write，一种是接收模式（Read）
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!=SUCCESS);//EV6事件，等待地址发送完成
	
	//最麻烦的地方在这里  1.如果自动给回应，会不停的发数据
	//                    2.结束信号应该放哪里的问题？
	I2C_GenerateSTOP(I2C2,ENABLE);//1.STOP信号要提前发，告诉从机，接收到这个数据之后，就结束了
	//关闭自动应答
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	//一直等到RXNE，接收数据寄存器不为空
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED)!=SUCCESS);
	uint8_t data = I2C_ReceiveData(I2C2);//从数据寄存器读数据
	
	//打开自动应答
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	return data;
}


void I2CModel_Init(void)
{
	//1.开RCC时钟（GPIO，I2C）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	
	//2.GPIO结构体  PB10=SCL(输出)  PB11=SDA(输出，输入)
	//疑问：PB11配置成复用开漏以后，还能不能输入？
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;//复用开漏（因为是硬件帮我们发送数据）
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//3.I2C结构体
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;//是否自动应答
	I2C_InitStruct.I2C_ClockSpeed = 90000;//标准模式最大100k，快速400k
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_16_9;//SCL时钟信号用的
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;//给主机也给一个地址 
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//使用7位地址 
	I2C_Init(I2C2,&I2C_InitStruct);
	//4.启动
	I2C_Cmd(I2C2,ENABLE);
}

void MPU6050_Init(void)
{
	I2CModel_Init();
	
	//电源管理 1.睡眠模式  2.待机   3 时钟
	MPU6050_WriteData(PWR_MGMT_1,0x01);
	MPU6050_WriteData(PWR_MGMT_2,0x00);
	
	MPU6050_WriteData(SMPLRT_DIV,0x02);
	MPU6050_WriteData(CONFIG,0x06);
	MPU6050_WriteData(GYRO_CONFIG,0x18);
	MPU6050_WriteData(ACCEL_CONFIG,0x18);
}


void getMpu6050Data(MPU6050_Data *mpu6050Data)
{
	mpu6050Data->accX = MPU6050_ReadData(ACCEL_XOUT_H)<<8 | MPU6050_ReadData(ACCEL_XOUT_L);
	mpu6050Data->accY = MPU6050_ReadData(ACCEL_YOUT_H)<<8 | MPU6050_ReadData(ACCEL_YOUT_L);
	mpu6050Data->accZ = MPU6050_ReadData(ACCEL_ZOUT_H)<<8 | MPU6050_ReadData(ACCEL_ZOUT_L);
	mpu6050Data->groyX = MPU6050_ReadData(GYRO_XOUT_H)<<8 | MPU6050_ReadData(GYRO_ZOUT_L);
	mpu6050Data->groyY = MPU6050_ReadData(GYRO_YOUT_H)<<8 | MPU6050_ReadData(ACCEL_YOUT_L);
	mpu6050Data->groyZ = MPU6050_ReadData(GYRO_ZOUT_H)<<8 | MPU6050_ReadData(ACCEL_ZOUT_L);
}