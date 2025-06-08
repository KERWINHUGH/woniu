#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdio.h>
#include <string.h>

void Serial_Init(void);
void Serial_Byte(uint8_t data);
void Serial_Arr(uint8_t *arr,uint16_t len);
void Serial_Str(char *str);
void Serial_Num(uint32_t num);


#endif
