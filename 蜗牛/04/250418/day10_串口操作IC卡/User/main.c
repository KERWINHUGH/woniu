#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"
#include "IC.h"
//1.����У���
//2.��ô��
//3.��ô����

uint8_t ReadCardArr[8] = {0x01,0x08 ,0xA1 ,0x20 ,0x00 ,0x01 ,0x00 ,0x00};


int main()
{
	OLED_Init();//��ʼ����Ļ
	Serial_Init();
	/*****************����У��ͣ������Ͷ����ŵ�����***************/
	Sent_ICode(ReadCardArr);
	
	
	while(1)
	{
		
	}
	
}
