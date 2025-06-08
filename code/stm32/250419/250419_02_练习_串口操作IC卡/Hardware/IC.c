#include "stm32f10x.h"                  // Device header
#include "IC.h"
#include "stdio.h"
#include "Serial.h"
#include "OLED.h"

//读取卡号
void dealReadCardTask(void);
//读取块数据
void dealReadBlockTask(void);
//写入块数据
void dealWriteBlockTask(void);

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

void Sent_ICode(uint8_t *arr)
{
	CheckVolidataVal(arr);
	Serial_Arr(arr,arr[1]);
}

uint8_t message[100];
//接收到数据的中断函数
void USART1_IRQHandler(void)
{
	//静态变量，在函数被调用时，可以保持之前的值
	static uint8_t index = 0;//数组的索引值
	static uint8_t len = 0;//要接收的数据的长度
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		//接收发送的数据
		uint8_t data = USART_ReceiveData(USART1);	
		
		//如果索引为1，表示收到了第二个数据，第二个数据是传输数据的长度
		//所以把这一次传输的数据赋值给len，得到发送过来的数据长度
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
				dealReadCardTask();
			}else if(message[2] == 0xA3)
			{
				//读取块信息
				dealReadBlockTask();
			}else if(message[2] == 0xA4)
			{
				//写入块信息
				dealWriteBlockTask();
			}
		}
			
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
//读取卡号，返回值;01 0C A1 20 00 04 00 0A DC EF F9 B7
void dealReadCardTask(void)
{
	//2字节卡类型
	uint8_t cardType[2] = {0x00};
	//4字节卡号
	uint8_t cardNum[4] = {0x00};
	
	//验证校验和
	uint8_t checksum = CheckVolidataVal(message);
	
	if(checksum != message[7])
	{
		OLED_ShowString(1,1,"Check Erorr");
		return;
	}
	
	//判断是否读成功
	if(message[4] == 0x00)//返回成功
	{
		//拷贝数组特定长度的元素
		memcpy(cardType,&message[5],2);
		memcpy(cardNum ,&message[7],4);
		
		//1  4  7
		for(uint8_t i = 0; i < 2; i++)
		{
			OLED_ShowHexNum(1,1+i*3,cardType[i],2);
		}
		for(uint8_t j = 0; j < 4; j++)
		{
			OLED_ShowHexNum(2,1+j*3,cardNum[j],2);
		}
	}else //返回失败
	{
		OLED_ShowString(1,1,"Read ID Erorr");
	}
}

//读取块数据
void dealReadBlockTask(void)
{
	//块数据
	uint8_t blockData[16] = {0x00};
	
	//验证校验和
	uint8_t checksum = CheckVolidataVal(message);
	
	if(checksum != message[21])
	{
		OLED_ShowString(1,1,"Check Erorr");
		return;
	}
	
	//判断是否读成功
	if(message[4] == 0x00)//返回成功
	{
		//拷贝数组特定长度的元素
		memcpy(blockData ,&message[5],15);
		
		//1  4  7
		for(uint8_t i = 0; i < 3; i++)
		{
			OLED_ShowHexNum(1,1+i*3,blockData[i],2);
		}

	}else //返回失败
	{
		OLED_ShowString(1,1,"Read Block Erorr");
	}
}

//写入块数据
void dealWriteBlockTask(void)
{
	//验证校验和
	uint8_t checksum = CheckVolidataVal(message);
	
	if(checksum != message[7])
	{
		OLED_ShowString(1,1,"Check Erorr");
		return;
	}
	
	//判断是否写成功
	if(message[4] == 0x00)//返回成功
	{
		OLED_ShowString(1,1,"Write Success");
	}else
	{
		OLED_ShowString(1,1,"Write Fail");
	}
}
