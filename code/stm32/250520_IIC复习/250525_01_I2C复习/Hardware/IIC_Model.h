#ifndef _IIC_MODEL_H
#define _IIC_MODEL_H

//初始化IIC引脚配置
void IIC_ModelInit(void);

//IIC开始信号
void IIC_Start(void);


//IIC结束信号
void IIC_Stop(void);

//IIC发送一位ACK
void IIC_SendACK(uint8_t Ack);

//IIC发送一个字节
void IIC_SendByte(uint8_t data);

//IIC接收一位ACK
uint8_t IIC_ReceiveACK(void);

//IIC接收一个字节
uint8_t IIC_RecevieByte(void);



#endif