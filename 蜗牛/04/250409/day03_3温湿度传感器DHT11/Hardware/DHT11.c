#include "stm32f10x.h"                  // Device header
#include "Delay.h"

GPIO_InitTypeDef GPIO_InitStruct;
//初始化DHT11
void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

//切换为输出模式,每次到初始化的时候，或者开始请求的时候，主机保证IO线路是高电平
void DHT11_SetPP(void)
{
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//初始是高电平
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
	//2.主机输出低电平至少18ms
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	Delay_ms(20);
	//3.主机再拉高20-40us
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	Delay_us(30);
}

//DHT11，响应主机的信息
//如果收到了DHT11响应信息，返回一个SUCCESS（1），如果没有收到，返回ERROR（0）
uint8_t DHT11_Resp(void)
{
	//1.切换成输入模式
	DHT11_SetIPU();
	//2.读取温湿度传感器的响应数据
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==0)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==0);//等到从机从低电平拉高了
		return SUCCESS;
	}
	else
	{
		return ERROR;
	}
}

//获取一个字节的数据byte，DHT11给我们发数据，DHT11发送数据是高位先行
uint8_t DHT11_GetByteData(void)
{
	uint8_t data = 0x00;//0000 0000                  假设对方1111 0000     
	
	for(uint8_t i = 0 ;i < 8 ; i++)
	{
		//1.等待一个高电平，等待一个低电平
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==1);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==0);
		//2.延迟35us
		Delay_us(35);
		//3.读取电平状态,如果读到的是1，表示DHT11，发送了一个1
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==1)
		{
		    data |= (0x80>>i);//如果要把一个变量某一位变成1，其他位不变。|=对应的位
		}
	}
	
	return data;
}

//总的获取数据的方法








