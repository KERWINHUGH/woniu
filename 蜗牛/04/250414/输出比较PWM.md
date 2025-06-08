## 1.PWM

* PWM ：脉冲宽度调制，输出高低电平

* 关注：频率 = CKPSC/(PSC+1)/(ARR+1)

​          占空比：CCR/(ARR+1)

* PWM1的公式：CNT<CCR输出高电平  CNT>=CCR 输出低电平

原理：

![img](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504141217981.png)

## 2.开发要注意的几个点

### 1.比较单元

* TIM_OCStructInit 函数可以帮我初始化结构体成员

* 为什么需要TIM_OCStructInit 帮我初始化？因为有一些成员是高级定时器才需要设置的
* 模式：TIM_OCMode_PWM1，TIM_OCMode_PWM2公式不一样
* 极性：将输出波形换相
* ![img](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504141407517.png)

````c
	//4.输出比较单元OC  output compare
	//因为输出比较单元结构体有4个成员只给高级定时器用的，所以TIM_OCStructInit函数专门给所有成员赋初值
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);//初始化一个输出比较结构体
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//CNT<CCR输出1，CNT>=CCR输出0
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出波形极性不变
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 20;//占空比
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);//给TIM2的OC1配置输出比较
````



### 2.GPIO设置要用复用



````c
	//5.GPIO--TIM2_CH1 = PA0
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);


````



![img](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504141407640.png)

## 3.呼吸灯

`````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
int main()
{
	OLED_Init();//初始化屏幕
	PWM_Init();//fre=10000   duty=20%
	while(1)
	{
		for(uint16_t i =5 ; i < 1000 ; i++)
		{
			TIM_SetCompare1(TIM2,i);//设置捕获比较寄存器
			Delay_ms(1);
		}
		
		for(uint16_t i =999 ; i >= 5 ; i--)
		{
			TIM_SetCompare1(TIM2,i);//设置捕获比较寄存器
			Delay_ms(1);
		}
	}
	
}

`````



````c
#include "stm32f10x.h"                  // Device header

/**
   目标：使用TIM2生成一个PWM波形，频率为10000，占空比为20%
   CK_PSC=72M     PSC=72    ARR=100  Fre = 72M/72*100 = 10000Hz  Duty: CCR=20/ARR = 20%
*/

void PWM_Init(void)
{
	//1.RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.配置TIM的输入来源-内部72M
	TIM_InternalClockConfig(TIM2);
	
	//3.时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStruct.TIM_Period = 1000 - 1; //ARR
	TIM_TimeBaseStruct.TIM_Prescaler = 72 -1 ;//PSC
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x00;//给高级定时器用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	
	//4.输出比较单元OC  output compare
	//因为输出比较单元结构体有4个成员只给高级定时器用的，所以TIM_OCStructInit函数专门给所有成员赋初值
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);//初始化一个输出比较结构体
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//CNT<CCR输出1，CNT>=CCR输出0
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出波形极性不变
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;//占空比
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);//给TIM2的OC1配置输出比较
	
	//5.GPIO--TIM2_CH1 = PA0
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//5.启动
	TIM_Cmd(TIM2,ENABLE);
}
````







## 4.舵机

![img](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504141444498.png)



>* PWM的周期20ms
>* fre = 1/20ms = 50Hz，72MHz/PSC/ARR = 50Hz
>* PSC=72   ARR=20000

````c
#include "stm32f10x.h"                  // Device header

/**
   目标：使用TIM2生成一个PWM波形，频率为10000，占空比为20%
   CK_PSC=72M     PSC=72    ARR=100  Fre = 72M/72*100 = 10000Hz  Duty: CCR=20/ARR = 20%
*/

void PWM_Init(void)
{
	//1.RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.配置TIM的输入来源-内部72M
	TIM_InternalClockConfig(TIM2);
	
	//3.时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStruct.TIM_Period = 20000 - 1; //ARR
	TIM_TimeBaseStruct.TIM_Prescaler = 72 -1 ;//PSC
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x00;//给高级定时器用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	
	//4.输出比较单元OC  output compare
	//因为输出比较单元结构体有4个成员只给高级定时器用的，所以TIM_OCStructInit函数专门给所有成员赋初值
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);//初始化一个输出比较结构体
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//CNT<CCR输出1，CNT>=CCR输出0
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出波形极性不变
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;//占空比
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);//给TIM2的OC1配置输出比较
	
	//5.GPIO--TIM2_CH1 = PA0
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//5.启动
	TIM_Cmd(TIM2,ENABLE);
}

````

main.c

````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Encoder.h"
/**
	要求一：20ms的脉冲 ，意味着频率=1/20ms=50Hz
	所以：PSC=72  ARR=20000  计算fre = 72M/72*20000 = 50Hz
	要求二：高电平时间0.5ms的时候，转动角度0      0.5/20 = CCR/20000    CCR = 500
	        
	       高电平时间2.5ms的时候，转动角度180     2.5/20 = CCR/20000    CCR = 2500
*/

//传一个角度进来，舵机就会转动多少度
void setSG50Angle(uint8_t angle)
{
	TIM_SetCompare1(TIM2,500+2000*angle/180);
}

int main()
{
	OLED_Init();//初始化屏幕
	Encoder_Init();//初始化编码器
	PWM_Init();//fre=10000   duty=20%
	
	
	while(1)
	{
		OLED_ShowSignedNum(1,1,num,4);
		
		if(num>0 && num<=180)
		{
			setSG50Angle(num);
		}
	}
	
}



````





## 5.电机



![img](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202504141754765.png)

代码：

````c
#include "stm32f10x.h"                  // Device header

/**
   目标：使用TIM2生成一个PWM波形，频率为10000，占空比为20%
   CK_PSC=72M     PSC=72    ARR=100  Fre = 72M/72*100 = 10000Hz  Duty: CCR=20/ARR = 20%
*/

void PWM_Init(void)
{
	//1.RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//2.配置TIM的输入来源-内部72M
	TIM_InternalClockConfig(TIM2);
	
	//3.时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStruct.TIM_Period = 100 - 1; //ARR
	TIM_TimeBaseStruct.TIM_Prescaler = 72 -1 ;//PSC
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x00;//给高级定时器用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	
	//4.输出比较单元OC  output compare
	//因为输出比较单元结构体有4个成员只给高级定时器用的，所以TIM_OCStructInit函数专门给所有成员赋初值
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);//初始化一个输出比较结构体
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//CNT<CCR输出1，CNT>=CCR输出0
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出波形极性不变
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;//占空比
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);//给TIM2的OC1配置输出比较
	
	//5.GPIO--TIM2_CH1 = PA0
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//5.启动
	TIM_Cmd(TIM2,ENABLE);
}
````



````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

//20ma

int main()
{
	OLED_Init();//初始化屏幕
	PWM_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1  | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//调整方向
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	TIM_SetCompare1(TIM2,90);//调整速度
	
	while(1)
	{
		
	}
	
}



````

