#ifndef _IIC_MODE_H
#define _IIC_MODE_H

//����ģ���������
void I2C_ModeInit(void);//GPIO

void I2C_ModeStart(void);//�������ƿ�ʼ�ź�
void I2C_ModeStop(void);//�������ͽ����ź�

void I2C_ModeSendData(uint8_t data);//��������һ���ֽ����ݵ���Ϣ
void I2C_ModeSendACK(uint8_t ack);//�������ӻ�����һλ��Ӧ��ACK��

uint8_t I2C_ModeReceiveData(void);//�������մӻ�һ���ֽ����ݵ���Ϣ
uint8_t I2C_ModeReceiverACK(void);//������Ӧֻ��һλ��0��ʾӦ��1��ʾ��Ӧ��ACK��


#endif
