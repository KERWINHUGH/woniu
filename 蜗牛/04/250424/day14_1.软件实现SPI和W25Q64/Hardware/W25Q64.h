#ifndef __W25Q64_H
#define __W25Q64_H
#include "SPI_Model.h"

#define Write_Enable 0x06     //дʹ��
#define Read_Status_Register1 0x05  //���λ��æ��������Ĵ���֪��оƬæ��æ
#define Page_Program 0x02  //д��
#define Sector_Erase 0x20  //����
#define Read_Data 0x03  //������

void W25Q64_Init(void);

//����(�Ѳ�����һ�����ݶ����1)
void SectorErase(uint32_t address);
//д��һ���ֽ�
void PageProgram(uint32_t address,uint8_t data);
//��ȡ����
uint8_t ReadData(uint32_t address);

#endif

