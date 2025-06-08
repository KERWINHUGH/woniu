#include "stm32f10x.h"                  // Device header
#include "USART.h"

//初始化串口的收发引脚
void Serial_Init(void)
{
	//1.开启USART和GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.USART结构体
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_Init(USART1,&USART_InitStruct);
	
	//4.开启USART
	USART_Cmd(USART1,ENABLE);
}
//发送一个字节
void Serial_SendByte(uint8_t data)
{
	USART_SendData(USART1,data);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	
}
//发送16位数ADC寄存器DR值
void Serial_SendHalfWord(uint16_t data)
{
	//先送高8位
	Serial_SendByte((data>>8)&0xFF);
	//再送低八位
	Serial_SendByte(data&0xFF);
}
//发送数组，数组元素均为8位数字
void Serial_SendArr(uint8_t *arr, uint16_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		Serial_SendByte(arr[i]);
	}
}
//发送字符串
void Serial_SendStr(char *str)
{
	while(*str)
	{
		Serial_SendByte(*str++);
	}
}
//发送长数字，将数字转为字符发送
void Serial_SendNum(uint32_t num)
{
	//1.定义一个数组存放转为字符后的数字
	char arr[11] = {0};
	//2.定义数组索引
	uint8_t index = 10;
	//3.将数组最后一位赋值为结束符‘\0’
	arr[index] = '\0';
	
	//4.循环转换数字
	do{
		//5.转换数字为字符串，并直接将转换后的字符存到字符数组中
		//字符数组最后一位的index位置已经存放了结束符，故从index-1个位置开始转换
		arr[--index] = num%10 + '0';	//数字对10取模后就是数字的个位数，再加上 字符0 '0'（不是结束符'\0'） 存放到数组的倒数第二位
		num/=10;	//数字除以10后，相当于舍弃掉了已经存到数组中的最后一位
	}while(num!=0);//数字不为0时结束，因为每次循环中都会将数字取模再数以10
	
	Serial_SendStr(&arr[index]);
}
int fputc(int ch,FILE *fp)
{
	Serial_SendByte(ch);
	return ch;
}
