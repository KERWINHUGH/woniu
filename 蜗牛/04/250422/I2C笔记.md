* 两根通信线Serial Clock  Serial Data
* 同步、半双工
* 带数据应答
* 支持总线挂载多设备

## I2C

#### 基本介绍

I2C（Inter IC Bus，简称I2C或IIC）是由Philips公司开发的一种通用数据总线，目前应用非常广泛。本课程主要是OLED和MPU6050为例进行讲解。

| **名称** |       **引脚**       | **双工** | **时钟** |        **电平**         | **设备** |
| :------: | :------------------: | :------: | :------: | :---------------------: | :------: |
|  USART   |        TX、RX        |  全双工  |   异步   |          单端           |  点对点  |
|   I2C    |       SCL、SDA       |  半双工  |   同步   |    单端  高低电平0 1    |  多设备  |
|   SPI    | SCLK、MOSI、MISO、CS |  全双工  |   同步   |          单端           |  多设备  |
|   CAN    |     CAN_H、CAN_L     |  半双工  |   异步   | 差分两根线的电压差，0 1 |  多设备  |
|   USB    |        DP、DM        |  半双工  |   异步   |          差分           |  点对点  |

#### 硬件规定

I2C总线支持一主多从和多主多从模式，我们主要讲一主多从模式。STM32作为主机，其它模块OLED和MPU6050作为从机。

所以我们主要学习的是I2C一主多从模式下主机的通信方式。

1. 主机引出两根总线，分别是SCL和SDA，SCL就是时钟线，SDA是数据线。
2. 时钟线SCL由主机控制，在一主多从模式下，从机只能被动读取SCL上的高低电平信号。**主机的SCL可以使用推挽输出模式。但协议规定，SCL要使用开漏输出模式+上拉电阻的模式。**
3. 数据线SDA需要输出和输入，为了确保不短路（如果主机输出高电平，从机输出低电平就会短路）。**SDA也使用开漏输出模式。GPIO在开漏输出模式下，可以输入。**
4. 在SCL和SDA上都接一个4.7K欧的上拉电阻以后，I2C默认就是高电平，主机对SCL有绝对控制权，主机在SCL线上要输出低电平时就拉低SCL，要输出高电平时就输出电阻态。
5. 主要在SDA上输出高电平和低电平同SCL。
6. 由于SDA要负责主机给从机发数据，还要负责从机给主机发数据，所以从机也可能会改变SDA的电平。如果从机发送0，就拉低SDA电平，如果从机要发送1，就输出高阻态。

![image-20231206104250725](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503142322202.png)

#### 基本时序单元

起始条件：SCL高电平期间，SDA从高电平切换到低电平

终止条件：SCL高电平期间，SDA从低电平切换到高电平

![image-20231206104555009](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503142322542.png)

（1）主机发送一个字节，从机接收一个数据

SCL低电平期间，主机将数据位依次放到SDA线上（高位先行），然后释放SCL，从机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次，即可发送一个字节。

![image-20231206104609398](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503142322535.png)

（2）从机发送一个数据，主机接收一个字节

SCL低电平期间，从机将数据位依次放到SDA线上（高位先行），然后释放SCL，主机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次，即可接收一个字节（主机在接收之前，需要释放SDA）。

![image-20231206104633858](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503142322504.png)

（3）发送应答

主机在接收完一个字节之后，在下一个时钟发送一位数据，数据0表示应答，数据1表示非应答。

所有的应答中，都是0表示应答，1表示非应答（每次发送和接收结束后，都会把SDA放手--拉到高电平）



![image-20231206161835536](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503142322584.png)

（4）接收应答

主机在发送完一个字节之后，在下一个时钟接收一位数据，判断从机是否应答，数据0表示应答，数据1表示非应答（主机在接收之前，需要释放SDA）。

![image-20231206161854463](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503142322898.png)





![image-20250314171652643](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503142322994.png)





#### 代码



````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
/**
  使用GPIO模拟I2C时序，和MPU6050进行通信
  1.先用软件GPIO模拟一次,SCL=B10  SDA=B11
  2.后面用32自带的硬件再写一次
*/

