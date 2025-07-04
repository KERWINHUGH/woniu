#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "LED.h"




void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10 ;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//串口配置
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStruct.USART_BaudRate =9600;
	USART_InitStruct.USART_Parity =USART_Parity_No;
	USART_InitStruct.USART_StopBits =USART_StopBits_1;
	USART_InitStruct.USART_WordLength =USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruct);
	
	//开串口接收中断
	//中断标志一定是外设加杠加IT，不是FLAG
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel =USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStruct);
	
	//启动串口
	USART_Cmd(USART1,ENABLE);
}


void Serial_Byte(uint8_t data)
{
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}
void Serial_Arr(uint8_t *arr,uint16_t len)
{
	for(uint16_t i = 0; i < len; i++)
	{
		Serial_Byte(arr[i]);
	}
}
void Serial_String(char *str)
{
	while(*str)
	{
		Serial_Byte(*str++);
	}
}
void Serial_Number(uint32_t num)
{
	char arr[11] ;
	uint16_t index = 10;
	arr[index] = '\0';
	do{
		arr[--index] = num%10 + '0';
		num /= 10;
	}while(num!=0);
	Serial_String(&arr[index]);
}

int fputc(int ch, FILE* fp)
{
	Serial_Byte(ch);
	return ch;
}

