#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"


//����˯��ģʽ��GPIO�ǲ��Ṥ���ģ���Ҫһ���ж�ȥ���ѣ��޸Ĵ�������жϺ���Ҫ��ס������RESET�����ٵ��keil��¼��Ȼ����Ҫ���־Ϳ�����¼��ȥ
void EXTI_Demo()
{
	//1.GPIO�����ò����жϵ�����	PA0	���ó�����ģʽ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//2.AFIO	��GPIO����ӳ�䵽EXTI�Ķ�Ӧ����·�ϣ�ֻ��GPIO���޷������жϵģ�PA0----EXTI��Line0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);//��GPIOA0��ӳ�䵽EXTI	Line0��
	//3.EXTI
	//EXTI��ʱ�Ӳ������ã�EXTI��CPU�ⲿ���ⲿ�жϲ�������ʱ�ӣ�CPU������ͣ��ģʽ��ʱ��Ҳ��رգ��ⲿ�жϻỽ��CPU
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTI,ENABLE);
	EXTI_InitTypeDef  EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line9;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStruct);
	//4.NVIC	��CPU�ں�����ÿ�ʱ��
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
		
		//����˯��ģʽ��CPUʱ�ӹرգ�����ʱ�Ӻ����費��Ӱ�졣ֻ�Ǵ��벻������������У�SRAM������Ĵ��������ݶ����ڡ�
		__WFI();
	}
}


//5.�жϺ���
void EXTI9_5_IRQHandler(void)
{
//	num++;
	//ÿ�ν����жϺ�����ִ���߼��󣬽���ر��жϱ�־λ
	EXTI_ClearITPendingBit(EXTI_Line9);
}
