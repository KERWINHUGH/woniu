#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
//初始化
void W25Q64_Init(void)
{
	SPI_ModelInit();
}

//写使能
void WriteEnable(void)
{
	//启动
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Write_Enable);
	
	//结束
	SPI_ModelStop();
}

//等待忙的方法，为写入和擦除服务的
void waitBusy(void)
{
	//启动
	SPI_ModelStart();
	
	//发指令
	SPI_ModelSwapData(Read_Status_Register1);
	//按照文档11.1.1 ，如果状态寄存器最低位是1，表示忙，0就表示不忙
	while((SPI_ModelSwapData(0x00) & 0x01) == 0x01);

	//结束
	SPI_ModelStop();
}

//擦除(把擦出这一块数据都变成1)
void SectorErase(uint32_t address)
{
	WriteEnable();
	
	//启动
	SPI_ModelStart();
	
	//擦除指令
	SPI_ModelSwapData(Sector_Erase);
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	
	//结束
	SPI_ModelStop();
	waitBusy();//等待擦除完成
}

//写入一个字节
void PageProgram(uint32_t address,uint8_t data)
{
	WriteEnable();
	//启动
	SPI_ModelStart();
	
	//发写入的指令
	SPI_ModelSwapData(Page_Program);
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	SPI_ModelSwapData(data);
	
	//结束
	SPI_ModelStop();
	waitBusy();//等待写入完成
}

//读取数据
uint8_t ReadData(uint32_t address)
{
	//启动
	SPI_ModelStart();
	
	//发写入的指令
	SPI_ModelSwapData(Read_Data);
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	uint8_t data = SPI_ModelSwapData(0x00);
	
	//结束
	SPI_ModelStop();
	return data;
}









