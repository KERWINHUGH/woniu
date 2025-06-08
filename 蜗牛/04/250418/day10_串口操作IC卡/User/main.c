#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"
#include "IC.h"
//1.计算校验和
//2.怎么发
//3.怎么接收

uint8_t ReadCardArr[8] = {0x01,0x08 ,0xA1 ,0x20 ,0x00 ,0x01 ,0x00 ,0x00};


int main()
{
	OLED_Init();//初始化屏幕
	Serial_Init();
	/*****************计算校验和，并发送读卡号的数组***************/
	Sent_ICode(ReadCardArr);
	
	
	while(1)
	{
		
	}
	
}
