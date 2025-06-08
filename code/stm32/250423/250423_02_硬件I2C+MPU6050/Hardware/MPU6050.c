#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"



//I2C��ʼ��
void I2C_ModelInit(void)
{
	//1.��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//GPIO		PB10 = SCL(���)		PB11 = SDA(����+���)
	//��©ģʽ�¿��Զ�ȡ����״̬
	//����ģʽ�£�������ضϿ����������
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
		
	//2.I2C�ṹ��
	I2C_InitTypeDef I2C_InitStruct;
//	I2C_StructInit(&I2C_InitStruct);//���Բ���д
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;//�Ƿ��Զ�Ӧ��
	I2C_InitStruct.I2C_ClockSpeed = 90000;//��׼ģʽ���100K������ģʽ���400K
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;//��Ϊ�ӻ��ĵ�ַ,������һ����ַ
	
	//��ʱ���ź��õģ���©���ģʽ�µ�ƽ��1��0�ܿ죬mos�ܿ��غܿ���Դﵽ50MHz
	//���Ǵ�0��1�������������軺�����ߵ�ƽ��ռ�ձȾ��������������ߵ�ƽ���ٶ�
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	I2C_Init(I2C2,&I2C_InitStruct);
	
	I2C_Cmd(I2C2,ENABLE);
}

void MPU6050_Init(void)
{
	I2C_ModelInit();
	
	MPU6050_Write(PWR_MGMT_1,0x01);
	MPU6050_Write(PWR_MGMT_2,0x00);
	MPU6050_Write(SMPLRT_DIV,0x02);
	MPU6050_Write(CONFIG,0x06);
	MPU6050_Write(GYRO_CONFIG,0x18);
	MPU6050_Write(ACCEL_CONFIG,0x18);
}

void MPU6050_Write(uint8_t RegAdd,uint8_t data)
{
	//��ʼ�ź�
	I2C_GenerateSTART(I2C2,ENABLE);
	//�ȴ�EV5��ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);//EV5�¼�,start������¼�
	
	//���͵�ַ
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	//�ȴ����͵�EV6��ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);//EV6�¼����ȴ�Ѱַ����
	
	I2C_SendData(I2C2,RegAdd);
	//�ȴ����͵�EV8�����ڷ������ݵ��¼���ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);//EV8�¼�
	
	I2C_SendData(I2C2,data);
	//�ȴ����͵�EV8-2���������ݽ�����ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);//EV8-2�¼�
	
	I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t MPU6050_Read(uint8_t RegAdd)
{
	//��ʼ�ź�
	I2C_GenerateSTART(I2C2,ENABLE);
	//�ȴ�EV5��ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//���͵�ַ��д
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	//�ȴ����͵�EV6��ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);//EV6�¼��ķ���ģʽ
	
	I2C_SendData(I2C2,RegAdd);
	//�ȴ����͵�EV8-2���������ݽ������¼���ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);//EV8-2�¼������ͼĴ�����ַ����
	
	//��ʼ�ź�
	I2C_GenerateSTART(I2C2,ENABLE);
	//�ȴ�EV5��ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//���͵�ַ����
	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Receiver);
	//�ȴ����͵�EV6��ֱ������SUCCESS�˳�ѭ��
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);//EV6�¼��Ľ���ģʽ
	
	//����1�������ź���ǰ�������ߴӻ������յ����ݺ�ͽ���
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	//����2���ر��Զ�Ӧ��
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	//��������		I2C�ṹ�����õ��Զ���ӦACK�������һֱ��������,��ǰ�ر��Զ�Ӧ��
	//��������ʱ���ȴ��������ݼĴ��������ݣ���ȥ����
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);//EV7,�������ݼĴ�����Ϊ��
	uint8_t data = I2C_ReceiveData(I2C2);
	
	//����2�����Զ�Ӧ��
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	
	return data;
}

void getMpu6050Data(MPU6050_Data *MPU6050_speedRegData)
{
	MPU6050_speedRegData->AccX =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
	MPU6050_speedRegData->AccY =  MPU6050_Read(ACCEL_YOUT_H) << 8 | MPU6050_Read(ACCEL_YOUT_L);
	MPU6050_speedRegData->AccZ =  MPU6050_Read(ACCEL_ZOUT_H) << 8 | MPU6050_Read(ACCEL_ZOUT_L);
	
	MPU6050_speedRegData->GyroX =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
	MPU6050_speedRegData->GyroY =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
	MPU6050_speedRegData->GyroZ =  MPU6050_Read(ACCEL_XOUT_H) << 8 | MPU6050_Read(ACCEL_XOUT_L);
}

