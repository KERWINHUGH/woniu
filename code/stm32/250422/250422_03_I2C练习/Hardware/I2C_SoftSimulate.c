#include "stm32f10x.h"                  // Device header
#include "I2C_SoftSimulate.h"
#include "Delay.h"

//��ʼ��IIC����-----		-----PB10:SCL		PB11:SDA
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
	//ģ���ʼ״̬
	IIC_WriteSDA(1);
	IIC_SetSCL(1);
	
	//���Ϳ�ʼ�ź�
	IIC_WriteSDA(0);
	IIC_SetSCL(0);
}

void IIC_Stop(void)
{
	//ģ�������ʼ״̬
	IIC_WriteSDA(0);
	
	//���ͽ����ź�
	IIC_SetSCL(1);
	IIC_WriteSDA(1);
}

//��������һ��ACK
void IIC_SendAck(uint8_t ack)
{
	//��������SCL
	
	//������ACK
	IIC_WriteSDA(ack);
	
	//�����1��������������֮����Ҫ����SCL���ôӻ�ȥ������
	//��������SCL
	IIC_SetSCL(1);
	
	
	//��������SCL
	IIC_SetSCL(0);
	
}

//��������һ���ֽ�
void IIC_SendData(uint8_t data)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		//��������SCL��Ĭ������
		
		//����������
		IIC_WriteSDA(data & (0x80 >> i));
		
		//�����1��������������֮����Ҫ����SCL���ôӻ�ȥ������
		//��������SCL
		IIC_SetSCL(1);
		
		//��������SCL
		IIC_SetSCL(0);
	}
}
//��������һ��ACK
uint8_t IIC_ReceiveAck(void)
{
	//�������ͷ�SDA
	IIC_WriteSDA(1);
	
	//�ӻ�����ACK
	
	//�ӻ��Զ�����SCL
	
	//�����2���ӻ��������ݺ�����Ӧ������SCLȥ��
	//��������SCL
	IIC_SetSCL(1);
	
	//��������ACK
	uint8_t ack = IIC_ReadSDA();
	
	//�����3�������������ݺ���Ҫ��SCL����
	//��������SCL
	IIC_SetSCL(0);
	
	return ack;
}
//��������һ���ֽ�
uint8_t IIC_ReceiveData(void)
{
	//�������ͷ�SDA
	IIC_WriteSDA(1);
	
	uint8_t data = 0x00;
	for(uint8_t i = 0; i < 8; i++)
	{
		//����ʱ����
		
			
		//�����4�������ͷ�SDAӦ��������������SCL֮ǰ����ѭ���ⲿ��ֻ���ͷ�һ��
//		//�������ͷ�SDA
//		IIC_WriteSDA(1);
		
		//�ӻ�������
			
		//�ӻ��Զ�����SCL
		
		//��������ʱ����
		IIC_SetSCL(1);
		
		//������ȡ����
		if(IIC_ReadSDA())
		{
			data |= (0x80>>i);
		}
		
		//��������ʱ����
		IIC_SetSCL(0);
		
	}
	return data;
}
