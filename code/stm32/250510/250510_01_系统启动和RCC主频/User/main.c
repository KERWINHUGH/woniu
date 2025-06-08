#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PVD.h"

int main()
{
	OLED_Init();
	PVD_ConfigInit();

	while(1)
	{
			
	}
}
