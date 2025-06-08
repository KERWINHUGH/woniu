#include "stm32f10x.h"
#include "RTC_Model.h"

void RTC_ModelInit(void)
{
	//1.���üĴ���RCC_APB1ENR��PWREN��BKPENλ��ʹ�ܵ�Դ�ͺ󱸽ӿ�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	
	//2.���üĴ���PWR_CR��DBPλ��ʹ�ܶԺ󱸼Ĵ�����RTC�ķ��ʡ�
	PWR_BackupAccessCmd(ENABLE);
	
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x0606)
	{
		//3.����LSE(32.768KHz),��RTCCLKʹ��
	RCC_LSEConfig(RCC_LSE_ON);
	
	//4.�ж�LES�Ƿ������ɹ�����ΪLSEʱ�ӽ�����HSE�ܿ죬��ȷ��RCC�����ɹ�
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET );
	
	//5.��LSEʱ����ΪRTCCLK��ʱ��Դʹ��
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	
	//6.����RTCʱ��
	RCC_RTCCLKCmd(ENABLE);
	
	//7.��ͬ��һ��APB1��RTCCLK,���ȴ���������1234�Ͳ���56һ�����
	RTC_WaitForSynchro();
	
	//8.��ʼ����Ԥ����PRL   ʱ�������CNT    
	//��������RTC_CRL�Ĵ����е�CNFλ��ʹRTC��������ģʽ�󣬲���д��RTC_PRL��RTC_CNT��RTC_ALR�Ĵ���
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32768-1);
	//���κμĴ�����д����������Ҫ��һ��д�Ĵ�������
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
//����RTC�����ж�
void SetAlarmInterrupt(uint32_t alarmValue)
{
	//���κμĴ�����д����������Ҫ��һ��д�Ĵ�������
	RTC_WaitForLastTask();
	//�������ӵ�ֵ
	RTC_SetAlarm(alarmValue);
	
	
	//���κμĴ�����д����������Ҫ��һ��д�Ĵ�������
	RTC_WaitForLastTask();
	//����RTC�����ж�
	RTC_ITConfig(RTC_IT_ALR,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStruct);
}
