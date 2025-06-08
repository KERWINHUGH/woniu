#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "DMA_M2M.h"

uint8_t arr0[4] = {0x00,0x01,0x02};
uint8_t arr1[4] = {0};
int main()
{
	
	OLED_Init();
	DMA_M2MInit();

	while(1)
	{
		DMA_Cmd(DMA1_Channel1,DISABLE);
		//普通模式下，DMA_InitStruct.DMA_BufferSize的值将会递减，变为0后不在变化
		//循环模式下,DMA_InitStruct.DMA_BufferSize的值变为0后又将恢复成配置结构体时设置的值
		DMA_SetCurrDataCounter(DMA1_Channel1,4);
		DMA_Cmd(DMA1_Channel1,ENABLE);
		arr0[0]++;
		arr0[1]++;
		arr0[2]++;

		
		Delay_s(1);
		OLED_ShowNum(1,1,arr0[0],2);
		OLED_ShowNum(2,1,arr0[1],2);
		OLED_ShowNum(3,1,arr0[2],2);
		
		OLED_ShowNum(1,5,arr1[0],2);
		OLED_ShowNum(2,5,arr1[1],2);
		OLED_ShowNum(3,5,arr1[2],2);
	}
}
