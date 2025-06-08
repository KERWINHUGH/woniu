#include "stm32f10x.h"                  // Device header
#include "PVD.h"
#include "OLED.h"

void PVD_ConfigInit(void)
{
	//1.��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	//2.����PVD
	PWR_PVDLevelConfig(PWR_PVDLevel_2V9);//���õ�Դ�����������ѹ��2.9V��
	PWR_PVDCmd(ENABLE);
	
	//��һ������ʱ����Ҫ����жϱ�־λ�������ϵ�ͽ����жϣ�Ӱ���߼�
	PWR_ClearFlag(PWR_FLAG_PVDO);
	
	//3.�����жϣ��ο�4.2.2����ѹ�������ж�ʱ�½��ش�������ѹ�½�����ֵ�µ��ж�ʱ���������ش���
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line16;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	//4.NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = PVD_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

}

void PVD_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line16) == SET)
	{
		OLED_ShowString(1,1,"PVD");
		EXTI_ClearITPendingBit(EXTI_Line16);
	}
}
