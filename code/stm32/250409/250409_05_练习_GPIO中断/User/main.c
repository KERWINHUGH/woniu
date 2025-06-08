#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"

uint8_t num = 0;

int main()
{
	OLED_Init();
	
	//1.设置GPIO----配置引脚
	//错误点1：外部中断，设置引脚应该为输入模式
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//2.设置AFIO----GPIO不能直接连接到EXTI线路上，需要使用AFIO将GPIO连接到EXTI的线路
	//错误点2：配置AFIO时，需要去GPIO.h里看哪个函数符合配置GPIO线路-----实际为GPIO_EXTILineConfig
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	//3.设置EXTI----配置GPIO的线路，使能这个线路，配置中断的类型，并配置触发这个外部中断的方式
	//不需要设置时钟
	//错误点3:初始化完结构体后，需要调用EXTI初始化函数
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	//4.设置NVIC----配置中断的通道，使能这个通道，设置中断的抢占优先级NVIC_IRQChannelPreemptionPriority（0~15），配置中断子优先级
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	while(1)
	{
		OLED_ShowNum(1,1,num,5);
	}
}

//5.编写中断函数
//错误点4：外部中断需要清理中断标志位
//错误点5：清除标志位函数的参数为配置好的EXTI的线路
void EXTI0_IRQHandler(void)
{
	num++;
	EXTI_ClearITPendingBit(EXTI_Line0);
}
