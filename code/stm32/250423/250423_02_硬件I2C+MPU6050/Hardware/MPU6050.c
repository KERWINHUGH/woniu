#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"



//I2C初始化
void I2C_ModelInit(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//GPIO		PB10 = SCL(输出)		PB11 = SDA(输入+输出)
	//开漏模式下可以读取输入状态
	//输入模式下，输出开关断开，不能输出
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
		
	//2.I2C结构体
	I2C_InitTypeDef I2C_InitStruct;
//	I2C_StructInit(&I2C_InitStruct);//可以不用写
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;//是否自动应答
	I2C_InitStruct.I2C_ClockSpeed = 90000;//标准模式最快100K，快速模式最快400K
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;//作为从机的地址,给主机一个地址
	
	//给时钟信号用的，开漏输出模式下电平从1变0很快，mos管开关很快可以达到50MHz
	//但是从0变1外面有上拉电阻缓慢拉高电平，占空比就是上拉电阻拉高电平的速度
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	I2C_Init(I2C2,&I2C_InitStruct);
	
	I2C_Cmd(I2C2,ENABLE);
}

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
	//起始信号
	I2C_GenerateSTART(I2C2,ENABLE);
	//等待EV5，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);//EV5事件,start的完成事件
	
	//发送地址
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	//等待发送的EV6，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);//EV6事件，等待寻址结束
	
	I2C_SendData(I2C2,RegAdd);
	//等待发送的EV8，正在发送数据的事件，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);//EV8事件
	
	I2C_SendData(I2C2,data);
	//等待发送的EV8-2，发送数据结束，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);//EV8-2事件
	
	I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t MPU6050_Read(uint8_t RegAdd)
{
	//起始信号
	I2C_GenerateSTART(I2C2,ENABLE);
	//等待EV5，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//发送地址，写
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	//等待发送的EV6，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);//EV6事件的发送模式
	
	I2C_SendData(I2C2,RegAdd);
	//等待发送的EV8-2，发送数据结束的事件，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);//EV8-2事件，发送寄存器地址结束
	
	//起始信号
	I2C_GenerateSTART(I2C2,ENABLE);
	//等待EV5，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//发送地址，读
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Receiver);
	//等待发送的EV6，直到等于SUCCESS退出循环
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);//EV6事件的接收模式
	
	//问题1：结束信号提前发，告诉从机，接收到数据后就结束
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	//问题2：关闭自动应答
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	//接收数据		I2C结构体设置的自动回应ACK，这里会一直发送数据,提前关闭自动应答
	//接收数据时，等待接收数据寄存器有数据，再去接收
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);//EV7,接收数据寄存器不为空
	uint8_t data = I2C_ReceiveData(I2C2);
	
	//问题2：打开自动应答
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	
	return data;
}

void getMpu6050Data(MPU6050_Data *MPU6050_speedRegData)
{
	MPU6050_speedRegData->AccX =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
	MPU6050_speedRegData->AccY =  MPU6050_Read(ACCEL_YOUT_H) << 8 | MPU6050_Read(ACCEL_YOUT_L);
	MPU6050_speedRegData->AccZ =  MPU6050_Read(ACCEL_ZOUT_H) << 8 | MPU6050_Read(ACCEL_ZOUT_L);
	
	MPU6050_speedRegData->GyroX =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
	MPU6050_speedRegData->GyroY =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
	MPU6050_speedRegData->GyroZ =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
}

