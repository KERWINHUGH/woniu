#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/*************************************
*Ŀ�꣺��д�󱳼Ĵ�����10��16λ�Ĵ�������20���ֽ�
*
*
*************************************/

int main()
{
	OLED_Init();
	
	//1.ͨ�����üĴ���RCC_APB1ENR��PWREN��BKPENλ���򿪵�Դ�ͺ󱸽ӿڵ�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	
	//2.��Դ���ƼĴ���(PWR_CR)��DBPλ��ʹ�ܶԺ󱸼Ĵ�����RTC�ķ��ʡ�
	PWR_BackupAccessCmd(ENABLE);
	
	//3.��д����
	//BKP_WriteBackupRegister(BKP_DR1, 0x0606);
	

	while(1)
	{
		OLED_ShowHexNum(1,1,BKP_ReadBackupRegister(BKP_DR1),4);
	}
}
