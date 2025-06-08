#ifndef __I2C_MODEL_H
#define __I2C_MODEL_H
//������������Ǹ�STM32����д�ģ�MPU6050�����Ѿ���I2CЭ��ĳ����ˡ�
void I2C_ModelInit(void);//GPIO

void I2C_ModelStart(void);//������ʼ

void I2C_ModelSendData(uint8_t data);//��������һ�����ݣ��ֽڣ�

uint8_t I2C_ModelReceiveAck(void);//����������Ӧֻ��1λ��0��ʾӦ��1��ʾ��Ӧ��

uint8_t I2C_ModeReceiveData(void);//��������һ������8λ

void I2C_ModelSendAck(uint8_t ack);//�������ӻ�һ����Ӧ1λ

void I2C_ModelStop(void);//�������ͽ�����Ϣ
#endif

