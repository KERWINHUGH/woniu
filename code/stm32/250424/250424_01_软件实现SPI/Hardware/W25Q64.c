#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
#include "SPI_Model.h"

void W25Q64_Init(void)
{
	SPI_ModelInit();
}
//写使能
void W25Q64_WriteEnable(void)
{

	SPI_ModelStart();
	
	SPI_ModelSwap(WRITE_EABLE);//发送指令
	
	SPI_ModelStop();
}
//等待状态寄存器的忙标志位，为写入和擦除服务
void W25Q64_WaitBusy(void)
{
	SPI_ModelStart();
	
	SPI_ModelSwap(READ_STATUS_REGISTER);//发送指令
	
	//参考文档11.1.1，如果寄存器最低位是1，表示忙，0为不忙
	while((SPI_ModelSwap(0x00) & 0x01) == 0x01);
	
	SPI_ModelStop();
}
//扇区擦除
void W25Q64_SectorErase(uint32_t address)
{
	//擦除之前先写使能
	W25Q64_WriteEnable();
	
	SPI_ModelStart();
	
	SPI_ModelSwap(SECTOR_ERASE);//发送指令
	
	//发送地址
	SPI_ModelSwap(address >> 16);//发送地址
	SPI_ModelSwap(address >>8);//发送送地址
	SPI_ModelSwap(address);//发送送地址
	
	SPI_ModelStop();
	//等待擦除完成
	W25Q64_WaitBusy();
}
//写数据
void W25Q64_PageProgram(uint32_t address,uint8_t data)
{
	//写入之前先写使能
	W25Q64_WriteEnable();
	
	SPI_ModelStart();

	SPI_ModelSwap(PAGE_PROGRAM);//发送指令
	
	//发送地址
	SPI_ModelSwap(address >> 16);//发送送地址
	SPI_ModelSwap(address >>8);//发送送地址
	SPI_ModelSwap(address);//发送送地址
	
	SPI_ModelSwap(data);//发送指令	
	
	SPI_ModelStop();
	//等待写入完成
	W25Q64_WaitBusy();	
	
}
//读数据
uint8_t W25Q64_ReadData(uint32_t address)
{	
	SPI_ModelStart();

	SPI_ModelSwap(READ_DATA);//发送指令
	
	//发送地址
	SPI_ModelSwap(address >> 16);//发送送地址
	SPI_ModelSwap(address >>8);//发送送地址
	SPI_ModelSwap(address);//发送送地址
	
	uint8_t data = SPI_ModelSwap(0x00);//发送指令	
	
	SPI_ModelStop();
	
	return data;
}

//写数组
void W25Q64_PageProgramArr(uint32_t address,uint8_t *arr,uint16_t len)
{
	//写入之前先写使能
	W25Q64_WriteEnable();
	
	SPI_ModelStart();

	SPI_ModelSwap(PAGE_PROGRAM);//发送指令
	
	//发送地址
	SPI_ModelSwap(address >> 16);//发送送地址
	SPI_ModelSwap(address >>8);//发送送地址
	SPI_ModelSwap(address);//发送送地址
	
	for(uint16_t i = 0; i<len; i++)
	SPI_ModelSwap(arr[i]);//交换数据
	
	SPI_ModelStop();
	//等待写入完成
	W25Q64_WaitBusy();	
	
}
//读数据
uint8_t * W25Q64_ReadArr(uint32_t address,uint8_t *arr,uint16_t len)
{	
	SPI_ModelStart();

	SPI_ModelSwap(READ_DATA);//发送指令
	
	//发送地址
	SPI_ModelSwap(address >> 16);//发送送地址
	SPI_ModelSwap(address >>8);//发送送地址
	SPI_ModelSwap(address);//发送送地址
	
	for(uint16_t i = 0; i<len; i++)
	arr[i] = SPI_ModelSwap(0x00);//发送指令	
	
	SPI_ModelStop();
	
	return arr;
}
