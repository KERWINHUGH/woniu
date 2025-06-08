#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
#include "SPI_Model.h"


void W25Q64_Init(void)
{
	SPI_ModelInit();
}

void W25Q64_WriteEnable(void)
{
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Write_Enable);
	
	SPI_ModelStop();
}

void W25Q64_WaitBusy(void)
{
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Read_Status_Register);
	
	//等待获得状态位为0
	while((SPI_ModelSwapData(0x00) & 0x01)==0x01);
	
	SPI_ModelStop();
}

void W25Q64_SectorErase(uint32_t address)
{
	//先写使能
	W25Q64_WriteEnable();
	
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Sector_Erase);
	
	//发送地址
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	
	SPI_ModelStop();
	
	//错误点1：等待擦除完成，忙状态位为0
	W25Q64_WaitBusy();
}

void W25Q64_PageProgram(uint32_t address,uint8_t data)
{
	//先写使能
	W25Q64_WriteEnable();
	
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Page_Program);
	
	//发送地址
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	
	//发送数据
	SPI_ModelSwapData(data);
	
	SPI_ModelStop();
	
	//等待忙状态位为0
	W25Q64_WaitBusy();
}

void W25Q64_WiteByteArr(uint32_t address,uint8_t *arr,uint16_t len)
{
	//先写使能
	W25Q64_WriteEnable();
	
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Page_Program);
	
	//发送地址
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	
	//发送数据
	for(uint16_t i = 0;i<len;i++)
	SPI_ModelSwapData(arr[i]);
	
	SPI_ModelStop();
	
	//等待忙状态位为0
	W25Q64_WaitBusy();
}

uint8_t W25Q64_ReadData(uint32_t address)
{
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Read_Data);
	
	//发送地址
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	
	//接收数据
	uint8_t data = SPI_ModelSwapData(0x00);
	
	SPI_ModelStop();
	
	return data;
}

void W25Q64_ReadBtyeArr(uint32_t address,uint8_t *arr,uint16_t len)
{
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Read_Data);
	
	//发送地址
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	
	//接收数据
	for(uint16_t i = 0;i<len;i++)
	arr[i] = SPI_ModelSwapData(0x00);
	
	SPI_ModelStop();
	
}