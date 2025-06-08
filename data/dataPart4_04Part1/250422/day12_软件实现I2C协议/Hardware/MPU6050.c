#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"

void MPU6050_Write(uint8_t registerAddress,uint8_t data)
{
	I2C_ModelStart();
    
	I2C_ModelSendData(0xD0);//Ѱ���豸+д
	I2C_ModelReceiveAck();
	
	I2C_ModelSendData(registerAddress);//���üĴ�����ַ
	I2C_ModelReceiveAck();
	
	I2C_ModelSendData(data);//��������
	I2C_ModelReceiveAck();
	
	I2C_ModelStop();
}

uint8_t MPU6050_Read(uint8_t registerAddress)
{
	//��д��Ϊ�˹̶��Ĵ�����ַ
	I2C_ModelStart();
	I2C_ModelSendData(0xD0);//Ѱ���豸+дW=0
	I2C_ModelReceiveAck();

	//���üĴ�����ַ��MPU 6050�ļĴ���ָ���ָ����Ӧ�ļĴ�����ַ��λ�á��Ȼ����ʱ�򣬻�ֱ�Ӵ������ַ��������
	I2C_ModelSendData(registerAddress);//���üĴ�����ַ
	I2C_ModelReceiveAck();
	
	//���¿�ʼ
	I2C_ModelStart();
	I2C_ModelSendData(0xD1);//Ѱ���豸+��R=1
	I2C_ModelReceiveAck();
	
	//ֱ�Ӵ�֮ǰд��ĵ�ַ��λ�ã���ʼ��������
	uint8_t data = I2C_ModeReceiveData();
	I2C_ModelSendAck(1);//��1��ʾ��Ӧ��  ��0��ʾӦ�𣬶��һ������������
	
	I2C_ModelStop();
	return data;
}

void MPU6050_Init(void)
{
	I2C_ModelInit();
	//����MPU6050��ؼĴ�����ֵ
	MPU6050_Write(PWR_MGMT_1,0x01);
	MPU6050_Write(PWR_MGMT_2,0x00);
	MPU6050_Write(SMPLRT_DIV,0x02);
	MPU6050_Write(CONFIG,0x06);
	MPU6050_Write(GYRO_CONFIG,0x18);
	MPU6050_Write(ACCEL_CONFIG,0x18);
}










