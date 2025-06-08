#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/*************************************
*目标：读写后背寄存器：10个16位寄存器，共20个字节
*
*
*************************************/

int main()
{
	OLED_Init();
	
	//1.通过设置寄存器RCC_APB1ENR的PWREN和BKPEN位来打开电源和后备接口的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	
	//2.电源控制寄存器(PWR_CR)的DBP位来使能对后备寄存器和RTC的访问。
	PWR_BackupAccessCmd(ENABLE);
	
	//3.读写操作
	//BKP_WriteBackupRegister(BKP_DR1, 0x0606);
	

	while(1)
	{
		OLED_ShowHexNum(1,1,BKP_ReadBackupRegister(BKP_DR1),4);
	}
}
