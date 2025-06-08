#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"
#include "IC.h"


uint8_t ReadCardArr[8] = {0x01,0x08,0xA1,0x20,0x00,0x01,0x00,0x00};

int main()
{
	OLED_Init();
	Serial_Init();	
	//Serial_Byte(0x31);
	/******************计算校验和，并发送读卡号的数组***************/
	CheckVolidataVal(ReadCardArr);
	Serial_Arr(ReadCardArr,ReadCardArr[1]);
	
	while(1)
	{
		
	}
}
