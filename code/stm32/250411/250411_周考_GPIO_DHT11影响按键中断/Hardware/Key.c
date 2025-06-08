#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "DHT11.h"

int8_t num = 25;
extern TemHum NowTemHum;
void Key_Init(void)
{
		//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//2.配置PB1和PB11
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，默认输入高电平
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1  | GPIO_Pin_11;//配置PB1的线路和PB11的线路
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//3.配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
	//4.配置EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line1 | EXTI_Line11;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	//5.配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn ;//配置PB1的通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	//错误点4：配置NVIC通道时 ，不能放到一起
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;//配置PB11的通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
}
void EXTI1_IRQHandler(void)
{
	//判断是否为EXTI1_IRQn中断状态
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		//按键B1被按下，读取到一个0
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
		{
			Delay_ms(20);//第一次按下后，防止抖动
			//按键稳定时，一直等待按键松开
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
			Delay_ms(20);//防止松开后的抖动
			num++;
			//OLED_ShowNum(1,5,NowTemHum.Tem_Integer,2);
			OLED_ShowSignedNum(2,5,num,4);
		if(NowTemHum.Tem_Integer > num)
		{
			LED1_On();
		}else
		{
			LED1_Off();
		}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
//!!!!!!!!错误点5：！！！！中断函数名字不能写错，不能少写或者多写字母！！！！！！！！！！否则会导致其他中断也无法执行
void EXTI15_10_IRQHandler(void)
{
	//判断是否为EXTI1_IRQn中断状态
	if(EXTI_GetITStatus(EXTI_Line11) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
		{
			Delay_ms(20);//第一次按下后，防止抖动
			//按键稳定时，一直等待按键松开
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
			Delay_ms(20);//防止松开后的抖动
			num--;
		//OLED_ShowNum(1,5,NowTemHum.Tem_Integer,2);
		OLED_ShowSignedNum(2,5,num,4);
		if(NowTemHum.Tem_Integer > num)
		{
			LED1_On();
		}else
		{
			LED1_Off();
		}
		}
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}
