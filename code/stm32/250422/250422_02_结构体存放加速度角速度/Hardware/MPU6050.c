#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "IIC_Mode.h"

void MPU6050_Init(void)
{
	I2C_ModeInit();
	MPU6050_Write(PWR_MGMT_1,0x01);
	MPU6050_Write(PWR_MGMT_2,0x00);
	MPU6050_Write(SMPLRT_DIV,0x02);
	MPU6050_Write(CONFIG,0x06);
	MPU6050_Write(GYRO_CONFIG,0x18);
	MPU6050_Write(ACCEL_CONFIG,0x18);
}

void MPU6050_Write(uint8_t regAdd, uint8_t data)
{
	//MPU6050д��ʱ��
	I2C_ModeStart();
	I2C_ModeSendData(0xD0);//Ѱ���豸+д��������Ҫ�Ķ�д������
	I2C_ModeReceiverACK();
	
	I2C_ModeSendData(regAdd);//ѡ��Ҫ���õļĴ�����ַ
	I2C_ModeReceiverACK();
	
	I2C_ModeSendData(data);//�����������õ�Դ
	I2C_ModeReceiverACK();
	
	I2C_ModeStop();
}

uint8_t MPU6050_Read(uint8_t regAdd)
{
	//MPU6050����ʱ��
	//ǰ�벿��������д��ʱ�򣬽��Ĵ���ָ��ָ��Ҫ���ļĴ���
	I2C_ModeStart();
	I2C_ModeSendData(0xD0);//Ѱ���豸+д��������Ҫ�Ķ�д������
	I2C_ModeReceiverACK();
	
	I2C_ModeSendData(regAdd);//ѡ��Ҫ���õļĴ�����ַ
	I2C_ModeReceiverACK();
	
	//��벿�����ö���ʱ��,ֱ��ȥ���Ĵ���������ȥ��Ҫ���ļĴ�����ַ
	I2C_ModeStart();
	I2C_ModeSendData(0xD1);//Ѱ���豸+����������Ҫ�Ķ�д������
	I2C_ModeReceiverACK();
	
	uint8_t data = I2C_ModeReceiveData();//�����������õ�Դ
	I2C_ModeSendACK(1);//��1��ʾ��Ӧ�𣬷�0��ʾӦ�����Ӧ��Ϊ0���ӻ�ָ�������ƶ�������������
	
	I2C_ModeStop();
	
	return data;
}

