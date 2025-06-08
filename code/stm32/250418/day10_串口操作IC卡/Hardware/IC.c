#include "stm32f10x.h"                  // Device header
#include "IC.h"
#include <stdio.h>

//计算校验公式：是从包的第一个字节到第包长减一个字节的异或值，最后取反
//也就是从第一个字节到倒数第二个字节的异或值，最后取反。
uint8_t checkVolidateValue(uint8_t *buf)
{
	uint8_t checksum = 0;
	for(uint8_t i = 0; i<(buf[1]-1) ; i++)
	{
		checksum^=buf[i];
	}
	buf[buf[1]-1] = ~checksum;//校验和，放到数组的最后一位
	return buf[buf[1]-1];
}

//发送指令
void Sent_ICode(uint8_t *arr)
{
	checkVolidateValue(arr);
	Serial_Arr(arr,arr[1]);
}


uint8_t message[100];//收到的消息放在这个数组

void dealReadCardTask(void);
//接收到数据的中断函数：例子接收的数据：01 0C A1 20 00 04 00 0A DC EF F9 B7
void USART1_IRQHandler(void)
{
	//静态的变量，在方法被多次调用的时候，可以保持之前的值
	static uint8_t index = 0;//数组的索引位置
	static uint8_t len = 0; //要接收的数组的长度
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		//接收发送过来的数据
		uint8_t data = USART_ReceiveData(USART1);
	
		//如果索引为1，表示收到了第二个数据，第二个数据正好是长度，所以把数据赋值给len
		if(index==1)
		{
			len = data;
		}
		
		//收到一个数据，就存一个数据
		message[index++] = data;
		
		//如果索引++后，正好等于收到的数据长度，说明接收数据完成，就把index和len恢复缺省默认值，处理具体逻辑
		if(index==len)
		{
			index = 0;
			len = 0;
			//处理逻辑,根据收到的不同的指令，调用不同的函数去处理数据
			if(message[2]==0xA1)//读取卡号
			{
				dealReadCardTask();
				
			}else if (message[2]==0xA3)//读取数据块
			{
			
			}else if (message[2]==0xA4)//写数据块
			{
			
			}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

//读取卡号，返回的值：01 0C A1 20 00 04 00 0A DC EF F9 B7
void dealReadCardTask(void)
{
	//2 字节卡类型+4 字节卡号
	uint8_t cardType[2] = {0x00};
	uint8_t cardNum[4] = {0x00};
	
	//老师没有验证校验和
	if(message[4] == 0x00)//返回成功
	{
		//从message数组的第5个索引位置开始，拷贝2个值到cardType里面
		memcpy(cardType,&message[5],2);
		memcpy(cardNum,&message[7],4);
		
		//1 4 7 
		for(uint8_t i = 0 ;i <2;i++)
		{
			OLED_ShowHexNum(1,1+(i*3),cardType[i],2);
		}
		
		for(uint8_t j = 0 ;j <4;j++)
		{
			OLED_ShowHexNum(2,1+j*3,cardNum[j],2);
		}
		
	}
	else
	{
	
	}
}







