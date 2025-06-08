#include "stm32f10x.h"                  // Device header
#include "Delay.h"

GPIO_InitTypeDef GPIO_InitStruct;
//��ʼ��DHT11
void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

//�л�Ϊ���ģʽ,ÿ�ε���ʼ����ʱ�򣬻��߿�ʼ�����ʱ��������֤IO��·�Ǹߵ�ƽ
void DHT11_SetPP(void)
{
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//��ʼ�Ǹߵ�ƽ
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

//�л�Ϊ����ģʽ
void DHT11_SetIPU(void)
{
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

//������STM32������һ��������Ϣ
void DHT11_Req(void)
{
	//1.�л�Ϊ���ģʽ
	DHT11_SetPP();
	//2.��������͵�ƽ����18ms
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	Delay_ms(20);
	//3.����������20-40us
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	Delay_us(30);
}

//DHT11����Ӧ��������Ϣ
//����յ���DHT11��Ӧ��Ϣ������һ��SUCCESS��1�������û���յ�������ERROR��0��
uint8_t DHT11_Resp(void)
{
	//1.�л�������ģʽ
	DHT11_SetIPU();
	//2.��ȡ��ʪ�ȴ���������Ӧ����
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==0)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==0);//�ȵ��ӻ��ӵ͵�ƽ������
		return SUCCESS;
	}
	else
	{
		return ERROR;
	}
}

//��ȡһ���ֽڵ�����byte��DHT11�����Ƿ����ݣ�DHT11���������Ǹ�λ����
uint8_t DHT11_GetByteData(void)
{
	uint8_t data = 0x00;//0000 0000                  ����Է�1111 0000     
	
	for(uint8_t i = 0 ;i < 8 ; i++)
	{
		//1.�ȴ�һ���ߵ�ƽ���ȴ�һ���͵�ƽ
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==1);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==0);
		//2.�ӳ�35us
		Delay_us(35);
		//3.��ȡ��ƽ״̬,�����������1����ʾDHT11��������һ��1
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ==1)
		{
		    data |= (0x80>>i);//���Ҫ��һ������ĳһλ���1������λ���䡣|=��Ӧ��λ
		}
	}
	
	return data;
}

//�ܵĻ�ȡ���ݵķ���








