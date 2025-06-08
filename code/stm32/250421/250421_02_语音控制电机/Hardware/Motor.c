#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "PWM.h"

//初始化电机引脚
void Motor_Init(void)
{
	PWM_Init();
		//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;//电机正反的两个引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

//电机左轮向前
void Left_Forward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}
//电机左轮向后
void Left_Backward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
//电机左轮停止
void Left_Stop(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}
//设置左轮速度----[-99,99]
void Left_SetSpeed(int16_t speed)
{
	if(speed == 0)Left_Stop();
	else if(speed > 0)
	{
		Left_Forward();
		TIM_SetCompare1(TIM2,speed);
	}else if(speed < 0)
	{
		Left_Backward();
		TIM_SetCompare1(TIM2,-speed);
	}
}

