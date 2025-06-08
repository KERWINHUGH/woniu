#ifndef _W25Q64_H
#define _W25Q64_H


#define  WRITE_EABLE  					0x06
#define  READ_STATUS_REGISTER  	0x05
#define  PAGE_PROGRAM  					0x02
#define  SECTOR_ERASE 				 	0x20
#define  READ_DATA							0x03
#define  JEDEC_ID								0x9F

void W25Q64_Init(void);

//ÉÈÇø²Á³ý
void W25Q64_SectorErase(uint32_t address);

void W25Q64_PageProgram(uint32_t address,uint8_t data);


uint8_t W25Q64_ReadData(uint32_t address);

void W25Q64_PageProgramArr(uint32_t address,uint8_t *arr,uint16_t len);

uint8_t * W25Q64_ReadArr(uint32_t address,uint8_t *arr,uint16_t len);

#endif
