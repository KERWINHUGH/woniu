#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdio.h>

void USART_Config(void);
void SendByte(uint8_t data);
void SendArr(uint8_t *arr, uint32_t len);
void SendStr(char *str);
void SendNumber(uint32_t num);
int fputc(int ch, FILE *fp);

#endif
