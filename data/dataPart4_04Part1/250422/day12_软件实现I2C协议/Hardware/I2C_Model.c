#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//������������Ǹ�STM32����д�ģ�MPU6050�����Ѿ���I2CЭ��ĳ����ˡ�
void I2C_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//��ʼ�����Ǹߵ�ƽ
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

//SCLд����
void I2C_ModelWriteSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10,data);
	Delay_us(5);
}
//SDAд
void I2C_ModelWriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11,data);
	Delay_us(5);
}

//SDA��
uint8_t I2C_ModelReadSDA(void)
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(5);
	return data;
}

void I2C_ModelStart(void)//������ʼ
{
	I2C_ModelWriteSDA(1);//SDA�߷�ǰ��
	I2C_ModelWriteSCL(1);
	
	I2C_ModelWriteSDA(0);
	I2C_ModelWriteSCL(0);
}

void I2C_ModelStop(void)//�������ͽ�����Ϣ
{
	//SCLĬ��ǰ��Ĳ��������Ե͵�ƽ����
	I2C_ModelWriteSDA(0);
	
	I2C_ModelWriteSCL(1);
	I2C_ModelWriteSDA(1);//SDAһ��Ҫ��һ��SCLΪ�ߵ�����£�SDAҪ��0��1�Ĺ���
}

void I2C_ModelSendData(uint8_t data)//��������һ�����ݣ��ֽڣ�����λ����   1100 0100
{
	for(uint8_t i = 0 ; i < 8 ; i++)
	{	
		//SCL�͵�ƽ��ʱ������������
		I2C_ModelWriteSDA(data & (0x80>>i)); //1100 0100 & 1000 0000 = 1000 0000
		//SCL����
		I2C_ModelWriteSCL(1);
		//�ӻ�������
		
		//SCL����
		I2C_ModelWriteSCL(0);
	}	
}

void I2C_ModelSendAck(uint8_t ack)//�������ӻ�һ����Ӧ1λ
{
	I2C_ModelWriteSDA(ack);
	//SCL����
	I2C_ModelWriteSCL(1);
	//�ӻ���Ӧ��
	
	//SCL����
	I2C_ModelWriteSCL(0);
}

uint8_t I2C_ModeReceiveData(void)//��������һ������8λ  1010 0100
{
	//�����ͷ������ߣ����ӻ�����
	I2C_ModelWriteSDA(1);
	
	uint8_t data = 0x00;//1000 0000
	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		//�ӻ���bit
		
		//SCL����
		I2C_ModelWriteSCL(1);
		//����������,���������1������Ҫ�ŵ�data��
		if(I2C_ModelReadSDA())
		{
			data |= (0x80>>i);
		}
		
		//SCL����		
		I2C_ModelWriteSCL(0);
	}
	return data;
}

uint8_t I2C_ModelReceiveAck(void)//����������Ӧֻ��1λ��0��ʾӦ��1��ʾ��Ӧ��
{
	//�����ͷ������ߣ����ӻ�����
	I2C_ModelWriteSDA(1);
	
	//�ӻ���ACK
		
	//SCL����
	I2C_ModelWriteSCL(1);
	//������Ӧ��λ
	uint8_t ack  = I2C_ModelReadSDA();

	//SCL����		
	I2C_ModelWriteSCL(0);
	
	return ack;
}















