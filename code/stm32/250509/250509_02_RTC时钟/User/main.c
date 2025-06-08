#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "RTC_Model.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"


/*************************************
* 1.������ʱ������ʾ����Ļ��
* 2.�ϵ�󣬻������������ʱ�仹�ܼ�����
* 3.������ʱ�����������
*************************************/

int main()
{
	OLED_Init();
	RTC_ModelInit();
	//�����жϷ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//��һ�����ӣ��ڵ�ǰʱ���10����������������ж�
	SetAlarmInterrupt(RTC_GetCounter() + 10);
	
	OLED_ShowString(1,1,"    -  -  ");
	OLED_ShowString(2,1,"  :  :  ");

	while(1)
	{
		time_t now = RTC_GetCounter() + 8*3600;//�õ�ʱ�����׶�ʱ�䣬�õ�ʱ�����8Сʱ�õ���ǰʱ��
			
		struct tm* nowtime = localtime(&now);
		
		OLED_ShowNum(1,1,nowtime->tm_year+1900,4);
		OLED_ShowNum(1,6,nowtime->tm_mon+1,2);
		OLED_ShowNum(1,9,nowtime->tm_mday,2);
		
		OLED_ShowNum(2,1,nowtime->tm_hour,2);
		OLED_ShowNum(2,4,nowtime->tm_min,2);
		OLED_ShowNum(2,7,nowtime->tm_sec,2);
		
		
//		char *timestr ;
//		strftime(timestr,200,"%Y/%m/%d %H:%M:%S\n",nowtime);


//		OLED_ShowString(1,1,timestr);
			OLED_ShowNum(3,1, RTC_GetCounter(),10);
	}
}

//RTC���жϺ���
void RTC_IRQHandler()
{
	if(RTC_GetITStatus(RTC_IT_ALR) == SET)
	{
		OLED_ShowString(4,1,"alarm");
		
		//������ӱ�־λ
		RTC_ClearITPendingBit(RTC_IT_ALR);
	}
}