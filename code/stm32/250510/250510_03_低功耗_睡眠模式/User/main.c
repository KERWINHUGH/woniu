#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"


//进入睡眠模式后，GPIO是不会工作的，需要一个中断去唤醒，修改代码加上中断后，需要按住开发板RESET键，再点击keil烧录，然后需要松手就可以烧录进去
void EXTI_Demo()
{
	//1.GPIO，配置产生中断的引脚	PA0	配置成输入模式
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//2.AFIO	把GPIO引脚映射到EXTI的对应的线路上（只有GPIO是无法产生中断的）PA0----EXTI的Line0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);//将GPIOA0，映射到EXTI	Line0上
	//3.EXTI
	//EXTI的时钟不用配置，EXTI在CPU外部，外部中断不依赖于时钟，CPU待机或停机模式下时钟也会关闭，外部中断会唤醒CPU
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTI,ENABLE);
	EXTI_InitTypeDef  EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line9;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStruct);
	//4.NVIC	在CPU内核里，不用开时钟
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

uint16_t num=0;
int main()
{
	OLED_Init();
	EXTI_Demo();

	while(1)
	{
		OLED_ShowNum(1,1,num++,4);
		
		//进入睡眠模式，CPU时钟关闭，其他时钟和外设不受影响。只是代码不会继续向下运行，SRAM和外设寄存器的数据都还在。
		__WFI();
	}
}


//5.中断函数
void EXTI9_5_IRQHandler(void)
{
//	num++;
	//每次进了中断函数，执行逻辑后，建议关闭中断标志位
	EXTI_ClearITPendingBit(EXTI_Line9);
}
