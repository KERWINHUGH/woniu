#include "stm32f10x.h"
#include "IIC_Model.h"
#include "Delay.h"


/*
	stm32f103��IIC1��IIC2�������߶�Ӧ������
	IIC1:	SCL->PB6	SDA->PB7
	IIC2:	SCL->PB10 SDA->PB11
	
	���ģ�����stm32f103��IIC2
*/			

//��ʼ��IIC��������
void IIC_ModelInit(void)
{
	//1.����IIC2��SCL��SDA����
	
	//1.1��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//1.2����GPIO�ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//1.3����GPIOģʽʱ��SCL��SDA��Ҫ����Ϊ��©ģʽ
	//��ΪSCLʱ�ٷ��涨��Ҫʹ�ÿ�©ģʽ����SDA��Ҫ����ҲҪ���������Ϊ����ģʽ�Ļ��������������Ϊ���ģʽ�Ļ���������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//1.3��SCL��ʼ��Ϊ�ߵ�ƽ
	//�״��1����ʼ������ʱ��Ӧ�ý�SCL��SDA������
//	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
	
}

void IIC_SetSCL(uint8_t BitValue)
{	
	//�����1��BitValue��ֵӦ��ǿתΪ��BitAction���ͣ������߸�����ʱ���͸���BitAction���͵Ĳ���
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	//�״��2���������ƽ��Ӧ���ӳ�5us
	Delay_us(5);
}

void IIC_WriteSDA(uint8_t BitValue)
{
	//�����1��BitValue��ֵӦ��ǿתΪ��BitAction���ͣ������߸�����ʱ���͸���BitAction���͵Ĳ���
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	//�״��2���������ƽ��Ӧ���ӳ�5us
	Delay_us(5);
}

uint8_t IIC_ReadSCL(void)
{
	//�״��3����ȡ���ݺ󣬻���Ҫ���ӳ�5us����˲���ֱ�ӷ��ض�ȡ��������
//	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
	Delay_us(5);
	return data;
}

uint8_t IIC_ReadSDA(void)
{
	//�״��3����ȡ���ݺ󣬻���Ҫ���ӳ�5us����˲���ֱ�ӷ��ض�ȡ��������
//	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(5);
	return data;
}

//IIC��ʼ�ź�
void IIC_Start(void)
{
	//2.д��ʼ�ź�
	//2.1������SDA����SDA����Ĭ��״̬��������SDA����Ϊ��Ϊ������ֹͣ�źţ�ֹͣ�ź���SCL��SDA��Ϊ�ͣ�SCL�����ߣ�SDA������
	IIC_WriteSDA(Bit_SET);
	
	//2.2������SCL����SCL����Ĭ��״̬
	IIC_SetSCL(Bit_SET);	

	//2.3������SDA����SCL���ڸߵ�ƽ��ʱ������SDA====����ʼ�ź�
	IIC_WriteSDA(Bit_RESET);
	
	//2.4�ٽ�SCL����
	IIC_SetSCL(Bit_RESET);
	
	//�״��4����ʼ�ͽ����źŲ���Ҫ���ӳ�
//	//2.5�ӳ�5us
//	Delay_us(5);
	
}


//IIC�����ź�
void IIC_Stop(void)
{
	//֪ʶ�㣺SCLĬ��ǰ��Ĳ������Ե͵�ƽ��������߲��ø�SCLǰ������
	//3.д�����ź�
	//3.1������SCL����SCL����Ĭ��״̬��������SDA����Ϊ��Ϊ�������ڿ�ʼ�źţ���ʼ�ź���SCL��SDA��Ϊ��ʱ��������SDA,������SCL
//	IIC_SetSCL(Bit_RESET);
	
	//3.2������SDA����SDA����Ĭ��״̬
	IIC_WriteSDA(Bit_RESET);
	
	//3.3�Ƚ�SCL����
	IIC_SetSCL(Bit_SET);
	
	//3.4�ٽ�SDA���ߣ���SCL���ڸߵ�ƽ��ʱ������SDA====�������ź�
	IIC_WriteSDA(Bit_SET);
	
	//�״��4����ʼ�ͽ����źŲ���Ҫ���ӳ�
//	//3.5�ӳ�5us
//	Delay_us(5);
}

//IIC����һλACK
void IIC_SendACK(uint8_t Ack)
{
	//4.д����ACK
	//֪ʶ�㣺SCLĬ��ǰ��Ĳ������Ե͵�ƽ������������Բ���д��SCL����
	//4.1����SCL��Ĭ�Ͽ�ʼSCL�Ǹߵ�ƽ
//	IIC_SetSCL(Bit_RESET);
	
	//4.2����һλACK
	IIC_WriteSDA(Ack);
	
	//4.3����SCL���ôӻ�ȥ��ȡ�������͵�����
	IIC_SetSCL(Bit_SET);	
	
	//�״��5��IICЭ��涨��SCLĬ�ϲ������Ե͵�ƽ��������������Ҫ�Ƚ�SCL����
	IIC_SetSCL(Bit_RESET);
	
}

