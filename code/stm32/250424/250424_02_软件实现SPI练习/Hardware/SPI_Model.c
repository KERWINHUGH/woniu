#include "stm32f10x.h"                  // Device header
#include "SPI_Model.h"

//��ʼ������
void SPI_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//��ʼ����Ƭѡ������
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	//��ʼ����ʱ��������----ģʽ0
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

void SPI_ModelWriteSCK(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)data);
}

void SPI_ModelWriteData(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)data);
}

uint8_t SPI_ModelReadData(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

void SPI_ModelStart(void)
{
	//Ƭѡ������
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void SPI_ModelStop(void)
{
	//Ƭѡ������
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}



uint8_t SPI_ModelSendData(uint8_t data)
{
	
//	SPI_ModelStart();
	
	for(uint8_t i = 0; i<8; i++)
	{
		//ģʽ0��ʼ֮���Ҫ������
		//����MSB��λ���з��͵�һλ
		SPI_ModelWriteData(data & 0x80);
		
		//���͵�һλ������һλ�����������������λ����ԭ��Ҫ�����ݵĵ���λ
		data <<= 1;
		
		//����SCK���ӻ�ȥ��
		SPI_ModelWriteSCK(1);
		
		//�ȵ��������ٶ�,�Ҷ�����ǰλΪ1ʱ���ٴ�ŵ�����λ���λ
		if(SPI_ModelReadData())
		data |= 0x01;
		
		//�����1���������ݺ�Ӧ�ý�SCK����
		SPI_ModelWriteSCK(0);
	
	}
//	SPI_ModelStop();
	
	return data;
}
