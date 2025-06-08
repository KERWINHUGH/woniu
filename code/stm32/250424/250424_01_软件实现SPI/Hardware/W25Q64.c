#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
#include "SPI_Model.h"

void W25Q64_Init(void)
{
	SPI_ModelInit();
}
//дʹ��
void W25Q64_WriteEnable(void)
{

	SPI_ModelStart();
	
	SPI_ModelSwap(WRITE_EABLE);//����ָ��
	
	SPI_ModelStop();
}
//�ȴ�״̬�Ĵ�����æ��־λ��Ϊд��Ͳ�������
void W25Q64_WaitBusy(void)
{
	SPI_ModelStart();
	
	SPI_ModelSwap(READ_STATUS_REGISTER);//����ָ��
	
	//�ο��ĵ�11.1.1������Ĵ������λ��1����ʾæ��0Ϊ��æ
	while((SPI_ModelSwap(0x00) & 0x01) == 0x01);
	
	SPI_ModelStop();
}
//��������
void W25Q64_SectorErase(uint32_t address)
{
	//����֮ǰ��дʹ��
	W25Q64_WriteEnable();
	
	SPI_ModelStart();
	
	SPI_ModelSwap(SECTOR_ERASE);//����ָ��
	
	//���͵�ַ
	SPI_ModelSwap(address >> 16);//���͵�ַ
	SPI_ModelSwap(address >>8);//�����͵�ַ
	SPI_ModelSwap(address);//�����͵�ַ
	
	SPI_ModelStop();
	//�ȴ��������
	W25Q64_WaitBusy();
}
//д����
void W25Q64_PageProgram(uint32_t address,uint8_t data)
{
	//д��֮ǰ��дʹ��
	W25Q64_WriteEnable();
	
	SPI_ModelStart();

	SPI_ModelSwap(PAGE_PROGRAM);//����ָ��
	
	//���͵�ַ
	SPI_ModelSwap(address >> 16);//�����͵�ַ
	SPI_ModelSwap(address >>8);//�����͵�ַ
	SPI_ModelSwap(address);//�����͵�ַ
	
	SPI_ModelSwap(data);//����ָ��	
	
	SPI_ModelStop();
	//�ȴ�д�����
	W25Q64_WaitBusy();	
	
}
//������
uint8_t W25Q64_ReadData(uint32_t address)
{	
	SPI_ModelStart();

	SPI_ModelSwap(READ_DATA);//����ָ��
	
	//���͵�ַ
	SPI_ModelSwap(address >> 16);//�����͵�ַ
	SPI_ModelSwap(address >>8);//�����͵�ַ
	SPI_ModelSwap(address);//�����͵�ַ
	
	uint8_t data = SPI_ModelSwap(0x00);//����ָ��	
	
	SPI_ModelStop();
	
	return data;
}

//д����
void W25Q64_PageProgramArr(uint32_t address,uint8_t *arr,uint16_t len)
{
	//д��֮ǰ��дʹ��
	W25Q64_WriteEnable();
	
	SPI_ModelStart();

	SPI_ModelSwap(PAGE_PROGRAM);//����ָ��
	
	//���͵�ַ
	SPI_ModelSwap(address >> 16);//�����͵�ַ
	SPI_ModelSwap(address >>8);//�����͵�ַ
	SPI_ModelSwap(address);//�����͵�ַ
	
	for(uint16_t i = 0; i<len; i++)
	SPI_ModelSwap(arr[i]);//��������
	
	SPI_ModelStop();
	//�ȴ�д�����
	W25Q64_WaitBusy();	
	
}
//������
uint8_t * W25Q64_ReadArr(uint32_t address,uint8_t *arr,uint16_t len)
{	
	SPI_ModelStart();

	SPI_ModelSwap(READ_DATA);//����ָ��
	
	//���͵�ַ
	SPI_ModelSwap(address >> 16);//�����͵�ַ
	SPI_ModelSwap(address >>8);//�����͵�ַ
	SPI_ModelSwap(address);//�����͵�ַ
	
	for(uint16_t i = 0; i<len; i++)
	arr[i] = SPI_ModelSwap(0x00);//����ָ��	
	
	SPI_ModelStop();
	
	return arr;
}
