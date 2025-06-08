#include "STM32F10x.h"
#include "DHT.h"
#include "Delay.h"

GPIO_InitTypeDef GPIO_InitStruct;
//初始化一个引脚----PA0
void DHT_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}
//设置主机为输出模式
//不需要再设置引脚
void DHT_SetOutputMode(void)
{
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}
//设置主机为输入模式
//不需要再设置引脚
void DHT_SetInputMode(void)
{
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}
//发送请求
void DHT_Req(void)
{
	DHT_SetOutputMode();
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	Delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	Delay_us(30);
}
//等待回复
//错误点1：当主机等待DHT11回复时，主机发送请求时已经将线路拉高，此时只需要判断线路电平是否为1
//错误点2：当判断线路电平为0时，说明DHT11正在回复，此时继续等待DHT发送高电平，然后再返回SUCCESS
uint8_t DHT_Resp(void)
{
	DHT_SetInputMode();
	//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
	//Delay_us(45);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
		return SUCCESS;
	}else
	{
		return ERROR;
	}
}
//获取一个字节
//错误点1：获得8个比特位时，循环应该在读取引脚状态之前
//错误点2：data初始化应该是0x00，8位比特是2位16进制
//错误点3：data应该是和 0x80 进行或运算
uint8_t DHT_GetByte(void)
{
	uint8_t data = 0x00;
	for(int i = 0; i < 8 ; i++)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
		Delay_us(35);
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
		{
			data |= (0x80>>i);
		}
	}
	return data;
}
//获得当前温湿度
//错误点1：获得温湿度的时候，需要先判断DHT11的回复是否成功
//错误点2：其次获取温湿度时，不需要循环，在外部调用时循环获得温湿度
//在这个函数中加上while（1）会导致程序一直卡在这里
void DHT_GetNowTemHumi(TemHumi *NowTemHumi)
{
	//while(1)
	//{
		DHT_Req();
		if(DHT_Resp() == SUCCESS)
		{
			NowTemHumi->Humi_int = DHT_GetByte();
			NowTemHumi->Humi_deci = DHT_GetByte();
			NowTemHumi->Tem_int = DHT_GetByte();
			NowTemHumi->Tem_deci= DHT_GetByte();
			NowTemHumi->CheckSum = DHT_GetByte();
		}
	//}
}
