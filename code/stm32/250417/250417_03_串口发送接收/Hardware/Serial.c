#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "string.h"
#include "OLED.h"
#include "LED.h"

/**
**	串口初始化
**	
*/

extern uint8_t data;

void Serial_Init(void)
{
	//1.开串口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2.配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	//初始化发送引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//初始化接收引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.USART结构体
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);
	
	//USART IT
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

	//4.启动串口
	USART_Cmd(USART1,ENABLE);
}

void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1 ,USART_IT_RXNE) == SET)
	{
		data = USART_ReceiveData(USART1);
		if(data == '1')
		{
			LED1_On();
		}else if(data == '2')
		{
			LED1_Off();
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

//USART发送一个字节
void Send_Byte(uint8_t data)
{
	USART_SendData(USART1,data);
	//TXE:Transmit data register empty
	//判断发送数据寄存器是否为空，为空则继续发，不为空则等待
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

//USART发送一个字节数组
void Send_Array(uint8_t *array, uint16_t len)
{
	for(uint16_t i = 0; i < len; i++)
	{
		Send_Byte(array[i]);
	}
}

//USART发送一个字符串
void Send_String(char *string)
{
	while(*string)
	{
		Send_Byte(*string++);
	}
}

//USART发送一串1232456，数字转字符发送
void Send_Numbers(uint32_t num)
{	
	char arr[11] ; 
	uint8_t index = 10;
	arr[index] = '\0';
		
	//取每位的数字
	do{
		//取模之后+字符'\0'转换成字符串
		arr[--index] =  '0' + num%10 ; 
		num /= 10;
	}while(num != 0);
	
	Send_String(&arr[index]);
}

int fputc(int ch,FILE *fp)
{
	Send_Byte(ch);
	return ch;
}
