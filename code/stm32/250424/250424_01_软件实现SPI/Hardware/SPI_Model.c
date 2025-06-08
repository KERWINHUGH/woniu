#include "stm32f10x.h"                  // Device header
#include "SPI_Model.h"


/*****************************************
**	PA4----SS
**	PA5----SCK
**	PA6----MISO
**	PA7----MOSI
**	�ӻ�:W25Qxx  VSS CS--(SS) DO--(MISO) GND CLK--(SCK) DI--(MOSI)
**	ʹ��ģʽ0	����ʱ��SCK=0����һ�����ض����ݣ�SS����ʱ���Ͽ�ʼ������
*/

void SPI_WriteSS(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)data);
}

void SPI_WriteSCK(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)data);
}

void SPI_WriteMOSI(uint8_t data)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)data);
}

uint8_t SPI_ReadMISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}




//��ʼ��
void SPI_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6  ;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//��ʼ��SSΪ��,Ĭ��Ƭѡ��Ϊ1
	SPI_WriteSS(1);
	
	//��ʼ��SCKΪ0------ʹ��ģʽ0,SCKĬ��Ϊ0
	SPI_WriteSCK(0);
}

//����
void SPI_ModelStart(void)
{
	SPI_WriteSS(0);
}

//ֹͣ
void SPI_ModelStop(void)
{
	SPI_WriteSS(1);
}

//��������----ģʽ0��SS���͵�ʱ��ʼ�����ݣ���һ������Ϊ�����أ���ʼ�����ڶ����������½��أ���ʼ������
//MSB:��λ���У��ȷ���λ���������ݷŵ���λ
uint8_t SPI_ModelSwap(uint8_t data)
{

	for(uint8_t i = 0; i < 8; i++)
	{
		//MOSI�����ݣ�data & 1000 0000
		SPI_WriteMOSI(data & (0x80));
		
		//����һλ����ֵ
		data <<= 1;
		
		//����SCK
		SPI_WriteSCK(1);
		
		//������MISO�����������1�������λдΪ1
		if(SPI_ReadMISO())
		data |= 0x01;
		
		//����SCK
		SPI_WriteSCK(0);
	}

	return data;
}

//uint8_t SPI_ModelSwap(uint8_t data)
//{
//	uint8_t receiveData = 0x00;
//	
//	for(uint8_t i = 0; i < 8; i++)
//	{
//		//MOSI������
//		SPI_WriteMOSI(data & (0x80>>i));
//		
//		//����SCK
//		SPI_WriteSCK(1);
//		
//		//������MISO
//		if(SPI_ReadMISO())
//		receiveData |= (0x80>>i);
//		
//		//����SCK
//			SPI_WriteSCK(0);
//	}
//	
//	
//	return receiveData;
//}

