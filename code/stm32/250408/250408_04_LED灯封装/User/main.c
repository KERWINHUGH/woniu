#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"

int main()
{

	LED_Init();
	OLED_Init();
	
	//OLED_Clear();
	
	OLED_ShowChar(1,5,'A');//显示单个字符
	OLED_ShowString(2,1,"Hello");//显示字符串
	OLED_ShowNum(3,1,12345,5);//显示数字
	OLED_ShowSignedNum( 4,1,-100,3);//显示带负号数字
//	OLED_ShowHexNum( 1,1,100,2);//显示16进制	64 6*16+4 = 100
//	OLED_ShowBinNum( 2,1,100,8);//显示2进制		01100100
	while(1)
	{
		LED1_Turn();
		LED2_Turn();
		Delay_ms(500);
	}
	
}
