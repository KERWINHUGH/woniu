#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "PWM.h"

//��ʼ���������
void Motor_Init(void)
{
	PWM_Init();
		//1.��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;//�����������������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

//���������ǰ
void Left_Forward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}
//����������
void Left_Backward(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
//�������ֹͣ
void Left_Stop(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}
//���������ٶ�----[-99,99]
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

