#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"

//SRAM的地址：从0x2000 0000开始
//FLASH的地址：从0x0800 0000开始,程序存在flash从这里开始
//外设的地址PERIPH_BASE：从0x40000000开始

//ADC1的起始地址0x4001 2400
uint8_t a = 0;
uint8_t b = 1;
const uint8_t c = 10;

int main()
{
	OLED_Init();
	OLED_ShowHexNum(1,1,(uint32_t)&a,8);//0x2000 0000
	OLED_ShowHexNum(2,1,(uint32_t)&b,8);//0x0000 0001
	OLED_ShowHexNum(3,1,(uint32_t)&c,8);//0x0800 0740
	OLED_ShowHexNum(4,1,(uint32_t)&ADC1->DR,8);//0x4001 244C 
	while(1)
	{

		
	}
}
