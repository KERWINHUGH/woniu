#include "stm32f10x.h"                  // Device header
#include "SPI_Model.h"


/*****************************************
**	PA4----SS
**	PA5----SCK
**	PA6----MISO
**	PA7----MOSI
**	从机:W25Qxx  VSS CS--(SS) DO--(MISO) GND CLK--(SCK) DI--(MOSI)
**	使用模式0	空闲时，SCK=0；第一个边沿读数据，SS拉低时马上开始放数据
*/

void SPI_WriteSS(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)data);
}

void SPI_WriteSCK(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)data);
}

void SPI_WriteMOSI(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)data);
}

uint8_t SPI_ReadMISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}




//初始化
void SPI_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6  ;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//初始化SS为高,默认片选线为1
	SPI_WriteSS(1);
	
	//初始化SCK为0------使用模式0,SCK默认为0
	SPI_WriteSCK(0);
}

//启动
void SPI_ModelStart(void)
{
	SPI_WriteSS(0);
}

//停止
void SPI_ModelStop(void)
{
	SPI_WriteSS(1);
}

//交换数据----模式0：SS拉低的时候开始放数据，第一个边沿为上升沿，开始读；第二个边沿是下降沿，开始放数据
//MSB:高位先行，先发高位，接收数据放到低位
uint8_t SPI_ModelSwap(uint8_t data)
{

	for(uint8_t i = 0; i < 8; i++)
	{
		//MOSI放数据，data & 1000 0000
		SPI_WriteMOSI(data & (0x80));
		
		//左移一位并赋值
		data <<= 1;
		
		//拉高SCK
		SPI_WriteSCK(1);
		
		//读数据MISO，如果读到是1，将最低位写为1
		if(SPI_ReadMISO())
		data |= 0x01;
		
		//拉低SCK
		SPI_WriteSCK(0);
	}

	return data;
}

//uint8_t SPI_ModelSwap(uint8_t data)
//{
//	uint8_t receiveData = 0x00;
//	
//	for(uint8_t i = 0; i < 8; i++)
//	{
//		//MOSI放数据
//		SPI_WriteMOSI(data & (0x80>>i));
//		
//		//拉高SCK
//		SPI_WriteSCK(1);
//		
//		//读数据MISO
//		if(SPI_ReadMISO())
//		receiveData |= (0x80>>i);
//		
//		//拉低SCK
//			SPI_WriteSCK(0);
//	}
//	
//	
//	return receiveData;
//}

