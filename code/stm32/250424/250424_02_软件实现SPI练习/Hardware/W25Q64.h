#ifndef _W25Q64_H
#define _W25Q64_H

#define Write_Enable					0x06
#define Read_Status_Register	0x05
#define Page_Program					0x02
#define Sector_Erase					0x20
#define Read_Data							0x03
#define JEDEC_ID							0x9F		//��Ʒ��Ϣ


//��ʼ������
void W25Q64_Init(void);
//дʹ��

//��������
void SectorErase(uint32_t address);
//��ҳд������
void PageProgram(uint32_t address,uint8_t data);
//��ҳ������
uint8_t ReadData(uint32_t address);
#endif
