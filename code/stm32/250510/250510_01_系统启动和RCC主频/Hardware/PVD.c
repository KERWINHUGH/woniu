#include "stm32f10x.h"                  // Device header
#include "PVD.h"
#include "OLED.h"

void PVD_ConfigInit(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	//2.配置PVD
	PWR_PVDLevelConfig(PWR_PVDLevel_2V9);//配置电源管理监控输入电压（2.9V）
	PWR_PVDCmd(ENABLE);
	
	//第一次启动时，需要清除中断标志位，避免上电就进入中断，影响逻辑
	PWR_ClearFlag(PWR_FLAG_PVDO);
	
	//3.配置中断，参考4.2.2，电压上升的中断时下降沿触发，电压下降到阈值下的中断时，是上升沿触发
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
