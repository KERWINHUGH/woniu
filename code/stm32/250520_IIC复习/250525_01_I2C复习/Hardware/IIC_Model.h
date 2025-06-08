#ifndef _IIC_MODEL_H
#define _IIC_MODEL_H

//��ʼ��IIC��������
void IIC_ModelInit(void);

//IIC��ʼ�ź�
void IIC_Start(void);


//IIC�����ź�
void IIC_Stop(void);

//IIC����һλACK
void IIC_SendACK(uint8_t Ack);

//IIC����һ���ֽ�
void IIC_SendByte(uint8_t data);

//IIC����һλACK
uint8_t IIC_ReceiveACK(void);

//IIC����һ���ֽ�
uint8_t IIC_RecevieByte(void);



#endif