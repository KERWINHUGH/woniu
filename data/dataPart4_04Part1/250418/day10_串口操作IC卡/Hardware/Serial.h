#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>
#include <string.h>
void Serial_Init(void);
void Serial_Byte(uint8_t data);
void Serial_Arr(uint8_t *arr , uint16_t len);
void Serial_String(char *str);
void Serial_Num(uint32_t num);


#endif

