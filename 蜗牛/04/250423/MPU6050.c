#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
/**
1.Ӳ��I2CҪʹ�ã�I2Cʱ�ӿ���-�ṹ������
2.Ӳ��I2C��ʼ����������������.....
*/
void MPU6050_WriteData(uint8_t registerData,uint8_t data)
{
	//1.��ʼ
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);//�ȴ�EV5�¼���Start��ɵ��¼�
	
	//���͵�ַ
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS);//EV6�¼����ȴ���ַ�������

	I2C_SendData(I2C2,registerData);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING)!=SUCCESS);//EV8�¼�..����������
	
	I2C_SendData(I2C2,data);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS);//EV8_2�¼�����ʾ����
	
	I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t MPU6050_ReadData(uint8_t registerData)
{
	//��ʼ
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);//�ȴ�EV5�¼���Start��ɵ��¼�
	
	//���͵�ַ��Write
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS);//EV6�¼����ȴ���ַ�������

	//���ͼĴ�����ַ
	I2C_SendData(I2C2,registerData);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS);//EV8�¼�..����������
	
	//���¿�ʼ
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);//�ȴ�EV5�¼���Start��ɵ��¼�
	
	//���͵�ַ Read EV6�¼������֣�һ���Ƿ���ģʽ��Write��һ���ǽ���ģʽ��Read��
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!=SUCCESS);//EV6�¼����ȴ���ַ�������
	
	//���鷳�ĵط�������  1.����Զ�����Ӧ���᲻ͣ�ķ�����
	//                    2.�����ź�Ӧ�÷���������⣿
	I2C_GenerateSTOP(I2C2,ENABLE);//1.STOP�ź�Ҫ��ǰ�������ߴӻ������յ��������֮�󣬾ͽ�����
	//�ر��Զ�Ӧ��
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	//һֱ�ȵ�RXNE���������ݼĴ�����Ϊ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED)!=SUCCESS);
	uint8_t data = I2C_ReceiveData(I2C2);//�����ݼĴ���������
	
	//���Զ�Ӧ��
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	return data;
}


void I2CModel_Init(void)
{
	//1.��RCCʱ�ӣ�GPIO��I2C��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	
	//2.GPIO�ṹ��  PB10=SCL(���)  PB11=SDA(���������)
	//���ʣ�PB11���óɸ��ÿ�©�Ժ󣬻��ܲ������룿
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;//���ÿ�©����Ϊ��Ӳ�������Ƿ������ݣ�
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//3.I2C�ṹ��
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;//�Ƿ��Զ�Ӧ��
	I2C_InitStruct.I2C_ClockSpeed = 90000;//��׼ģʽ���100k������400k
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_16_9;//SCLʱ���ź��õ�
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;//������Ҳ��һ����ַ 
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//ʹ��7λ��ַ 
	I2C_Init(I2C2,&I2C_InitStruct);
	//4.����
	I2C_Cmd(I2C2,ENABLE);
}

void MPU6050_Init(void)
{
	I2CModel_Init();
	
	//��Դ���� 1.˯��ģʽ  2.����   3 ʱ��
	MPU6050_WriteData(PWR_MGMT_1,0x01);
	MPU6050_WriteData(PWR_MGMT_2,0x00);
	
	MPU6050_WriteData(SMPLRT_DIV,0x02);
	MPU6050_WriteData(CONFIG,0x06);
	MPU6050_WriteData(GYRO_CONFIG,0x18);
	MPU6050_WriteData(ACCEL_CONFIG,0x18);
}


void getMpu6050Data(MPU6050_Data *mpu6050Data)
{
	mpu6050Data->accX = MPU6050_ReadData(ACCEL_XOUT_H)<<8 | MPU6050_ReadData(ACCEL_XOUT_L);
	mpu6050Data->accY = MPU6050_ReadData(ACCEL_YOUT_H)<<8 | MPU6050_ReadData(ACCEL_YOUT_L);
	mpu6050Data->accZ = MPU6050_ReadData(ACCEL_ZOUT_H)<<8 | MPU6050_ReadData(ACCEL_ZOUT_L);
	mpu6050Data->groyX = MPU6050_ReadData(GYRO_XOUT_H)<<8 | MPU6050_ReadData(GYRO_ZOUT_L);
	mpu6050Data->groyY = MPU6050_ReadData(GYRO_YOUT_H)<<8 | MPU6050_ReadData(ACCEL_YOUT_L);
	mpu6050Data->groyZ = MPU6050_ReadData(GYRO_ZOUT_H)<<8 | MPU6050_ReadData(ACCEL_ZOUT_L);
}