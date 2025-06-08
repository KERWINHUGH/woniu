#include "stm32f10x.h"                  // Device header
#include "SPI_Model.h"

void SPI_Model_WriteSS(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)data);
}

void SPI_Model_WriteSCK(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)data);
}

void SPI_Model_WriteData(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)data);
}

uint8_t SPI_Model_ReadData(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

void SPI_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//����SS
	SPI_Model_WriteSS(1);
	
	//����SCK----ģʽ0
	SPI_Model_WriteSCK(0);
	
}

void SPI_ModelStart(void)
{
	SPI_Model_WriteSS(0);
}

void SPI_ModelStop(void)
{
	SPI_Model_WriteSS(1);
}

uint8_t SPI_ModelSwapData(uint8_t data)
{
	for(uint8_t i =0;i<8;i++)
	{
		//����SS�ͷ�����
		SPI_Model_WriteData(data & 0x80);
		
		data<<=1;
		
		//����SCK
		SPI_Model_WriteSCK(1);
		
		//��ȡ�ӻ�����
		//������յ�Ϊ1��ŵ����һλ
		if(SPI_Model_ReadData())
		data |= 0x01;
		
		//����SCK
		SPI_Model_WriteSCK(0);
	}
	return data;
}
