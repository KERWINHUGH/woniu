#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"


/***************************************
* 1.解除写保护，写入PR预分频器和RLR重装载寄存器
* 2.启动看门狗
*	3.第一次喂狗
* 4.循环去喂狗
****************************************/

void iwdg_config(void)
{
	//1.开时钟，不用写，参考芯片参考手册6.2.9
	//如果启动了看门狗，LSI将被强制打开
	
	//2.解除写保护，写入PR预分频器和RLR重装载寄存器
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);//16
	IWDG_SetReload(2500-1);//2500,12位寄存器，最大值为4096
	//3.启动看门狗
	IWDG_Enable();
	
	//4.第一次启动看门狗就喂一次狗
	IWDG_ReloadCounter();
	
}

uint16_t num = 0;
int main()
{
	OLED_Init();
	iwdg_config();

	while(1)
	{
		OLED_ShowNum(1,1,num++,4);
		Delay_ms(1006);
		//4.喂狗
		IWDG_ReloadCounter();
	}
}
