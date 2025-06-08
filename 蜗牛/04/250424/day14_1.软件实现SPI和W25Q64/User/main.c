#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "W25Q64.h"
//д������
//��ȡ����
//1.д���ʱ�򣬲����� 1-0 0���ܱ��1
//2.д�볬��256byte
//3.�����Ժ󣬶�ȡ���ݣ����Ƿ���1
//4.д��󣬵����Ƿ�ʧ����
//5.����ʱ���Ƿ���Կ�ҳ
int main()
{
	OLED_Init();//��ʼ����Ļ
	W25Q64_Init();
	SectorErase(0x00FF00);
	PageProgram(0x00FF00,0xA9);
	OLED_ShowHexNum(1,1,ReadData(0x00FF00),2);
	
	while(1)
	{
		
	}
	
}
