#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	//1.��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//2.����
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//�������룬Ĭ�Ͼ�������ĸߵ�ƽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

//�ж���һ�����������ˣ���������ˣ��ͷ��ض�Ӧ�����֣����û���κΰ�������������0
uint8_t getKeyPressNum(void)
{
	uint8_t num = 0;
	
	//�������B1�������ˣ�����һ��0
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		//��һ�ΰ���֮�󣬷�ֹ����
		Delay_ms(20);
		//�����Ѿ��ȶ��ˣ��ȴ���һ������Ϊֹ
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		//��ֹ�ɿ���Ķ���
		Delay_ms(20);
		
		num = 1;
	}
	
	//�������B11�ϵ�Key������2
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		//��һ�ΰ���֮�󣬷�ֹ����
		Delay_ms(20);
		//�����Ѿ��ȶ��ˣ��ȴ���һ������Ϊֹ
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		//��ֹ�ɿ���Ķ���
		Delay_ms(20);
		
		num = 2;
	}
	
	
	return num;
}
