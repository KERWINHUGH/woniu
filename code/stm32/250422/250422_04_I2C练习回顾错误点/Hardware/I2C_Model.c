#include "stm32f10x.h"                  // Device header
#include "I2C_Model.h"
#include "Delay.h"

void I2C_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

void I2C_ModelWriteSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)data);
	Delay_us(5);
}

void I2C_ModelWriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)data);  
	Delay_us(5);
}

uint8_t I2C_ModelReadSDA(void)
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_ms(5);
	return data;
}

void I2C_ModelStart(void)
{
	I2C_ModelWriteSDA(1);
	I2C_ModelWriteSCL(1);
	
	I2C_ModelWriteSDA(0);
	I2C_ModelWriteSCL(0);
}

void I2C_ModelStop(void)
{
	I2C_ModelWriteSDA(0);
	
	I2C_ModelWriteSCL(1);
	I2C_ModelWriteSDA(1);
}

void I2C_ModelSendAck(uint8_t ack)
{
	//SCL����
	
	//������
	I2C_ModelWriteSDA(ack);
	
	//SCL���ߣ��ôӻ�ȥ��
	I2C_ModelWriteSCL(1);
	
	//SCL����
	I2C_ModelWriteSCL(0);
}

void I2C_ModelSendData(uint8_t data)
{
	for(uint8_t i = 0; i<8 ;i++)
	{
		//SCL����
	
		//������
		I2C_ModelWriteSDA(data & (0x80>>i));
		
		//SCL���ߣ��ôӻ�ȥ��
		I2C_ModelWriteSCL(1);
		
		//SCL����
		I2C_ModelWriteSCL(0);
	}
}

uint8_t I2C_ModelReceiveAck(void)
{
	//��������SDA
	I2C_ModelWriteSDA(1);
	
	//SCLĬ������
	
	//�ӻ�������
	
	//��������SCL
	I2C_ModelWriteSCL(1);
	
	//������ȡ����
	uint8_t ack = I2C_ModelReadSDA();
	
	//��������SCL
	I2C_ModelWriteSCL(0);
	
	return ack;
}

uint8_t I2C_ModelReceiveData(void)
{
	//��������SDA
	I2C_ModelWriteSDA(1);
	
	uint8_t data = 0x00;
	for(uint8_t i = 0; i<8 ;i++)
	{
			//SCLĬ������
	
		//�ӻ�������
		
		//��������SCL
		I2C_ModelWriteSCL(1);
		
		//������ȡ����
		if(I2C_ModelReadSDA())
		{
			data |= (0x80>>i);
		}
		
		//��������SCL
		I2C_ModelWriteSCL(0);
	
	}
	return data;
}
