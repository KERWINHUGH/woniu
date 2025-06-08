#ifndef _I2C_MODEL_H
#define _I2C_MODEL_H

void I2C_ModelInit(void);

void I2C_ModelStart(void);

void I2C_ModelStop(void);

void I2C_ModelSendAck(uint8_t ack);

void I2C_ModelSendData(uint8_t data);

uint8_t I2C_ModelReceiveAck(void);

uint8_t I2C_ModelReceiveData(void);

#endif
