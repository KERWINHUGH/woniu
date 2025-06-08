#include "stm32f10x.h"                  // Device header
#include "TIMER.h"
#include "OLED.h"
#include "ADC_Sample.h"
#include "USART.h"

//TIM2每10s产生一次中断
void TIM3_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//2.设置定时器时钟源
	TIM_InternalClockConfig(TIM3);
	
	//3.时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;		//2000 0/2000 = 10s
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;	//72000/36000 = 2000Hz
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	//4.设置主模式+主模式输出触发
	TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
	
	//5.开启定时器
	TIM_Cmd(TIM2,ENABLE);
}

//TIM2每10s产生一次中断
void TIM2_Init(void)
{
	//1.开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//2.设置定时器时钟源
	TIM_InternalClockConfig(TIM2);
	
	//3.时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;		//20000/2000 = 10s
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36000-1;	//72000/36000 = 2000Hz
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	//3.5清除定时器开始的一次CNT溢出，取消不用，让开始就采集一次数据
	//TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	//4.定时器中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//5.NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitTStruct;
	NVIC_InitTStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitTStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitTStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTStruct);
	
	//6.开启定时器
	TIM_Cmd(TIM2,ENABLE);
}

uint8_t num = 0;;
//中断读取ADC转换的光敏和热敏的数据，然后传到电脑的串口上
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		//ADC读取操作
		//使用DMA后，采集到的数据都存在数组中
		//OLED_ShowHexNum(1,1,sample[0],4);
		
		uint8_t h = (sample[1]>>8)&0xFF;
		uint8_t l = sample[1]&0xFF;
	
		OLED_ShowHexNum(2,1,h,4);
		OLED_ShowHexNum(3,1,l,4);
		
		
		//处理ADC采集到的数据
		if(sample[0] != 0 && sample[1] != 0)
		{
			Serial_SendHalfWord(sample[0]);
			Serial_SendHalfWord(sample[1]);		
		}

		
		//测试10s产生一次中断
		num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

//初始化定时器2和定时器3
void TIM23_Init(void)
{
	TIM2_Init();
	TIM3_Init();
}
