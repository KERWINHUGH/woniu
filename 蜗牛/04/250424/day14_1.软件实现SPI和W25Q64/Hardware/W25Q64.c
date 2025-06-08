#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
//��ʼ��
void W25Q64_Init(void)
{
	SPI_ModelInit();
}

//дʹ��
void WriteEnable(void)
{
	//����
	SPI_ModelStart();
	
	//��ָ��
	SPI_ModelSwapData(Write_Enable);
	
	//����
	SPI_ModelStop();
}

//�ȴ�æ�ķ�����Ϊд��Ͳ��������
void waitBusy(void)
{
	//����
	SPI_ModelStart();
	
	//��ָ��
	SPI_ModelSwapData(Read_Status_Register1);
	//�����ĵ�11.1.1 �����״̬�Ĵ������λ��1����ʾæ��0�ͱ�ʾ��æ
	while((SPI_ModelSwapData(0x00) & 0x01) == 0x01);

	//����
	SPI_ModelStop();
}

//����(�Ѳ�����һ�����ݶ����1)
void SectorErase(uint32_t address)
{
	WriteEnable();
	
	//����
	SPI_ModelStart();
	
	//����ָ��
	SPI_ModelSwapData(Sector_Erase);
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	
	//����
	SPI_ModelStop();
	waitBusy();//�ȴ��������
}

//д��һ���ֽ�
void PageProgram(uint32_t address,uint8_t data)
{
	WriteEnable();
	//����
	SPI_ModelStart();
	
	//��д���ָ��
	SPI_ModelSwapData(Page_Program);
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	SPI_ModelSwapData(data);
	
	//����
	SPI_ModelStop();
	waitBusy();//�ȴ�д�����
}

//��ȡ����
uint8_t ReadData(uint32_t address)
{
	//����
	SPI_ModelStart();
	
	//��д���ָ��
	SPI_ModelSwapData(Read_Data);
	SPI_ModelSwapData(address>>16);
	SPI_ModelSwapData(address>>8);
	SPI_ModelSwapData(address);
	uint8_t data = SPI_ModelSwapData(0x00);
	
	//����
	SPI_ModelStop();
	return data;
}









