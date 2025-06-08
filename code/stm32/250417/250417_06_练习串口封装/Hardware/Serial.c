#include "stm32f10x.h"                  // Device header
#include "Serial.h"


void USART_Config(void)
{
	//1.时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.USART结构体
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_Mode =USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStruct.USART_BaudRate =9600;
	USART_InitStruct.USART_Parity =USART_Parity_No;
	USART_InitStruct.USART_StopBits =USART_StopBits_1;
	USART_InitStruct.USART_WordLength =USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);
	//4.开启串口
	USART_Cmd(USART1,ENABLE);
}

void SendByte(uint8_t data)
{
	USART_SendData(USART1,data);
	//发送数据寄存器不为空时一直等待
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void SendArr(uint8_t *arr, uint32_t len)
{
	for(uint16_t i = 0; i < len; i++)
	{
		SendByte(arr[i]);
	}
}

void SendStr(char *str)
{
	//错误点1：当字符串的最后一个字符，即循环到'\0'时挑出循环
	//'\0'是具体的值，需要解引用取值
	while(*str)
	{
		SendByte(*str++);//str解引用取值，然后str再++
	}
}
void SendNumber(uint32_t num)
{
	char arr[11] ;
	uint8_t index =10;
	arr[index] = '\0';
	//知识点1：将数字拆解出后赋值给字符数组元素
	do{
		arr[--index] = num% 10+ '0';
		num/=10;
		//知识点2：当num等于0时，退出循环
	}while(num!=0);
	//知识点3：退出循环后将字符数组发出，发出时，注意存储数组元素使从数组最后一位向前存储的，数组头几个元素为空
	//因此需要将    为什么取地址，为什么发送字符串从index
	SendStr(&arr[index]);
}
//知识点4：参数是fputc的int ch, FILE *fp
int fputc(int ch, FILE *fp)
{
	//知识点5：里面只需要发送传进来的参数字符
	SendByte(ch);
	//错误点2：返回值应该是传进来的字符
	return ch;
}
