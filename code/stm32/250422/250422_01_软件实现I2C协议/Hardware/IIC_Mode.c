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
	
	//��ʼ��Ϊ�ߵ�ƽ���ⲿ������������3.3V����Ϊ�ߵ�ƽ����©ģʽ��������ߵ�ƽ��
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}
//SCLд����
void I2C_ModeWriteSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)data);
	Delay_us(5);
}
//SDAд����
void I2C_ModeWriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)data);
	Delay_us(5);
}
//SDA������
uint8_t I2C_ModeReadSDA(void)
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(5);
	return data;
}
//�������ƿ�ʼ�ź�
void I2C_ModeStart(void)
{
	//��ʼ�������������߶�����
	I2C_ModeWriteSDA(1);//SDA�����ߣ��ͽ����ź�������
	I2C_ModeWriteSCL(1);
	//���Ϳ�ʼ�ź�
	I2C_ModeWriteSDA(0);
	I2C_ModeWriteSCL(0);
}
//�������ͽ����ź�
void I2C_ModeStop(void)
{
	//SCLĬ��ǰ��Ĳ������Ե͵�ƽ��������߲��ø�SCLǰ������
	//ֻ��SDA�ĳ�ʼ����
	I2C_ModeWriteSDA(0);
	
	I2C_ModeWriteSCL(1);
	I2C_ModeWriteSDA(1);//SDAһ��Ҫ��һ��SCLΪ�ߵ�����£�SDAҪ��0��1�Ĺ���
}

//�������ӻ�����һλ��Ӧ��ACK��
void I2C_ModeSendACK(uint8_t ack)
{
	I2C_ModeWriteSDA(ack);
	//SCL����
	I2C_ModeWriteSCL(1);
	//�ӻ�������
	
	//SCL����
	I2C_ModeWriteSCL(0);
}

//��������һ���ֽ����ݵ���Ϣ
void I2C_ModeSendData(uint8_t data)
{
	for(uint8_t i = 0; i < 8; i++)
	{
	//SCL�͵�ƽʱ  ����������
	I2C_ModeWriteSDA(data & (0x80>>i));
	//SCL����
	I2C_ModeWriteSCL(1);
	//�ӻ�������
	
	//SCL����
	I2C_ModeWriteSCL(0);

	}
}

//������Ӧֻ��һλ��0��ʾӦ��1��ʾ��Ӧ��ACK��
uint8_t I2C_ModeReceiverACK(void)
{
	//�����ͷ�������,���ӻ�����
	I2C_ModeWriteSDA(1);
	
	//�ӻ���ACK������Ҫ����
		
	//SCL����
	I2C_ModeWriteSCL(1);
	
	//������Ӧ��λ
	uint8_t data = I2C_ModeReadSDA();
		
	//SCL����
	I2C_ModeWriteSCL(0);
	
	return data;
}

//�������մӻ�һ���ֽ����ݵ���Ϣ
uint8_t I2C_ModeReceiveData(void)
{
	//�����ͷ�������,���ӻ�����
	I2C_ModeWriteSDA(1);
	
	uint8_t data = 0x00;
	for(uint8_t i = 0; i < 8; i++)
	{
		//SCL���ͣ�SCLĬ���ǵ�,����Ҫ����
		
		//�ӻ���һλ���ݣ��ӻ�ȥ�ţ�����Ҫ����
		
		//SCL����
		I2C_ModeWriteSCL(1);
	
		//����������,���������1������Ҫȥ�����������ݷŵ�data��
		if(I2C_ModeReadSDA() == 1)
		{
			data |= (0x80>>i);
		}
		
		//SCL����
		I2C_ModeWriteSCL(0);
	}
	return data;
}

