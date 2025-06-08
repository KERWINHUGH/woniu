#ifndef _W25Q64_H
#define _W25Q64_H

#define Write_Enable					0x06
#define Read_Status_Register	0x05
#define Page_Program					0x02
#define Sector_Erase					0x20
#define Read_Data							0x03
#define JEDEC_ID							0x9F

void W25Q64_Init(void);

void W25Q64_WriteEnable(void);

void W25Q64_WaitBusy(void);

void W25Q64_SectorErase(uint32_t address);

void W25Q64_PageProgram(uint32_t address,uint8_t data);

uint8_t W25Q64_ReadData(uint32_t address);

void W25Q64_WiteByteArr(uint32_t address,uint8_t *arr,uint16_t len);

void W25Q64_ReadBtyeArr(uint32_t address,uint8_t *arr,uint16_t len);

#endif
