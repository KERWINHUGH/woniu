#include "stm32f10x.h"
#include "IIC_Model.h"
#include "Delay.h"


/*
	stm32f103中IIC1和IIC2的两根线对应的引脚
	IIC1:	SCL->PB6	SDA->PB7
	IIC2:	SCL->PB10 SDA->PB11
	
	软件模拟的是stm32f103的IIC2
*/			

//初始化IIC引脚配置
void IIC_ModelInit(void)
{
	//1.配置IIC2的SCL和SDA引脚
	
	//1.1开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//1.2配置GPIO结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//1.3配置GPIO模式时，SCL和SDA都要配置为开漏模式
	//因为SCL时官方规定需要使用开漏模式，而SDA既要输入也要输出，配置为输入模式的话不能输出，配置为输出模式的话可以输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//1.3将SCL初始化为高电平
	//易错点1：初始化引脚时，应该将SCL和SDA均拉高
//	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
	
}

void IIC_SetSCL(uint8_t BitValue)
{	
	//警告点1：BitValue的值应该强转为（BitAction类型），或者给参数时，就给出BitAction类型的参数
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	//易错点2：设置完电平后，应该延迟5us
	Delay_us(5);
}

void IIC_WriteSDA(uint8_t BitValue)
{
	//警告点1：BitValue的值应该强转为（BitAction类型），或者给参数时，就给出BitAction类型的参数
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	//易错点2：设置完电平后，应该延迟5us
	Delay_us(5);
}

uint8_t IIC_ReadSCL(void)
{
	//易错点3：读取数据后，还需要先延迟5us，因此不能直接返回读取到的数据
//	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
	Delay_us(5);
	return data;
}

uint8_t IIC_ReadSDA(void)
{
	//易错点3：读取数据后，还需要先延迟5us，因此不能直接返回读取到的数据
//	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(5);
	return data;
}

//IIC开始信号
void IIC_Start(void)
{
	//2.写开始信号
	//2.1先拉高SDA，让SDA处于默认状态，先拉高SDA是因为，为了区别停止信号，停止信号是SCL和SDA都为低，SCL先拉高，SDA再拉高
	IIC_WriteSDA(Bit_SET);
	
	//2.2再拉高SCL，让SCL处于默认状态
	IIC_SetSCL(Bit_SET);	

	//2.3先拉高SDA，在SCL处于高电平的时候，拉低SDA====》开始信号
	IIC_WriteSDA(Bit_RESET);
	
	//2.4再将SCL拉低
	IIC_SetSCL(Bit_RESET);
	
	//易错点4：开始和结束信号不需要加延迟
//	//2.5延迟5us
//	Delay_us(5);
	
}


//IIC结束信号
void IIC_Stop(void)
{
	//知识点：SCL默认前面的操作都以低电平结束，这边不用给SCL前提条件
	//3.写结束信号
	//3.1先拉低SCL，让SCL处于默认状态，先拉低SDA是因为，为了区别于开始信号，开始信号是SCL和SDA都为高时，先拉低SDA,再拉低SCL
//	IIC_SetSCL(Bit_RESET);
	
	//3.2再拉低SDA，让SDA处于默认状态
	IIC_WriteSDA(Bit_RESET);
	
	//3.3先将SCL拉高
	IIC_SetSCL(Bit_SET);
	
	//3.4再将SDA拉高，在SCL处于高电平的时候，拉高SDA====》结束信号
	IIC_WriteSDA(Bit_SET);
	
	//易错点4：开始和结束信号不需要加延迟
//	//3.5延迟5us
//	Delay_us(5);
}

//IIC发送一位ACK
void IIC_SendACK(uint8_t Ack)
{
	//4.写发送ACK
	//知识点：SCL默认前面的操作都以低电平结束，这里可以不用写将SCL拉低
	//4.1拉低SCL，默认开始SCL是高电平
//	IIC_SetSCL(Bit_RESET);
	
	//4.2发送一位ACK
	IIC_WriteSDA(Ack);
	
	//4.3拉高SCL，让从机去读取主机发送的数据
	IIC_SetSCL(Bit_SET);	
	
	//易错点5：IIC协议规定：SCL默认操作都以低电平结束，故这里需要先将SCL拉低
	IIC_SetSCL(Bit_RESET);
	
}

