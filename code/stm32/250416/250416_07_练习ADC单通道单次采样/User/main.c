#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "ADC_Converter.h"


int main()
{
	OLED_Init();
	ADC_Converter_Init();
	uint16_t val = 0;
	float v = 0 ;
	while(1)
	{
		//错误点3：采集到的数据要放到while循环中
		val = getConverval();
		v =(float)val*3.3/4096;
		OLED_ShowNum(2,1,v,1);
		OLED_ShowNum(2,3,(uint32_t)(v*100)%100,2);
		OLED_ShowString(2,2,".");
		OLED_ShowNum(1,1,val,4);
		
	}
}
