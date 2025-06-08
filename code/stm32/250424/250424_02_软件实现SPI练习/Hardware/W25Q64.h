#ifndef _W25Q64_H
#define _W25Q64_H

#define Write_Enable					0x06
#define Read_Status_Register	0x05
#define Page_Program					0x02
#define Sector_Erase					0x20
#define Read_Data							0x03
#define JEDEC_ID							0x9F		//产品信息


//初始化引脚
void W25Q64_Init(void);
//写使能

//扇区擦除
void SectorErase(uint32_t address);
//按页写入数据
void PageProgram(uint32_t address,uint8_t data);
//按页读数据
uint8_t ReadData(uint32_t address);
#endif
