#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "W25Q64.h"

/**************************
**	1.д������
**	2.��ȡ����
**	3.д��ʱ��������������1->0,0�ɲ�����->1				����:���� 1->0,������0->1
**	4.д�볬��256�ֽڣ���ȡ��ҳ����һҳ�Ƕ���			���ۣ�д�볬��256���ֽ�ʱ���������ֽڻ��ҳ�״�����д��
**	5.�����󣬶�ȡ���ݣ��Ƿ���1									���ۣ�����FF
**	6.д��󣬵����Ƿ�ʧ����										���ۣ����Զ�ȡ������֮ǰ������
**	7.����ʱ���Ƿ���Կ�ҳ��������һҳд����ȥ��		���ۣ����Զ�ȡ����һҳ������
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
