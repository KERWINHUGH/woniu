#include "stm32f10x.h"                  // Device header
#include "I2C_SoftSimulate.h"
#include "Delay.h"

//初始化IIC引脚-----		-----PB10:SCL		PB11:SDA
void IIC_ModeInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

void IIC_SetSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)data);
	Delay_us(5);
}

void IIC_WriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)data);
	Delay_us(5);
}

uint8_t IIC_ReadSDA(void)
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_ms(5);
	return data;
}

void IIC_Strat(void)
{
	//模拟初始状态
	IIC_WriteSDA(1);
	IIC_SetSCL(1);
	
	//发送开始信号
	IIC_WriteSDA(0);
	IIC_SetSCL(0);
}

void IIC_Stop(void)
{
	//模拟结束初始状态
	IIC_WriteSDA(0);
	
	//发送结束信号
	IIC_SetSCL(1);
	IIC_WriteSDA(1);
}

//主机发送一个ACK
void IIC_SendAck(uint8_t ack)
{
	//主机拉低SCL
	
	//主机放ACK
	IIC_WriteSDA(ack);
	
	//错误点1：主机放完数据之后，需要拉高SCL，让从机去读数据
	//主机拉高SCL
	IIC_SetSCL(1);
	
	
	//主机拉低SCL
	IIC_SetSCL(0);
	
}

//主机发送一个字节
void IIC_SendData(uint8_t data)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		//主机拉低SCL，默认拉低
		
		//主机放数据
		IIC_WriteSDA(data & (0x80 >> i));
		
		//错误点1：主机放完数据之后，需要拉高SCL，让从机去读数据
		//主机拉高SCL
		IIC_SetSCL(1);
		
		//主机拉低SCL
		IIC_SetSCL(0);
	}
}
//主机接收一个ACK
uint8_t IIC_ReceiveAck(void)
{
	//主机先释放SDA
	IIC_WriteSDA(1);
	
	//从机发送ACK
	
	//从机自动拉低SCL
	
	//错误点2：从机放完数据后，主机应当拉高SCL去读
	//主机拉高SCL
	IIC_SetSCL(1);
	
	//主机接收ACK
	uint8_t ack = IIC_ReadSDA();
	
	//错误点3：主机放完数据后，需要将SCL拉低
	//主机拉低SCL
	IIC_SetSCL(0);
	
	return ack;
}
//主机接收一个字节
uint8_t IIC_ReceiveData(void)
{
	//主机先释放SDA
	IIC_WriteSDA(1);
	
	uint8_t data = 0x00;
	for(uint8_t i = 0; i < 8; i++)
	{
		//拉低时钟线
		
			
		//错误点4：主机释放SDA应该是主机在拉低SCL之前，在循环外部，只用释放一次
//		//主机先释放SDA
//		IIC_WriteSDA(1);
		
		//从机放数据
			
		//从机自动拉低SCL
		
		//主机拉高时钟线
		IIC_SetSCL(1);
		
		//主机读取数据
		if(IIC_ReadSDA())
		{
			data |= (0x80>>i);
		}
		
		//主机拉低时钟线
		IIC_SetSCL(0);
		
	}
	return data;
}