//初始化GPIO,注意两个点
//1.I2C必须使用开漏  
//2.默认情况下，开始的时候，SCL+SDA都是高电平
//3.STM32的官方允许配置成输出模式的情况下，允许输入。输入模式下，不允许输出
//  我们配置成开漏，所以兼顾了输入和输出
void I2C_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//不是输出1，而是断开接地的开关，被外接的电阻拉高到高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

//SCL写入数据--时钟线一直在主机控制之下，从机只会读SCL，没资格写SCL
void I2C_ModelWriteSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,data);
	Delay_us(5);
}

//SDA写入数据
void I2C_ModelWriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,data);
	Delay_us(5);
}

//SDA读取数据
uint8_t I2C_ModelReadSDA()
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(5);
	return data;
}

//1.主机开始通信:初始，SCL和SDA都是高电平，SCL是高的情况下，如果拉低SDA，表示开始
void I2C_ModelStart(void)
{
	I2C_ModelWriteSDA(1);
	I2C_ModelWriteSCL(1);
	
	I2C_ModelWriteSDA(0);
	I2C_ModelWriteSCL(0);
}

//2.主机发数据（8位）

//3.主机要等从机一个应答位，0表示应答 

//4.主机接收从机发送的数据（8位）

//5.主机给从机一个应答位0表示应答 

//6.主机结束通信


````



## MPU6050

### 1.往MPU6050写入数据测试



![image-20250317143226745](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503171432917.png)



````c
//往MPU6050的指定寄存机，写入指定值
void MPU6050_WriteData(uint8_t registerAddress,uint8_t data)
{
	I2C_ModelStart();
	I2C_ModelSentByte(0xD0);//7位地址：1101 000  读写位：0
	I2C_ModelReceiveACK();
	
	I2C_ModelSentByte(registerAddress);
	I2C_ModelReceiveACK();
	
	I2C_ModelSentByte(data);
	I2C_ModelReceiveACK();
	
	I2C_ModelStop();
}
````

### 2.从MPU6050读取值

![image-20250317155317997](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202503171553200.png)

测试读取寄存器whoami

`````
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "I2C_Model.h"
int main()
{	
	//初始化OLED屏
	OLED_Init();
	
	I2C_ModelInit();
	
	I2C_ModelStart();
	I2C_ModelSentByte(0xD0);//0x68 1101000+0
	I2C_ModelReceiveACK();
	
	I2C_ModelSentByte(0x75);
	I2C_ModelReceiveACK();
	
	I2C_ModelStart();
	I2C_ModelSentByte(0xD1);//0x68 1101000+1=11010001=0xD1
	I2C_ModelReceiveACK();
	
	uint8_t whoami = I2C_ModelReceiveByte();
	I2C_ModelSentACK(1);
	
	I2C_ModelStop();
	OLED_ShowBinNum(1,1,whoami,8);
	OLED_ShowHexNum(2,1,whoami,2);
	
	while(1)
	{
		
	}
}




`````

### 3.完整代码

I2C_Model.c

````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
/**
软件模拟I2C协议
注意：时钟线任何操作都是以低电平结束，除非是整个通信结束，才以高电平结束
*/


//初始化GPIO引脚PB10-SCL  PB11-SDA
void I2C_ModelInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//开始的时候默认给一个高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

//SCL只需要写，不需要读
void I2C_ModelWriteSCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,data);
	Delay_us(5);
}

//SDA 写
void I2C_ModelWriteSDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,data);
	Delay_us(5);
}

//SDA 读
uint8_t I2C_ModelReadSDA(void)
{
	uint8_t data = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(5);
	return data;
}

//主机发开始信号,除了结束信号外，其他所有情况下，方法结束的时候，SCL都是拉低的
void I2C_ModelStart(void)
{
	I2C_ModelWriteSDA(1);//先写SDA，防止SCL高的情况下，拉高SDA是结束信号
	I2C_ModelWriteSCL(1);
	
	//在SCL高电平的情况，拉低SDA，表示开始信号
	I2C_ModelWriteSDA(0);
	I2C_ModelWriteSCL(0);
}

//主机发终止信号
void I2C_ModelStop(void)
{
	I2C_ModelWriteSDA(0);

	//SCL默认都是低电平结束	，只有终止信号是高电平结束
	I2C_ModelWriteSCL(1);
	I2C_ModelWriteSDA(1);
}

