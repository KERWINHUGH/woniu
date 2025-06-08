#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

void Serial_Init(void);
void Send_Byte(uint8_t data);
void Send_Array(uint8_t *array, uint16_t len);
void Send_String(char *string);
void Send_Numbers(uint32_t number);
int fputc(int ch,FILE *fp);
	
#endif
