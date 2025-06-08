#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
#include "PWM.h"


int16_t num = 0;
void Encoder_Init(void)
{
	//开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//1.GPIO
	GPIO_InitTypeDef GPIO_InitSTruct;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitSTruct.GPIO_Pin = GPIO_Pin_2  | GPIO_Pin_1;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitSTruct);
	//2.AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
	//3.EXTI
	EXTI_InitTypeDef EXTI_InitSTruct;
	//只有外部中断需要配线路，线路有20条	GPIO---Line0~Line15	其他Line16 Line17	Line18	Line19
	EXTI_InitSTruct.EXTI_Line = EXTI_Line2 | EXTI_Line1;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitSTruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置4个比特位，0~15，为2时，抢占优先级占两位0~3，响应优先级占两位0~3
	//4.NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	//通道有很多条，外部中断和内部中断都需要配置NVIC通道，内部中断不需要配置线路
	//NVIC配置的中断通道交给CPU，让CPU通过配置好的不同通道处理不同的中断函数（ISR中断服务例程）
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;	
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
	
}

//5.中断处理EXTI0函数,startup_stm32f10x.md.s汇编文件中定义
void EXTI2_IRQHandler()
{
	//1.判断中断来源，防止其他信号干扰
	if(EXTI_GetITStatus(EXTI_Line2) == SET)
	{
		if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) == 0 )&& (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1))
		{	
			num++;
		}
		//2.中断处理完以后，必须清除中断标志位，否则中断信号会不断的循环
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

//5.中断处理EXTI1函数,startup_stm32f10x.md.s汇编文件中定义
void EXTI1_IRQHandler()
{
	//1.判断中断来源，防止其他信号干扰
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		//判断PA0是不是下降沿，并且PA1是
		if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0 )&& (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) == 1))
		{	
			num--;
		}
		//2.中断处理完以后，必须清除中断标志位，否则中断信号会不断的循环
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
