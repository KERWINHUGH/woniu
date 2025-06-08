#include "stm32f10x.h"                  // Device header
#include "IIC_Mode.h"
#include "Delay.h"

//GPIO
void I2C_ModeInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化为高电平（外部上拉电阻拉到3.3V，成为高电平，开漏模式不会输出高电平）
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}
//SCL写函数
void I2C_ModeWriteSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)data);
	Delay_us(5);
}
//SDA写函数
void I2C_ModeWriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)data);
	Delay_us(5);
}
//SDA读函数
uint8_t I2C_ModeReadSDA(void)
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(5);
	return data;
}
//主机控制开始信号
void I2C_ModeStart(void)
{
	//初始化操作，两根线都拉高
	I2C_ModeWriteSDA(1);//SDA先拉高，和结束信号做区分
	I2C_ModeWriteSCL(1);
	//发送开始信号
	I2C_ModeWriteSDA(0);
	I2C_ModeWriteSCL(0);
}
//主机发送结束信号
void I2C_ModeStop(void)
{
	//SCL默认前面的操作都以低电平结束，这边不用给SCL前提条件
	//只给SDA的初始条件
	I2C_ModeWriteSDA(0);
	
	I2C_ModeWriteSCL(1);
	I2C_ModeWriteSDA(1);//SDA一定要有一个SCL为高的情况下，SDA要从0到1的过程
}

//主机给从机发送一位的应答（ACK）
void I2C_ModeSendACK(uint8_t ack)
{
	I2C_ModeWriteSDA(ack);
	//SCL拉高
	I2C_ModeWriteSCL(1);
	//从机读数据
	
	//SCL拉低
	I2C_ModeWriteSCL(0);
}

//主机发送一个字节数据的消息
void I2C_ModeSendData(uint8_t data)
{
	for(uint8_t i = 0; i < 8; i++)
	{
	//SCL低电平时  主机放数据
	I2C_ModeWriteSDA(data & (0x80>>i));
	//SCL拉高
	I2C_ModeWriteSCL(1);
	//从机读数据
	
	//SCL拉低
	I2C_ModeWriteSCL(0);

	}
}

//主机响应只有一位，0表示应答，1表示不应答（ACK）
uint8_t I2C_ModeReceiverACK(void)
{
	//主机释放数据线,给从机操作
	I2C_ModeWriteSDA(1);
	
	//从机放ACK，不需要操作
		
	//SCL拉高
	I2C_ModeWriteSCL(1);
	
	//主机读应答位
	uint8_t data = I2C_ModeReadSDA();
		
	//SCL拉低
	I2C_ModeWriteSCL(0);
	
	return data;
}

//主机接收从机一个字节数据的消息
uint8_t I2C_ModeReceiveData(void)
{
	//主机释放数据线,给从机操作
	I2C_ModeWriteSDA(1);
	
	uint8_t data = 0x00;
	for(uint8_t i = 0; i < 8; i++)
	{
		//SCL拉低，SCL默认是低,不需要操作
		
		//从机放一位数据，从机去放，不需要操作
		
		//SCL拉高
		I2C_ModeWriteSCL(1);
	
		//主机读数据,如果读到了1，才需要去将读到的数据放到data中
		if(I2C_ModeReadSDA() == 1)
		{
			data |= (0x80>>i);
		}
		
		//SCL拉低
		I2C_ModeWriteSCL(0);
	}
	return data;
}

