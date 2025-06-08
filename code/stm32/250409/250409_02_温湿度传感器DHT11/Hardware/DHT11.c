#include "stm32f10x.h"                  // Device header
#include "DHT11.h"
#include "Delay.h"

GPIO_InitTypeDef GPIO_InitStruct;
//初始化DHT11
void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}
//切换为输出模式
void DHT11_SetPP(void)
{
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//初始值给高电平
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	
}
//切换为输入模式
void DHT11_SetIPU(void)
{
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}
//主机（STM32）发送一个请求信息
void DHT11_Req(void)
{
	//1.切换为输出模式
	DHT11_SetPP();
	//2.输出低电平20ms
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	Delay_ms(20);
	//3.主机再拉高20~40us
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	Delay_us(30);
}
//DHT11,响应主机的信息
uint8_t DHT11_Resp(void)
{
	//1.主机切换输入模式
	DHT11_SetIPU();
	//2.读取温湿度传感器的响应数据
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
	{
		//等待DHT11从机响应信号低电平结束，直到拉高
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
		return SUCCESS;
	}else
	{
		return ERROR;
	}
}
//获取一个字节的数据，DHT11发送数据，使STM32处理数据
uint8_t DHT11_GetByteData(void)
{
	uint8_t data = 0x00;//0000 0000
	for(int i = 0; i < 8; i++)
	{
		//1.等待一个高电平，等待一个低电平
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
		//2.延迟35us
		Delay_us(35);
		//3.读取电平状态，如果读到的是1，，表示DHT11发送的是1
		if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
		{
			//对方发数据高位先行，先发送高位，0000 0000 -> 1000 1000
			data |=(0x80>>i) ;
		}
	}
	return data;
}
void DHT11_GetTemperAndHumidity(TemHum *NowTemHum)
{
		DHT11_Req();
		if(DHT11_Resp() == SUCCESS)
		{
			NowTemHum->Hum_Integer = DHT11_GetByteData();
			NowTemHum->Hum_decimal = DHT11_GetByteData();
			NowTemHum->Tem_Integer = DHT11_GetByteData();
			NowTemHum->Tem_decimal = DHT11_GetByteData();
			NowTemHum->checksum = DHT11_GetByteData();
			//Delay_s(1);
		}
}
