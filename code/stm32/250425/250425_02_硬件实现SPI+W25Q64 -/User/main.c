#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "W25Q64.h"

/**************************
**	1.写入数组
**	2.读取数组
**	3.写入时，不擦除，试试1->0,0可不可以->1				结论:可以 1->0,不可以0->1
**	4.写入超过256字节，读取当页和下一页是多少			结论：写入超过256个字节时，超过的字节会从页首处覆盖写入
**	5.擦除后，读取数据，是否都是1									结论：都是FF
**	6.写入后，掉电是否丢失数据										结论：可以读取到掉电之前的数据
**	7.读的时候是否可以跨页，先在下一页写入再去读		结论：可以读取到下一页的数据
**/	

int main()
{
	OLED_Init();
	W25Q64_Init();
	W25Q64_SectorErase(0x00FF00);
	
	uint8_t arr[3] = {0x11,0x22,0x33};
	W25Q64_WiteByteArr(0X00FF00,arr,3);

	
	uint8_t array[3] = {0};
	W25Q64_ReadBtyeArr(0x00FF00,array,3);
	
	OLED_ShowHexNum(1,1,array[0],2);
	OLED_ShowHexNum(1,4,array[1],2);
	OLED_ShowHexNum(1,7,array[2],2);
	while(1)
	{

	}
}
