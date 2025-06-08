#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "SPI_Model.h"
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
//	//�Ȳ���
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
