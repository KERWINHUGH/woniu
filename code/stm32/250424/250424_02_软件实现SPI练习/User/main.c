#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "W25Q64.h"

int main()
{
	OLED_Init();
	
	W25Q64_Init();
	
	SectorErase(0x00FF00);
	
	PageProgram(0x00FF00,0xB0);
	
	uint8_t data = ReadData(0x00FF00);
	
	OLED_ShowHexNum(1,1,data,2);

	while(1)
	{

	}
}
