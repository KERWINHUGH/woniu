#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Motor.h"

void dealTask(void);

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_3 ;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//串口配置
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStruct.USART_BaudRate =9600;
	USART_InitStruct.USART_Parity =USART_Parity_No;
	USART_InitStruct.USART_StopBits =USART_StopBits_1;
	USART_InitStruct.USART_WordLength =USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStruct);
	
	//开串口接收中断
	//中断标志一定是外设加杠加IT，不是FLAG
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel =USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStruct);
	
	//启动串口
	USART_Cmd(USART2,ENABLE);
}


void Serial_Byte(uint8_t data)
{
	USART_SendData(USART2,data);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
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
char message[100];
void USART2_IRQHandler(void)
{
	static uint8_t index = 0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{
		//接收发送的数据
		uint8_t data = USART_ReceiveData(USART2);	
		if(data == '@')
		{
			index = 0;
		}else if(data != '\r' && data != '\n')
		{
			//将收到的数据放在数组中
			message[index++] = data;
		}else if(data == '\n')
		{
			message[index] = '\0';
			dealTask();
		}
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}
void dealTask(void)
{
	if(strcmp( message,"TURN_ON") == 0)
	{
		Left_SetSpeed(500);
		Right_SetSpeed(-500);
		printf("%s","Turn On Success");
	}else if(strcmp( message,"TURN_OFF") == 0)
	{
		Right_SetSpeed(0);
		printf("%s","Turn Off Success");
	}else
	{
		printf("%s","unrecongnize error");
	}
}
