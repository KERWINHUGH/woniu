#ifndef _IIC_SOFTSIMULATE_H
#define _IIC_SOFTSIMULATE_H

void IIC_ModeInit(void);
void IIC_Strat(void);
void IIC_Stop(void);
void IIC_SendAck(uint8_t ack);
void IIC_SendData(uint8_t data);
uint8_t IIC_ReceiveAck(void);
uint8_t IIC_ReceiveData(void);

#endif
