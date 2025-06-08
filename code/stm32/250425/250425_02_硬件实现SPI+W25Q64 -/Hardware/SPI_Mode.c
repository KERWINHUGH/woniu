#include "stm32f10x.h"                  // Device header
#include "SPI_Model.h"

void SPI_Model_WriteSS(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)data);
}

void SPI_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//SCK和MOSI由硬件控制，所以使用复用推挽
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 ;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	SPI_InitTypeDef SPI_InitStruct;

	
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;//极性
	SPI_InitStruct.SPI_CPHA =SPI_CPHA_1Edge ;//相位
	SPI_InitStruct.SPI_CRCPolynomial = 0x00;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;//不要CRC循环校验
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//两线全双工
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//软件实现片选线
	
	SPI_Init(SPI1,&SPI_InitStruct);
	
	SPI_Cmd(SPI1,ENABLE);
	
	//拉高SS
	SPI_Model_WriteSS(1);
	
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
	//发送数据
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,data);
	
	//接收数据
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
	
}
