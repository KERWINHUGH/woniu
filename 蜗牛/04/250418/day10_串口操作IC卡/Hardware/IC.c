#include "stm32f10x.h"                  // Device header
#include "IC.h"
#include <stdio.h>

//����У�鹫ʽ���ǴӰ��ĵ�һ���ֽڵ��ڰ�����һ���ֽڵ����ֵ�����ȡ��
//Ҳ���Ǵӵ�һ���ֽڵ������ڶ����ֽڵ����ֵ�����ȡ����
uint8_t checkVolidateValue(uint8_t *buf)
{
	uint8_t checksum = 0;
	for(uint8_t i = 0; i<(buf[1]-1) ; i++)
	{
		checksum^=buf[i];
	}
	buf[buf[1]-1] = ~checksum;//У��ͣ��ŵ���������һλ
	return buf[buf[1]-1];
}

//����ָ��
void Sent_ICode(uint8_t *arr)
{
	checkVolidateValue(arr);
	Serial_Arr(arr,arr[1]);
}


uint8_t message[100];//�յ�����Ϣ�����������

void dealReadCardTask(void);
//���յ����ݵ��жϺ��������ӽ��յ����ݣ�01 0C A1 20 00 04 00 0A DC EF F9 B7
void USART1_IRQHandler(void)
{
	//��̬�ı������ڷ�������ε��õ�ʱ�򣬿��Ա���֮ǰ��ֵ
	static uint8_t index = 0;//���������λ��
	static uint8_t len = 0; //Ҫ���յ�����ĳ���
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		//���շ��͹���������
		uint8_t data = USART_ReceiveData(USART1);
	
		//�������Ϊ1����ʾ�յ��˵ڶ������ݣ��ڶ������������ǳ��ȣ����԰����ݸ�ֵ��len
		if(index==1)
		{
			len = data;
		}
		
		//�յ�һ�����ݣ��ʹ�һ������
		message[index++] = data;
		
		//�������++�����õ����յ������ݳ��ȣ�˵������������ɣ��Ͱ�index��len�ָ�ȱʡĬ��ֵ����������߼�
		if(index==len)
		{
			index = 0;
			len = 0;
			//�����߼�,�����յ��Ĳ�ͬ��ָ����ò�ͬ�ĺ���ȥ��������
			if(message[2]==0xA1)//��ȡ����
			{
				dealReadCardTask();
				
			}else if (message[2]==0xA3)//��ȡ���ݿ�
			{
			
			}else if (message[2]==0xA4)//д���ݿ�
			{
			
			}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

//��ȡ���ţ����ص�ֵ��01 0C A1 20 00 04 00 0A DC EF F9 B7
void dealReadCardTask(void)
{
	//2 �ֽڿ�����+4 �ֽڿ���
	uint8_t cardType[2] = {0x00};
	uint8_t cardNum[4] = {0x00};
	
	//��ʦû����֤У���
	if(message[4] == 0x00)//���سɹ�
	{
		//��message����ĵ�5������λ�ÿ�ʼ������2��ֵ��cardType����
		memcpy(cardType,&message[5],2);
		memcpy(cardNum,&message[7],4);
		
		//1 4 7 
		for(uint8_t i = 0 ;i <2;i++)
		{
			OLED_ShowHexNum(1,1+(i*3),cardType[i],2);
		}
		
		for(uint8_t j = 0 ;j <4;j++)
		{
			OLED_ShowHexNum(2,1+j*3,cardNum[j],2);
		}
		
	}
	else
	{
	
	}
}







