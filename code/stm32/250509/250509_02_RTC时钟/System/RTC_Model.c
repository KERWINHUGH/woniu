#include "stm32f10x.h"
#include "RTC_Model.h"

void RTC_ModelInit(void)
{
	//1.设置寄存器RCC_APB1ENR的PWREN和BKPEN位，使能电源和后备接口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	
	//2.设置寄存器PWR_CR的DBP位，使能对后备寄存器和RTC的访问。
	PWR_BackupAccessCmd(ENABLE);
	
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x0606)
	{
		//3.启动LSE(32.768KHz),给RTCCLK使用
	RCC_LSEConfig(RCC_LSE_ON);
	
	//4.判断LES是否启动成功，因为LSE时钟较慢，HSE很快，得确定RCC启动成功
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET );
	
	//5.将LSE时钟作为RTCCLK的时钟源使用
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	
	//6.启动RTC时钟
	RCC_RTCCLKCmd(ENABLE);
	
	//7.先同步一次APB1和RTCCLK,即等待上述步骤1234和步骤56一起结束
	RTC_WaitForSynchro();
	
	//8.开始配置预分配PRL   时间计数器CNT    
	//必须配置RTC_CRL寄存器中的CNF位，使RTC进入配置模式后，才能写入RTC_PRL、RTC_CNT、RTC_ALR寄存器
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32768-1);
	//对任何寄存器的写操作，都需要上一次写寄存器结束
	RTC_WaitForLastTask();
	RTC_SetCounter(1746848067);
	
	BKP_WriteBackupRegister(BKP_DR1,0x0606);
	
//	RTC_WaitForLastTask();
//	RTC_SetAlarm(3000-1);
	}else
	{
			RTC_WaitForSynchro();
	}
	
}
//设置RTC闹钟中断
void SetAlarmInterrupt(uint32_t alarmValue)
{
	//对任何寄存器的写操作，都需要上一次写寄存器结束
	RTC_WaitForLastTask();
	//设置闹钟的值
	RTC_SetAlarm(alarmValue);
	
	
	//对任何寄存器的写操作，都需要上一次写寄存器结束
	RTC_WaitForLastTask();
	//开启RTC闹钟中断
	RTC_ITConfig(RTC_IT_ALR,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStruct);
}
