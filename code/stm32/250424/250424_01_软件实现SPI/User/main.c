#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "SPI_Model.h"
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
//	//先擦除
//	W25Q64_SectorErase(0x00FF00);
//	
//	uint8_t array[256] = {0};
//	for(uint16_t i = 0; i<256; i++)
//	{
//		array[i] = 0x01+i;
//	}
//	
//	W25Q64_PageProgramArr(0x00FF00,array,256);
	
	W25Q64_PageProgram(0x010000,0xBB);
	
	uint8_t arr[300] ={0};
	W25Q64_ReadArr(0x00FF00,arr,257);
	
	OLED_ShowHexNum(1,1,arr[0],2);
	OLED_ShowHexNum(1,4,arr[1],2);
	OLED_ShowHexNum(1,7,arr[2],2);
	OLED_ShowHexNum(2,1,arr[253],2);
	OLED_ShowHexNum(2,4,arr[254],2);
	OLED_ShowHexNum(2,7,arr[255],2);
	
	OLED_ShowHexNum(3,1,arr[256],2);
	OLED_ShowHexNum(3,4,arr[257],2);
	OLED_ShowHexNum(3,7,arr[258],2);
	

	while(1)
	{

	}
}
