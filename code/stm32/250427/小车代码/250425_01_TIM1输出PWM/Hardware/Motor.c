#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "PWM.h"
#include "EncoderInterface.h"
#include "Timer.h"

/**
*TB6612:PWM控制速度		IN1	IN2控制方向
*AIN1->A0	AIN2->A1		PWM1----PA8----左轮
*BIN1->A4	BIN2->A5		PWM2----PA9----右轮
*/
void Motor_Init(void)
{
	//1.初始化PWM
	PWM_Init();
	//2.初始化控制电机方向的4个引脚
	//PA0----AIN1----右轮
	//PA1----AIN2----右轮
	//PA4----BIN1----左轮
	//PA5----BIN2----左轮
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//两个引脚输出模式配置为推挽输出，给电机驱动芯片提供高低电平控制方向
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

//控制左轮向前	AIN1->H	AIN2->L
void Left_Forward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
//控制左轮向后
void Left_Backward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}
//控制左轮停止
void Left_Stop(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}
//设置左轮速度	速度范围[-99，99],输入等于0停止，大于零向前，小于零向后
void Left_SetSpeed(int16_t speed )
{
	if(speed == 0)
	{
		Left_Stop();
	}else if(speed > 0)
	{
		Left_Forward();
		TIM_SetCompare1(TIM1,speed);
	}else if(speed < 0)
	{
		Left_Backward();
		TIM_SetCompare1(TIM1,-speed);
	}
}

//右轮向前
void Right_Forward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}
//右轮向后
void Right_Backward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
//右轮停止
void Right_Stop(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
//设置右轮速度
void Right_SetSpeed(int16_t speed)
{
	if(speed == 0)
	{
		Right_Stop();
	}else if(speed > 0)
	{
		Right_Forward();
		TIM_SetCompare2(TIM1,speed);
	}else if(speed < 0)
	{
		Right_Backward();
		TIM_SetCompare2(TIM1,-speed);
	}
}