//IIC发送一个字节
void IIC_SendByte(uint8_t data)
{
	//5.发送一个字节，高位先行。
	//5.1写出一个8次的循环，表示发送一个字节，每次发送一个数据位
	for(uint8_t i ; i < 8; i++)
	{
		//5.2拉低SCL，默认开始SCL是高电平
		//知识点：SCL默认前面的操作都以低电平结束，这里可以不用写将SCL拉低
//		IIC_SetSCL(Bit_RESET);
		
		//5.3发送一位ACK
		//5.3.1先将要发送的数据左移i位	data <<= i;
		//5.3.2再将左移后的数据与0x80进行位于操作，即每次都发送data左移i位后的最高位，就能实现高位先行
		IIC_WriteSDA((0x80 >> i) & data);
		
		//5.4拉高SCL，让从机去读取主机发送的数据
		IIC_SetSCL(Bit_SET);
		
		//易错点5：IIC协议规定：SCL默认操作都以低电平结束，故这里需要将SCL拉低
		IIC_SetSCL(Bit_RESET);
	}
}

//IIC接收一位ACK
uint8_t IIC_ReceiveACK(void)
{
	//6.写接收ACK
	//6.1接收数据之前，主机应该释放SDA
	IIC_WriteSDA(Bit_SET);
	
	//6.2主机拉高SCL，准备读取从机发送的数据
	IIC_SetSCL(Bit_SET);
	
	//6.3从机拉低SCL，从机发送数ACK,从机拉高SCL
	
	//易错点7：从机不会操作SCL，所以不能去等待SCL被改变，直接去读从机数据就可以了
	//上课程序中不需要等待SCL由高到低再到高
//	//6.4等待SDA上的数据
//	//6.4.1等待SCL被拉低
//	while(IIC_ReadSCL());
//	
//	//6.4.2等待SCL被拉高
//	while(!IIC_ReadSCL());
	
	//6.4.3读取并返回SDA上的数据
	//易错点5：IIC协议规定：SCL默认操作都以低电平结束，故这里在接收完数据后，需要先将SCL拉低
//	return IIC_ReadSDA();
	uint8_t data = IIC_ReadSDA();
	
	IIC_SetSCL(Bit_RESET);
	
	return data;
}

//IIC接收一个字节
uint8_t IIC_RecevieByte(void)
{
	//易错点6：主机释放SDA只需要在接收之前释放一次即可
	//7.3接收数据之前，主机应该释放SDA
	IIC_WriteSDA(Bit_SET);
	//7.写接收数据，高位接收
	//7.1先定义一个8位变量，用于接收数据并返回
	uint8_t data = 0x00;
	
	//7.2写一个8次的循环，用于接收一个字节，每次接收一位
	for(uint8_t i =0; i < 8; i++)
	{
		//易错点6：主机释放SDA只需要在接收之前释放一次即可
//	//7.3接收数据之前，主机应该释放SDA
//	IIC_WriteSDA(Bit_SET);
	
		//7.4主机拉高SC，准备读取从机发送的数据
		IIC_SetSCL(Bit_SET);
		
		//7.5从机拉低SCL，从机发送数ACK,从机拉高SCL
		
		//易错点7：从机不会操作SCL，所以不能去等待SCL被改变，直接去读从机数据就可以了
		//上课程序中不需要等待SCL由高到低再到高
//		//7.6等待SDA上的数据
//		//7.6.1等待SCL被拉低
//		while(IIC_ReadSCL());
//		
//		//7.6.2等待SCL被拉高
//		while(!IIC_ReadSCL());
		
		//7.6.3判断读取到的数据是否为1
		if(IIC_ReadSDA())
		{
			//7.6.4如果读取到SDA上的数据位的是1，将数据位放到data变量对应位置，否则不用管，因为data初始化每位就是0
			//7.6.4.1先将变量0x80右移i位
			//7.6.4.2移位后的结果就是第i次接收到的1，此时将移位后的当前位结果，使用位或运算符存放到data中
			//警告点：建议在表达式之间使用括号
//		data  |= 0x80 >> i;
			data  |= (0x80 >> i);
		}
		//易错点5：IIC协议规定：SCL默认操作都以低电平结束，故这里在接收完数据后，需要先将SCL拉低
		IIC_SetSCL(Bit_RESET);
	}
	//7.7读取并返回SDA上的数据
	return data;
}
