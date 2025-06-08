#include "stm32f10x.h"                  // Device header

/*
	STM32F103C8一共有48个引脚，
	官方给这些引脚进行了编号：A0-A15  B0-B15  C0-C15 D0-D15
	
	程序怎么控制硬件：程序往寄存器中写0/1，寄存器的01，就是硬件的开关
	32位二进制能转换成8位16进制
	案例1：给A0引脚一个高电平，点亮一个灯，以直接操作寄存器方式点亮一个灯
	代码中使用16进制，手册中寄存器是2进制，每4个2进制可以转换为1个16 进制，32位2进制可以转换为8位16进制
*/
//int main()
//{
//	//1.首先设置时钟，设置时钟先看设备挂载在哪个总线上（APB1,APB2）
//	//开启时钟GPIOC---APB2
//	RCC->APB2ENR = 0x00000010;//启动APB2上面GPIOC的时钟
//	//2.配置这个设备GPIOA的设备----GPIO_CR(ctrl register)
//	//0-7	8-15
//	GPIOC->CRH = 0x00300000;//配置成推挽输出：00；通用推挽输出模式：11
//	//3.使用这个设备GPIOA设备----GPIOx_ODR(output data register)
//	//操作GPIOC
//	GPIOC->ODR = 0x00000000;//PA9应该是0x0000 0200只使用后
//}

//int main()
//{
//	//1.首先设置时钟，设置时钟先看设备挂载在哪个总线上（APB1,APB2）
//	//然后找到专门开RCCAPB2设备的时钟
//	//开APB2-GPIOA的时钟，GPIOA挂载在APB2总线上的RCC_APB2
//	//参考6.3.7 RCC寄存器描述
//	RCC->APB2ENR = 0x00000004;//启动APB2上面GPIOA的时钟
//	//2.配置这个设备GPIOA的设备----GPIO_CR(ctrl register)
//	//PA0是低位----0~7是低寄存器，8~15是高寄存器PA9是高位
//	//参考8.2.1端口配置低寄存器(GPIOx_CRL)(x=A..E)
//	GPIOA->CRL = 0x00000003;//配置成推挽输出：00；通用推挽输出模式：11
//	//3.使用这个设备GPIOA设备----GPIOx_ODR(output data register)
//	//参考8.2.4端口输出数据寄存器(GPIOx_ODR)(X=A..E)
//	GPIOA->ODR = 0x00000001;//PA9应该是0x0000 0200只使用后
//}

