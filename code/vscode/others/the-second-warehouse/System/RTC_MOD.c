#include "stm32f10x.h"
void RCT_CLOCK_Config(int32_t alarmvalue)
{
    RTC_WaitForLastTask();
    RTC_SetAlarm(alarmvalue); // 设置RTC闹钟时间
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT_ALR, ENABLE); //
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); // 使能RTC中断

}
void RTC_Config(void)
{
    // 系统复位后，RTC时钟默认关闭，需要先使能RTC时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE); // 使能RTC备份寄存器访问权限
    // 设置RTC时钟源为LSE
    if (BKP_ReadBackupRegister(BKP_DR1) != 0x0606)
    {
        RCC_LSEConfig(RCC_LSE_ON);
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET)
            ; // 等待LSE时钟稳定
        // 设置RTC时钟分频系数为32768
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);
        RTC_WaitForSynchro();

        RTC_WaitForLastTask();
        RTC_SetPrescaler(32768 - 1);
        RTC_WaitForLastTask();
        RTC_SetCounter(1746841967);
        BKP_WriteBackupRegister(BKP_DR1, 0x0606); // 保存配置

    }
    else
    {
        RTC_WaitForSynchro();
    }

    // 退出RTC配置模式
}