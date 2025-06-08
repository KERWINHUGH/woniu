#ifndef _USART_H
#define _USART_H

#include <stdio.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t data);
void Serial_SendHalfWord(uint16_t data);
//发送数组，数组元素均为8位数字
void Serial_SendArr(uint8_t *arr, uint16_t len);
//发送字符串
void Serial_SendStr(char *str);
//发送长数字，将数字转为字符发送
void Serial_SendNum(uint32_t num);


#endif
