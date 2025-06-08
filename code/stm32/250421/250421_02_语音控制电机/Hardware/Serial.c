#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Motor.h"
#include "OLED.h"

void dealTask(void);

//串口初始化
void Serial_Init(void)
{
	//1.时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9  ;//USART1_TX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 ;//USART1_RX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.USART
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity =USART_Parity_No;
	USART_InitStruct.USART_StopBits  = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruct);
	
	//1.串口接收中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	//2.NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStruct);
	
	//4.开启USART
	USART_Cmd(USART1,ENABLE);
}
//串口发送字节
void Serial_Byte(uint8_t data)
{
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}
//串口发送数组
void Serial_Arr(uint8_t *arr,uint16_t len)
{
	for(uint16_t i = 0; i < len ;i ++)
	{
		Serial_Byte(arr[i]);
	}
}
//串口发送字符串
void Serial_Str(char *str)
{
	while(*str)
	{
		Serial_Byte(*str++);
	}
}
//串口发送数字
void Serial_Num(uint32_t num)
{
	char arr[11] = {0};
	uint8_t index = 10;
	arr[index] = '\0';
	do{
		arr[--index] = num%10+'0';
		num/=10;
	}while(num!=0);
	
		Serial_Str(&arr[index]);
}
//串口打印
int fputc(int ch,FILE* f)
{
	Serial_Byte(ch);
	return ch;
}

char msg[100] ;
//串口接收中断
void USART1_IRQHandler(void)
{
	static uint8_t index = 0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		uint8_t data = USART_ReceiveData(USART1);
		if(data == '@')
		{
			index = 0;
		}else if(data != '\r' && data != '\n')
		{
			msg[index++] = data;
		}else if(data == '\n')
		{
			msg[index] = '\0';
			dealTask();
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

void dealTask(void)
{
	if(strcmp(msg , "MOTOR_ON" ) == 0)
	{
		Left_SetSpeed(20);
		printf("OM");
	}else if(strcmp(msg , "MOTOR_OFF" ) == 0)
	{
		Left_SetSpeed(0);
		printf("CM");
	}else if(strcmp(msg , "MOTOR_FORWARD" ) == 0)
	{
		Left_SetSpeed(20);
		printf("FM");
	}else if(strcmp(msg , "MOTOR_BACKWARD" ) == 0)
	{
		Left_SetSpeed(-20);
		printf("BM");
	}else if(strcmp(msg , "MOTOR_ASC" ) == 0)
	{
		uint16_t speed = TIM_GetCapture1(TIM2);
		if(speed == 20)
		{
			Left_SetSpeed(40);
		}else if(speed == 40)
		{
			Left_SetSpeed(60);
		}else if(speed == 60)
		{
			Left_SetSpeed(80);
		}
		printf("AM");
	}else if(strcmp(msg , "MOTOR_DESC" ) == 0)
	{
		uint16_t speed = TIM_GetCapture1(TIM2);
		if(speed == 20)
		{
			Left_SetSpeed(0);
		}else if(speed == 40)
		{
			Left_SetSpeed(20);
		}else if(speed == 60)
		{
			Left_SetSpeed(40);
		}else if(speed == 80)
		{
			Left_SetSpeed(60);
		}
		printf("DM");
	}
	
}
