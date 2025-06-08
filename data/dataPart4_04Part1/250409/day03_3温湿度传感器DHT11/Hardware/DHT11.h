#ifndef __DHT11_H
#define __DHT11_H

void DHT11_Init(void);
void DHT11_Req(void);
uint8_t DHT11_Resp(void);
uint8_t DHT11_GetByteData(void);
#endif

