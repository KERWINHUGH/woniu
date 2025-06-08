#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//我们这个程序是给STM32主机写的，MPU6050里面已经有I2C协议的程序了。
void I2C_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化都是高电平
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

//SCL写函数
void I2C_ModelWriteSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10,data);
	Delay_us(5);
}
//SDA写
void I2C_ModelWriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11,data);
	Delay_us(5);
}

//SDA读
uint8_t I2C_ModelReadSDA(void)
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(5);
	return data;
}

void I2C_ModelStart(void)//主机开始
{
	I2C_ModelWriteSDA(1);//SDA高放前面
	I2C_ModelWriteSCL(1);
	
	I2C_ModelWriteSDA(0);
	I2C_ModelWriteSCL(0);
}

void I2C_ModelStop(void)//主机发送结束信息
{
	//SCL默认前面的操作，都以低电平结束
	I2C_ModelWriteSDA(0);
	
	I2C_ModelWriteSCL(1);
	I2C_ModelWriteSDA(1);//SDA一定要有一个SCL为高的情况下，SDA要从0到1的过程
}

void I2C_ModelSendData(uint8_t data)//主机发送一个数据（字节），高位现行   1100 0100
{
	for(uint8_t i = 0 ; i < 8 ; i++)
	{	
		//SCL低电平的时候主机放数据
		I2C_ModelWriteSDA(data & (0x80>>i)); //1100 0100 & 1000 0000 = 1000 0000
		//SCL拉高
		I2C_ModelWriteSCL(1);
		//从机读数据
		
		//SCL拉低
		I2C_ModelWriteSCL(0);
	}	
}

void I2C_ModelSendAck(uint8_t ack)//主机给从机一个相应1位
{
	I2C_ModelWriteSDA(ack);
	//SCL拉高
	I2C_ModelWriteSCL(1);
	//从机读应答
	
	//SCL拉低
	I2C_ModelWriteSCL(0);
}

uint8_t I2C_ModeReceiveData(void)//主机接收一个数据8位  1010 0100
{
	//主机释放数据线，给从机操作
	I2C_ModelWriteSDA(1);
	
	uint8_t data = 0x00;//1000 0000
	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		//从机放bit
		
		//SCL拉高
		I2C_ModelWriteSCL(1);
		//主机读数据,如果读到了1，才需要放到data中
		if(I2C_ModelReadSDA())
		{
			data |= (0x80>>i);
		}
		
		//SCL拉低		
		I2C_ModelWriteSCL(0);
	}
	return data;
}

uint8_t I2C_ModelReceiveAck(void)//主机接收响应只有1位，0表示应答，1表示不应答
{
	//主机释放数据线，给从机操作
	I2C_ModelWriteSDA(1);
	
	//从机放ACK
		
	//SCL拉高
	I2C_ModelWriteSCL(1);
	//主机读应答位
	uint8_t ack  = I2C_ModelReadSDA();

	//SCL拉低		
	I2C_ModelWriteSCL(0);
	
	return ack;
}