//主机发送一个字节//   //1101 0000=0xD0
void I2C_ModelSentByte(uint8_t data)
{
	for(uint8_t i = 0; i < 8 ; i++)
	{
		//1.SDA放一个bit
		I2C_ModelWriteSDA(data & (0x80 >>i));
		
		//2.SCL时钟线拉高
		I2C_ModelWriteSCL(1);
		
		//3.给从机读
		
		//4.SCL时钟线拉低
		I2C_ModelWriteSCL(0);
	}
	
}

//主机接收ACK应答,
uint8_t I2C_ModelReceiveACK(void)
{
	//1.释放SDA，给从机操作
	I2C_ModelWriteSDA(1);
	
	//2.从机在SCL低的时候，放一个数据
	
	//3.拉高SCL
	I2C_ModelWriteSCL(1);
	
	//4.读取SDA
	uint8_t ack = I2C_ModelReadSDA();
	
	//每次SCL都以低电平结束
	I2C_ModelWriteSCL(0);
	
	return ack;
}

//主机接收一个字节
uint8_t I2C_ModelReceiveByte(void)
{
	uint8_t data = 0x00;//00000000
	//1.释放SDA，给从机操作
	I2C_ModelWriteSDA(1);
	
	for(uint8_t i = 0; i < 8 ; i++)
	{
		//2.从机在SDA放一个数据
		
		//3.主机拉高SCL
		I2C_ModelWriteSCL(1);
		
		//4.主机读取SDA,如果主机读到了1
		if(I2C_ModelReadSDA())
		{
			data |= (0x80 >>i);
		}
		
		//5.主机拉低SCL，都以低电平结束
		I2C_ModelWriteSCL(0);
	}
	return data;
}

//主机给从机一个ACK应答//I2C_ModelWriteSCL(0);
void I2C_ModelSentACK(uint8_t ack)
{
	//1.主机在SDA上放一个应答位
	I2C_ModelWriteSDA(ack);
	
	//2.SCL拉高
	I2C_ModelWriteSCL(1);
	
	//3.从机读取应答
	
	//4.SCL拉低结束操作
	I2C_ModelWriteSCL(0);
}








````



I2C_Model.h

````c
#ifndef __I2C_MODEL_H
#define __I2C_MODEL_H

void I2C_ModelInit(void);
void I2C_ModelStart(void);
void I2C_ModelStop(void);
void I2C_ModelSentByte(uint8_t data);
uint8_t I2C_ModelReceiveACK(void);
uint8_t I2C_ModelReceiveByte(void);
void I2C_ModelSentACK(uint8_t ack);

#endif

````



MPU6050.c

````c
#include "stm32f10x.h"                  // Device header
#include "I2C_Model.h"
#include "Mpu6050.h"
//往MPU6050的指定寄存器，写入指定值
void MPU6050_WriteData(uint8_t registerAddress,uint8_t data)
{
	I2C_ModelStart();
	I2C_ModelSentByte(0xD0);//7位地址：1101 000  读写位：0
	I2C_ModelReceiveACK();
	
	I2C_ModelSentByte(registerAddress);
	I2C_ModelReceiveACK();
	
	I2C_ModelSentByte(data);
	I2C_ModelReceiveACK();
	
	I2C_ModelStop();
}

//从MPU6050的指定寄存器，读取数据
uint8_t MPU6050_ReadData(uint8_t registerAddress)
{
	//前面写的部分，只是为了，让MPU6050的指针指向registerAddress的位置
	I2C_ModelStart();
	I2C_ModelSentByte(0xD0);//7位地址：1101 000  读写位：0
	I2C_ModelReceiveACK();
	
	I2C_ModelSentByte(registerAddress);
	I2C_ModelReceiveACK();
	
	//重新开始，才是真正要读
	I2C_ModelStart();
	I2C_ModelSentByte(0xD1);//7位地址：1101 000  读写位：1   1101 0001
	I2C_ModelReceiveACK();
	
	uint8_t data = I2C_ModelReceiveByte();
	I2C_ModelSentACK(1);//发0就是应答，发1就是不应答
	
	I2C_ModelStop();
	return data;
}

