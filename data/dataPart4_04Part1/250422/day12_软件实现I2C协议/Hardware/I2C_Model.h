#ifndef __I2C_MODEL_H
#define __I2C_MODEL_H
//我们这个程序是给STM32主机写的，MPU6050里面已经有I2C协议的程序了。
void I2C_ModelInit(void);//GPIO

void I2C_ModelStart(void);//主机开始

void I2C_ModelSendData(uint8_t data);//主机发送一个数据（字节）

uint8_t I2C_ModelReceiveAck(void);//主机接收响应只有1位，0表示应答，1表示不应答

uint8_t I2C_ModeReceiveData(void);//主机接收一个数据8位

void I2C_ModelSendAck(uint8_t ack);//主机给从机一个相应1位

void I2C_ModelStop(void);//主机发送结束信息
#endif

