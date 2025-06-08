#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"


/***************************************
* 1.���д������д��PRԤ��Ƶ����RLR��װ�ؼĴ���
* 2.�������Ź�
*	3.��һ��ι��
* 4.ѭ��ȥι��
****************************************/

void iwdg_config(void)
{
	//1.��ʱ�ӣ�����д���ο�оƬ�ο��ֲ�6.2.9
	//��������˿��Ź���LSI����ǿ�ƴ�
	
	//2.���д������д��PRԤ��Ƶ����RLR��װ�ؼĴ���
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);//16
	IWDG_SetReload(2500-1);//2500,12λ�Ĵ��������ֵΪ4096
	//3.�������Ź�
	IWDG_Enable();
	
	//4.��һ���������Ź���ιһ�ι�
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
		//4.ι��
		IWDG_ReloadCounter();
	}
}
