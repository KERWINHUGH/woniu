#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "W25Q64.h"
//写入数组
//读取数组
//1.写入的时候，不擦除 1-0 0不能变成1
//2.写入超过256byte
//3.擦除以后，读取数据，看是否都是1
//4.写入后，掉电是否丢失数据
//5.读的时候，是否可以跨页
int main()
{
	OLED_Init();//初始化屏幕
	W25Q64_Init();
	SectorErase(0x00FF00);
	PageProgram(0x00FF00,0xA9);
	OLED_ShowHexNum(1,1,ReadData(0x00FF00),2);
	
	while(1)
	{
		
	}
	
}
