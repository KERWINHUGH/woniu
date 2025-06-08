#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "RTC_Model.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"


/*************************************
* 1.年月日时分秒显示到屏幕上
* 2.断电后，或者重启后，这个时间还能继续走
* 3.年月日时分秒可以设置
*************************************/

int main()
{
	OLED_Init();
	RTC_ModelInit();
	//设置中断分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//第一次闹钟，在当前时间的10秒后启动，并进入中断
	SetAlarmInterrupt(RTC_GetCounter() + 10);
	
	OLED_ShowString(1,1,"    -  -  ");
	OLED_ShowString(2,1,"  :  :  ");

	while(1)
	{
		time_t now = RTC_GetCounter() + 8*3600;//得到时间是伦敦时间，得到时间加上8小时得到当前时间
			
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

//RTC的中断函数
void RTC_IRQHandler()
{
	if(RTC_GetITStatus(RTC_IT_ALR) == SET)
	{
		OLED_ShowString(4,1,"alarm");
		
		//清除闹钟标志位
		RTC_ClearITPendingBit(RTC_IT_ALR);
	}
}