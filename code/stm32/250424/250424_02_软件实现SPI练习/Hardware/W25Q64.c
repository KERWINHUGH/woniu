#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
#include "SPI_Model.h"

void W25Q64_Init(void)
{
	SPI_ModelInit();
}
//写使能
void WriteEnable(void)
{
	SPI_ModelStart();
	
	//写使能指令
	SPI_ModelSendData(Write_Enable);
	
	SPI_ModelStop();
}
//读状态寄存器，等待忙标志位
//错误点2：函数内部等待忙标志位为0
//void ReadStatusRegister(void)
uint8_t ReadStatusRegister(void)
{
	SPI_ModelStart();
	
	//写使能指令
	SPI_ModelSendData(Read_Status_Register);
	
	//得到寄存器状态
	//错误点2：判断忙标志位是否为1，在循环中等待忙标志位为0
	uint8_t data = SPI_ModelSendData(0x00);
//	while((SPI_ModelSendData(0x00) & 0x01) == 0x01);
	
	SPI_ModelStop();
	
	return data;
}
//扇区擦除
void SectorErase(uint32_t address)
{
	//先开启写使能
	WriteEnable();
	
	SPI_ModelStart();
	
	//错误点3：擦除操作需要先发送擦除扇区的指令，然后再发送地址
	SPI_ModelSendData(Sector_Erase);
	
	//发送地址
	SPI_ModelSendData(address>>16);
	SPI_ModelSendData(address>>8);
	SPI_ModelSendData(address);
	
	SPI_ModelStop();
	
	//错误点4：等待忙状态直接调用函数即可
	//等待忙状态清零
	while(ReadStatusRegister());
//	ReadStatusRegister();
}
//按页写入一个字节数据
void PageProgram(uint32_t address,uint8_t data)
{
		//先开启写使能
	WriteEnable();
	
	SPI_ModelStart();
	
	//错误点5：写操作需要先发送写的指令，然后再发送地址
	SPI_ModelSendData(Page_Program);
	
	//发送地址
	SPI_ModelSendData(address>>16);
	SPI_ModelSendData(address>>8);
	SPI_ModelSendData(address);
	
	SPI_ModelSendData(data);
	
	SPI_ModelStop();
	
	//错误点6：等待忙状态直接调用函数即可
	//等待忙状态清零
	while(ReadStatusRegister());
//	ReadStatusRegister();
}
//按页读一个字节数据
uint8_t ReadData(uint32_t address)
{
	SPI_ModelStart();
	
	//错误点7：读操作需要先发送读的指令，然后再发送地址
	SPI_ModelSendData(Read_Data);
	
	//发送地址
	SPI_ModelSendData(address>>16);
	SPI_ModelSendData(address>>8);
	SPI_ModelSendData(address);
	
	uint8_t data = SPI_ModelSendData(0x00);
	
	SPI_ModelStop();
	
	return data;
}
