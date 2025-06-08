#include "stm32f10x.h"                  // Device header
#include "Car_Dsc.h"
#include "PWM.h"

void CarDirectionInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitSTruct;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTruct.GPIO_Pin = GPIO_Pin_2  | GPIO_Pin_3 | GPIO_Pin_4  | GPIO_Pin_5 ;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitSTruct);
}

void Left_Forward(void)
{
	CarDirectionInit();
	//调整电机转动方向----向前
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}
void Left_Backward(void)
{
	CarDirectionInit();
	//调整电机转动方向----向后
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
//速度参数：0~100
void Left_Speed(uint16_t speed)
{
	TIM_SetCompare1(TIM2,speed);	//设置捕获比较寄存器	调整电机速度
}

void Right_Forward(void)
{
	CarDirectionInit();
	//调整电机转动方向----向前
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}
void Right_Backward(void)
{
	CarDirectionInit();
	//调整电机转动方向----向后
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
//速度参数：0~100
void Right_Speed(uint16_t speed)
{
		TIM_SetCompare2(TIM2,speed);	//设置捕获比较寄存器	调整电机速度
}