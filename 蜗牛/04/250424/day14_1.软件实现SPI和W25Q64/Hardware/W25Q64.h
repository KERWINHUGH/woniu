#ifndef __W25Q64_H
#define __W25Q64_H
#include "SPI_Model.h"

#define Write_Enable 0x06     //写使能
#define Read_Status_Register1 0x05  //最低位是忙，读这个寄存器知道芯片忙不忙
#define Page_Program 0x02  //写入
#define Sector_Erase 0x20  //擦除
#define Read_Data 0x03  //读数据

void W25Q64_Init(void);

//擦除(把擦出这一块数据都变成1)
void SectorErase(uint32_t address);
//写入一个字节
void PageProgram(uint32_t address,uint8_t data);
//读取数据
uint8_t ReadData(uint32_t address);

#endif

