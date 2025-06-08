#include "stm32f10x.h"                  // Device header
#include "IC.h"


//计算校验公式：从包的第一个字节到包长减一个字节的长度的异或值
//即数组第一个元素异或第二个元素，一直异或到倒数第二个元素，最后取反
uint8_t CheckVolidataVal(uint8_t *buf)
{
	uint8_t checksum = 0;
	for(uint8_t i = 0; i < (buf[1]-1); i++)
	{
		checksum ^= buf[i];
	}
	buf[buf[1]-1] = ~checksum;//将校验和放到数组中
	return buf[buf[1]-1] ;
}

void dealReadcardTask(void);

uint8_t message[100];
//接收到数据的中断函数
void USART1_IRQHandler(void)
{
	static uint8_t index = 0;//数组的索引值
	static uint8_t len = 0;//要接收的数据的长度
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		//接收发送的数据
		uint8_t data = USART_ReceiveData(USART1);	
		
		//如果索引为1，表示收到了第二个数据，第二个数据是传输数据的长度，所以把这一次传输的数据赋值给len，得到发送过来的数据长度
		if(index == 1)
		{
			len = data;
		}
		
		//收到一个数据，就将数据放到数组中
		message[index++] = data;
		
		//如果索引值++后，正好等于收到数据长度，说明接收完成，把index和len恢复默认值，并处理具体逻辑
		if(index == len)
		{
			index =0;
			len =0;
			//处理具体逻辑,根据收到的不同的指令，去调用不同的处理数据的函数
			if(message[2] == 0xA1)
			{
				dealReadcardTask();
			}else if(message[2] == 0xA3)
			{
				//读取块信息
				
			}else if(message[2] == 0xA4)
			{
				//写入块信息
				
			}
		}
			
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
void dealReadcardTask(void)
{
	//验证校验和
	if(message[4] == 0x00)//返回成功
	{
		
	}else 
	{
		
	}
}
