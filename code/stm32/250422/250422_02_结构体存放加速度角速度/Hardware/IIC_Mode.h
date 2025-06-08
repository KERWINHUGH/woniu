#ifndef _IIC_MODE_H
#define _IIC_MODE_H

//我们模拟的是主机
void I2C_ModeInit(void);//GPIO

void I2C_ModeStart(void);//主机控制开始信号
void I2C_ModeStop(void);//主机发送结束信号

void I2C_ModeSendData(uint8_t data);//主机发送一个字节数据的消息
void I2C_ModeSendACK(uint8_t ack);//主机给从机发送一位的应答（ACK）

uint8_t I2C_ModeReceiveData(void);//主机接收从机一个字节数据的消息
uint8_t I2C_ModeReceiverACK(void);//主机响应只有一位，0表示应答，1表示不应答（ACK）


#endif
