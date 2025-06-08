#include "stm32f10x.h"                  // Device header

void Delay(int ms)
{
	while(ms--);
}

//int main()
//{
//	//1.设置时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	//2.配置端口和初始化引脚
//	//配置PA0引脚
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA,&GPIO_InitStruct);
//	

//	//3.三种方式实现设置引脚
//	while(1){
//		//--1.点亮PA0
//		GPIO_SetBits(GPIOA,GPIO_Pin_0 );
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_0 );
//		Delay(5000000);
//		
//		//--2.点亮PA1
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//		Delay(5000000);
//		
//		//--3.点亮PA2
//		GPIO_SetBits(GPIOA,GPIO_Pin_2);
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//		Delay(5000000);
//		
//		//--4.点亮PA3
//		GPIO_SetBits(GPIOA,GPIO_Pin_3);
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
//		Delay(5000000);
//		
//		//--5.点亮PA4
//		GPIO_SetBits(GPIOA,GPIO_Pin_4);
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//		Delay(5000000);
//		
//				//--4.点亮PA3
//		GPIO_SetBits(GPIOA,GPIO_Pin_3);
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
//		Delay(5000000);
//		
//				//--3.点亮PA2
//		GPIO_SetBits(GPIOA,GPIO_Pin_2);
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//		Delay(5000000);
//		
//				//--2.点亮PA1
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);
//		Delay(5000000);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//		Delay(5000000);
//	}
//}

//int main()
//{
//	//1.设置时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	//2.配置端口和初始化引脚
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA,&GPIO_InitStruct);
//	
//	//3.三种方式实现设置引脚
//	

//	//--2.
//	while(1){
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
//		Delay(5000000);
//		
//			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
//		Delay(5000000);
//		
//			GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
//		Delay(5000000);
//		
//			GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
//		Delay(5000000);
//		
//			GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
//		Delay(5000000);
//		
//			GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
//		Delay(5000000);
//		
//			GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);
//		Delay(5000000);
//		
//			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
//		Delay(5000000);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
//		Delay(5000000);
//	}

//}

int main()
{
	//1.设置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2.配置端口和初始化引脚
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3.三种方式实现设置引脚
	
	//--1.
	while(1){
		//--3.
		GPIO_Write(GPIOA,0x00000001);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000001);
		Delay(5000000);
		
				GPIO_Write(GPIOA,0x00000002);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000002);
		Delay(5000000);
		
				GPIO_Write(GPIOA,0x00000004);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000004);
		Delay(5000000);
		
				GPIO_Write(GPIOA,0x00000008);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000008);
		Delay(5000000);
		
				GPIO_Write(GPIOA,0x00000010);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000010);
		Delay(5000000);
		
				GPIO_Write(GPIOA,0x00000008);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000008);
		Delay(5000000);
		
				GPIO_Write(GPIOA,0x00000004);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000004);
		Delay(5000000);
		
				GPIO_Write(GPIOA,0x00000002);
		Delay(5000000);
		GPIO_Write(GPIOA,0x00000002);
		Delay(5000000);
		
	}
}
	
	