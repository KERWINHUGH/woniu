#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
#include "SPI_Model.h"

void W25Q64_Init(void)
{
	SPI_ModelInit();
}
//дʹ��
void WriteEnable(void)
{
	SPI_ModelStart();
	
	//дʹ��ָ��
	SPI_ModelSendData(Write_Enable);
	
	SPI_ModelStop();
}
//��״̬�Ĵ������ȴ�æ��־λ
//�����2�������ڲ��ȴ�æ��־λΪ0
//void ReadStatusRegister(void)
uint8_t ReadStatusRegister(void)
{
	SPI_ModelStart();
	
	//дʹ��ָ��
	SPI_ModelSendData(Read_Status_Register);
	
	//�õ��Ĵ���״̬
	//�����2���ж�æ��־λ�Ƿ�Ϊ1����ѭ���еȴ�æ��־λΪ0
	uint8_t data = SPI_ModelSendData(0x00);
//	while((SPI_ModelSendData(0x00) & 0x01) == 0x01);
	
	SPI_ModelStop();
	
	return data;
}
//��������
void SectorErase(uint32_t address)
{
	//�ȿ���дʹ��
	WriteEnable();
	
	SPI_ModelStart();
	
	//�����3������������Ҫ�ȷ��Ͳ���������ָ�Ȼ���ٷ��͵�ַ
	SPI_ModelSendData(Sector_Erase);
	
	//���͵�ַ
	SPI_ModelSendData(address>>16);
	SPI_ModelSendData(address>>8);
	SPI_ModelSendData(address);
	
	SPI_ModelStop();
	
	//�����4���ȴ�æ״ֱ̬�ӵ��ú�������
	//�ȴ�æ״̬����
	while(ReadStatusRegister());
//	ReadStatusRegister();
}
//��ҳд��һ���ֽ�����
void PageProgram(uint32_t address,uint8_t data)
{
		//�ȿ���дʹ��
	WriteEnable();
	
	SPI_ModelStart();
	
	//�����5��д������Ҫ�ȷ���д��ָ�Ȼ���ٷ��͵�ַ
	SPI_ModelSendData(Page_Program);
	
	//���͵�ַ
	SPI_ModelSendData(address>>16);
	SPI_ModelSendData(address>>8);
	SPI_ModelSendData(address);
	
	SPI_ModelSendData(data);
	
	SPI_ModelStop();
	
	//�����6���ȴ�æ״ֱ̬�ӵ��ú�������
	//�ȴ�æ״̬����
	while(ReadStatusRegister());
//	ReadStatusRegister();
}
//��ҳ��һ���ֽ�����
uint8_t ReadData(uint32_t address)
{
	SPI_ModelStart();
	
	//�����7����������Ҫ�ȷ��Ͷ���ָ�Ȼ���ٷ��͵�ַ
	SPI_ModelSendData(Read_Data);
	
	//���͵�ַ
	SPI_ModelSendData(address>>16);
	SPI_ModelSendData(address>>8);
	SPI_ModelSendData(address);
	
	uint8_t data = SPI_ModelSendData(0x00);
	
	SPI_ModelStop();
	
	return data;
}
