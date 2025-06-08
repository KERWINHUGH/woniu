#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"
#include "Encoder.h"

/**
要求一：舵机要求周期是20ms，即定时器频率为1/20ms = 50Hz
所以，设置PSC = 72; ARR = 20000; 计算输出的频率fre = 72MHz / 72 /20000 = 50Hz
要求二：一个周期内高电平时间是0.5ms和2.5ms
当高电平时间为0.5ms时，转动角度是0度，----占空比计算：CCR / ARR = 0.5 / 20  得到CCR = 500
当高电平时间为2.5ms时，转动角度是180度，----占空比计算：CCR / ARR = 2.5 / 20  得到CCR = 2500
*/

//参数angle在0~180之间
void SetSG50Angle(int16_t angle)
{
	//角度：0~180，对应CCR：500~2500
	TIM_SetCompare1(TIM2,500 + 2000 * angle / 180);	//设置捕获比较寄存器	
}

int main()
{
	OLED_Init();
	PWM_Init();
	Encoder_Init();
	
	while(1)
	{
//		for(uint16_t i = 0;i <180; i++)
//		{
//			SetSG50Angle(i);
//			Delay_ms(20);
//		}
		
		OLED_ShowSignedNum(1,1,num,3);
		if(num > 0 && num <= 180)
		{
			SetSG50Angle(num);
		}
	}
}
