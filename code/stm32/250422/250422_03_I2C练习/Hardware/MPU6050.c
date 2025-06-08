#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "I2C_SoftSimulate.h"

void MPU6050_Init(void)
{
	IIC_ModeInit();
}
//�����1��д��������Ҫ�������
//0xD0���豸��ַ���ô�
//��Ҫ����Ĳ�����Ҫд��ļĴ�����ַ������
void MPU6050_Write(uint8_t regArr,uint8_t data)
{
	IIC_Strat();
	IIC_SendData(0xD0);
	IIC_ReceiveAck();
	
	IIC_SendData(regArr);
	IIC_ReceiveAck();
	
	IIC_SendData(data);
	IIC_ReceiveAck();
	IIC_Stop();
}
//�����2����ȡ������Ҫ�������
//0xD0��0xD1��0xD���豸��ַ��0��1��д��ʽ���������������ô�
//��Ҫ����Ĳ�����Ҫ��ȡ�ļĴ�����ַ
uint8_t MPU6050_Read(uint8_t regArr)
{
	IIC_Strat();
	IIC_SendData(0xD0);
	IIC_ReceiveAck();
	
	IIC_SendData(regArr);
	IIC_ReceiveAck();
	
	IIC_Strat();
	IIC_SendData(0xD1);
	IIC_ReceiveAck();
	
	uint8_t data = IIC_ReceiveData();
	IIC_SendAck(1);
	IIC_Stop();
	return data;
}
