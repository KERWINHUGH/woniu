#include "stm32f10x.h"                  // Device header
#include "SPI_Model.h"

//初始化引脚
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
	
	//初始化，片选线拉高
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	//初始化，时钟线拉低----模式0
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
	//片选线拉低
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void SPI_ModelStop(void)
{
	//片选线拉高
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}



uint8_t SPI_ModelSendData(uint8_t data)
{
	
//	SPI_ModelStart();
	
	for(uint8_t i = 0; i<8; i++)
	{
		//模式0开始之后就要放数据
		//按照MSB高位先行发送第一位
		SPI_ModelWriteData(data & 0x80);
		
		//发送第一位后，左移一位，后续继续发送最高位，即原本要发数据的第七位
		data <<= 1;
		
		//拉高SCK给从机去读
		SPI_ModelWriteSCK(1);
		
		//等到有数据再读,且读到当前位为1时，再存放到数据位最低位
		if(SPI_ModelReadData())
		data |= 0x01;
		
		//错误点1：读到数据后应该将SCK拉低
		SPI_ModelWriteSCK(0);
	
	}
//	SPI_ModelStop();
	
	return data;
}
