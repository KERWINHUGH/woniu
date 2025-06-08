#include "stm32f10x.h"                  // Device header
/**
1.SPI1-APB2 SPI2-APB1
2.ʹ��SPI1��PA4-SS[CS]  PA5-SCK[CLK] PA6=MISO[DO]  PA7-MOSI[DI]
3.GPIO�Ķ�д������4���ߣ�ģ���SPIͨ��Э��
4.ʹ��ģʽ0 ����ʱ��SCK=0����һ�����ض����ݣ�SS���͵�ʱ��ͷ�����
*/
//дƬѡ
void SPI_WriteSS(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)data);
}

//дʱ���ź�
void SPI_WriteSCK(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)data);
}

//��������
void SPI_WriteMOSI(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)data);
}

//��������
uint8_t SPI_ReadMISO()
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

void SPI_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�Լ����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����ģʽ���ٷ����鸡�ջ�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//SS��ʼ��Ϊ1  CLK��ʼ��Ϊ0
	SPI_WriteSS(1);
	SPI_WriteSCK(0);
}

//����-SS����
void SPI_ModelStart(void)
{
	SPI_WriteSS(0);
}

//ֹͣ-SS����
void SPI_ModelStop(void)
{
	SPI_WriteSS(1);
}

//��������-ģʽ0��SS���͵�ʱ��ͷ������ݣ�SCL�ĵ�һ�����أ���������  �ڶ������أ��½�����
//MSB ��λ���У��շ�������ˣ�
uint8_t SPI_ModelSwapData(uint8_t sendData)//1010 1010 
{ 
	uint8_t receiveData = 0x00;
	//��ʱ���ߵĿ����£���һ�����ݣ���һ������
	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		//MOSI������
		SPI_WriteMOSI(sendData & (0x80>>i));
		
		//����SCK
		SPI_WriteSCK(1);
		
		//������MISO
		if(SPI_ReadMISO())
		{
			receiveData |= (0x80>>i);
		}
		
		//����SCK
		SPI_WriteSCK(0);
	}
	return receiveData;
}

//uint8_t SPI_ModelSwapData(uint8_t sendData)//1010 1010 
//{ 
//	//��ʱ���ߵĿ����£���һ�����ݣ���һ������
//	for(uint8_t i = 0 ; i < 8 ; i++)
//	{
//		//MOSI������
//		SPI_WriteMOSI(sendData & 0x80);
//		sendData <<= 1;
//		
//		//����SCK
//		SPI_WriteSCK(1);
//		
//		//������MISO
//		if(SPI_ReadMISO())
//		{
//			sendData |= 0x01;
//		}
//		
//		//����SCK
//		SPI_WriteSCK(0);
//	}
//	return sendData;
//}