//初始化并设置MPU6050
void MPU6050_Init(void)
{
	I2C_ModelInit();
	MPU6050_WriteData(PWR_MGMT_1,0x01);
	MPU6050_WriteData(PWR_MGMT_2,0x00);
	MPU6050_WriteData(SMPLRT_DIV,0x02);
	MPU6050_WriteData(CONFIG,0x06);
	MPU6050_WriteData(GYRO_CONFIG,0x18);
	MPU6050_WriteData(ACCEL_CONFIG,0x18);
}

void getMpu6050Data(MPU6050_Data *mpu6050Data)
{
	mpu6050Data->ACCX = MPU6050_ReadData(ACCEL_XOUT_H) <<8 | MPU6050_ReadData(ACCEL_XOUT_L);
	mpu6050Data->ACCY = MPU6050_ReadData(ACCEL_YOUT_H) <<8 | MPU6050_ReadData(ACCEL_YOUT_L);
	mpu6050Data->ACCZ = MPU6050_ReadData(ACCEL_ZOUT_H) <<8 | MPU6050_ReadData(ACCEL_ZOUT_L);
	mpu6050Data->GroyX = MPU6050_ReadData(GYRO_XOUT_H) <<8 | MPU6050_ReadData(GYRO_XOUT_L);
	mpu6050Data->GroyY = MPU6050_ReadData(GYRO_YOUT_H) <<8 | MPU6050_ReadData(GYRO_YOUT_L);
	mpu6050Data->GroyZ = MPU6050_ReadData(GYRO_ZOUT_H) <<8 | MPU6050_ReadData(GYRO_ZOUT_L);
	
}




````



MPU6050.h

````c
#ifndef __MPU6050_H
#define __MPU6050_H
//配置有关的寄存器
#define PWR_MGMT_1 0x6B  //电源管理器1
#define PWR_MGMT_2 0x6C  //电源管理器2
#define SMPLRT_DIV 0x19  //采样分频
#define CONFIG 0x1A      //总配置
#define GYRO_CONFIG 0x1B //角速度的配置
#define ACCEL_CONFIG 0x1C//加速度的配置


//读取的寄存器
#define ACCEL_XOUT_H 0x3B//X加速度的高八位
#define ACCEL_XOUT_L 0x3C//X加速度的低八位
#define ACCEL_YOUT_H 0x3D//Y加速度的高八位
#define ACCEL_YOUT_L 0x3E//Y加速度的低八位
#define ACCEL_ZOUT_H 0x3F//Z加速度的高八位
#define ACCEL_ZOUT_L 0x40//Z加速度的低八位

#define GYRO_XOUT_H 0x43//X角速度的高八位
#define GYRO_XOUT_L 0x44//X角速度的低八位
#define GYRO_YOUT_H 0x45//Y角速度的高八位
#define GYRO_YOUT_L 0x46//Y角速度的低八位
#define GYRO_ZOUT_H 0x47//Z角速度的高八位
#define GYRO_ZOUT_L 0x48//Z角速度的低八位

typedef struct{
	int16_t ACCX;
	int16_t ACCY;
	int16_t ACCZ;
	int16_t GroyX;
	int16_t GroyY;
	int16_t GroyZ;
} MPU6050_Data;

void MPU6050_Init(void);
void MPU6050_WriteData(uint8_t registerAddress,uint8_t data);
uint8_t MPU6050_ReadData(uint8_t registerAddress);
void getMpu6050Data(MPU6050_Data *mpu6050Data);


#endif

````



````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Mpu6050.h"

MPU6050_Data mpu6050Data;
int main()
{	
	//初始化OLED屏
	OLED_Init();
	
	MPU6050_Init();

	
	while(1)
	{
		getMpu6050Data(&mpu6050Data);
		OLED_ShowSignedNum(1,1,mpu6050Data.ACCX,5);
		OLED_ShowSignedNum(1,8,mpu6050Data.GroyX,5);
		
		OLED_ShowSignedNum(2,1,mpu6050Data.ACCY,5);
		OLED_ShowSignedNum(2,8,mpu6050Data.GroyY,5);
		
		OLED_ShowSignedNum(3,1,mpu6050Data.ACCZ,5);
		OLED_ShowSignedNum(3,8,mpu6050Data.GroyZ,5);
	}
}
//16次逐次逼近 



````















