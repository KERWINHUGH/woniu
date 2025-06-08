#include "stm32f10x.h"                  // Device header
/**
1.SPI1-APB2 SPI2-APB1
2.使用SPI1：PA4-SS[CS]  PA5-SCK[CLK] PA6=MISO[DO]  PA7-MOSI[DI]
3.GPIO的读写来控制4根线，模拟出SPI通信协议
4.使用模式0 空闲时，SCK=0，第一个边沿读数据，SS拉低的时候就放数据
*/
//写片选
void SPI_WriteSS(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)data);
}

//写时钟信号
void SPI_WriteSCK(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)data);
}

//发送数据
void SPI_WriteMOSI(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)data);
}

//接收数据
uint8_t SPI_ReadMISO()
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

void SPI_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//自己输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//输入模式，官方建议浮空或者上拉
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//SS初始化为1  CLK初始化为0
	SPI_WriteSS(1);
	SPI_WriteSCK(0);
}

//启动-SS拉低
void SPI_ModelStart(void)
{
	SPI_WriteSS(0);
}

//停止-SS拉高
void SPI_ModelStop(void)
{
	SPI_WriteSS(1);
}

//交换数据-模式0：SS拉低的时候就放了数据，SCL的第一个边沿（上升）读  第二个边沿（下降）放
//MSB 高位先行（收发都是如此）
uint8_t SPI_ModelSwapData(uint8_t sendData)//1010 1010 
{ 
	uint8_t receiveData = 0x00;
	//在时钟线的控制下，放一个数据，收一个数据
	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		//MOSI放数据
		SPI_WriteMOSI(sendData & (0x80>>i));
		
		//拉高SCK
		SPI_WriteSCK(1);
		
		//读数据MISO
		if(SPI_ReadMISO())
		{
			receiveData |= (0x80>>i);
		}
		
		//拉低SCK
		SPI_WriteSCK(0);
	}
	return receiveData;
}

//uint8_t SPI_ModelSwapData(uint8_t sendData)//1010 1010 
//{ 
//	//在时钟线的控制下，放一个数据，收一个数据
//	for(uint8_t i = 0 ; i < 8 ; i++)
//	{
//		//MOSI放数据
//		SPI_WriteMOSI(sendData & 0x80);
//		sendData <<= 1;
//		
//		//拉高SCK
//		SPI_WriteSCK(1);
//		
//		//读数据MISO
//		if(SPI_ReadMISO())
//		{
//			sendData |= 0x01;
//		}
//		
//		//拉低SCK
//		SPI_WriteSCK(0);
//	}
//	return sendData;
//}