//IIC����һ���ֽ�
void IIC_SendByte(uint8_t data)
{
	//5.����һ���ֽڣ���λ���С�
	//5.1д��һ��8�ε�ѭ������ʾ����һ���ֽڣ�ÿ�η���һ������λ
	for(uint8_t i ; i < 8; i++)
	{
		//5.2����SCL��Ĭ�Ͽ�ʼSCL�Ǹߵ�ƽ
		//֪ʶ�㣺SCLĬ��ǰ��Ĳ������Ե͵�ƽ������������Բ���д��SCL����
//		IIC_SetSCL(Bit_RESET);
		
		//5.3����һλACK
		//5.3.1�Ƚ�Ҫ���͵���������iλ	data <<= i;
		//5.3.2�ٽ����ƺ��������0x80����λ�ڲ�������ÿ�ζ�����data����iλ������λ������ʵ�ָ�λ����
		IIC_WriteSDA((0x80 >> i) & data);
		
		//5.4����SCL���ôӻ�ȥ��ȡ�������͵�����
		IIC_SetSCL(Bit_SET);
		
		//�״��5��IICЭ��涨��SCLĬ�ϲ������Ե͵�ƽ��������������Ҫ��SCL����
		IIC_SetSCL(Bit_RESET);
	}
}

//IIC����һλACK
uint8_t IIC_ReceiveACK(void)
{
	//6.д����ACK
	//6.1��������֮ǰ������Ӧ���ͷ�SDA
	IIC_WriteSDA(Bit_SET);
	
	//6.2��������SCL��׼����ȡ�ӻ����͵�����
	IIC_SetSCL(Bit_SET);
	
	//6.3�ӻ�����SCL���ӻ�������ACK,�ӻ�����SCL
	
	//�״��7���ӻ��������SCL�����Բ���ȥ�ȴ�SCL���ı䣬ֱ��ȥ���ӻ����ݾͿ�����
	//�Ͽγ����в���Ҫ�ȴ�SCL�ɸߵ����ٵ���
//	//6.4�ȴ�SDA�ϵ�����
//	//6.4.1�ȴ�SCL������
//	while(IIC_ReadSCL());
//	
//	//6.4.2�ȴ�SCL������
//	while(!IIC_ReadSCL());
	
	//6.4.3��ȡ������SDA�ϵ�����
	//�״��5��IICЭ��涨��SCLĬ�ϲ������Ե͵�ƽ�������������ڽ��������ݺ���Ҫ�Ƚ�SCL����
//	return IIC_ReadSDA();
	uint8_t data = IIC_ReadSDA();
	
	IIC_SetSCL(Bit_RESET);
	
	return data;
}

//IIC����һ���ֽ�
uint8_t IIC_RecevieByte(void)
{
	//�״��6�������ͷ�SDAֻ��Ҫ�ڽ���֮ǰ�ͷ�һ�μ���
	//7.3��������֮ǰ������Ӧ���ͷ�SDA
	IIC_WriteSDA(Bit_SET);
	//7.д�������ݣ���λ����
	//7.1�ȶ���һ��8λ���������ڽ������ݲ�����
	uint8_t data = 0x00;
	
	//7.2дһ��8�ε�ѭ�������ڽ���һ���ֽڣ�ÿ�ν���һλ
	for(uint8_t i =0; i < 8; i++)
	{
		//�״��6�������ͷ�SDAֻ��Ҫ�ڽ���֮ǰ�ͷ�һ�μ���
//	//7.3��������֮ǰ������Ӧ���ͷ�SDA
//	IIC_WriteSDA(Bit_SET);
	
		//7.4��������SC��׼����ȡ�ӻ����͵�����
		IIC_SetSCL(Bit_SET);
		
		//7.5�ӻ�����SCL���ӻ�������ACK,�ӻ�����SCL
		
		//�״��7���ӻ��������SCL�����Բ���ȥ�ȴ�SCL���ı䣬ֱ��ȥ���ӻ����ݾͿ�����
		//�Ͽγ����в���Ҫ�ȴ�SCL�ɸߵ����ٵ���
//		//7.6�ȴ�SDA�ϵ�����
//		//7.6.1�ȴ�SCL������
//		while(IIC_ReadSCL());
//		
//		//7.6.2�ȴ�SCL������
//		while(!IIC_ReadSCL());
		
		//7.6.3�ж϶�ȡ���������Ƿ�Ϊ1
		if(IIC_ReadSDA())
		{
			//7.6.4�����ȡ��SDA�ϵ�����λ����1��������λ�ŵ�data������Ӧλ�ã������ùܣ���Ϊdata��ʼ��ÿλ����0
			//7.6.4.1�Ƚ�����0x80����iλ
			//7.6.4.2��λ��Ľ�����ǵ�i�ν��յ���1����ʱ����λ��ĵ�ǰλ�����ʹ��λ���������ŵ�data��
			//����㣺�����ڱ��ʽ֮��ʹ������
//		data  |= 0x80 >> i;
			data  |= (0x80 >> i);
		}
		//�״��5��IICЭ��涨��SCLĬ�ϲ������Ե͵�ƽ�������������ڽ��������ݺ���Ҫ�Ƚ�SCL����
		IIC_SetSCL(Bit_RESET);
	}
	//7.7��ȡ������SDA�ϵ�����
	return data;
}
