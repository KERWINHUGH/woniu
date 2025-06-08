# 1.SysTick定时器

## 1.1 SysTick定时器概述

​		在以前,大多操作系统需要一个硬件定时器来产生操作系统需要的滴答中断,作为整个系统的时基。例如,为多个任务许以不同数目的时间片,确保没有一个任务能霸占系统;或者把每个定时器周期的某个时间范围赐予特定的任务等,还有操作系统提供的各种定时功能,都与这个滴答定时器有关。因此,需要一个定时器来产生周期性的中断,而且最好还让用户程序不能随意访问它的寄存器,以维持操作系统“心跳”的节律。
Cortex-M3 处理器内部包含了一个简单的定时器。因为所有的Cortex-M3处理器都带有这个定时器,软件在不同Cortex-M3处理器间的移植工作得以化简。该定时器的时钟源可以是内部时钟(FCLK,Cortex-M3处理器上的自由运行时钟),或者是外部时钟(Cortex-M3 处理器上的 STCLK信号)。不过,STCLK的具体来源由芯片设计者决定,因此不同产品之间的时钟频率可能会大不相同,需要检视芯片的器件手册来决定选择什么作为时钟源。
SysTick 定时器能产生中断,Cortex-M3处理器为它专门开出一个异常类型,并且在向量表中有它的一席之地。它使操作系统和其他系统软件在Cortex-M3处理器间的移植变得简单多了,因为在所有CM3产品间对其处理都是相同的。
SysTick 定时器除了能服务于操作系统之外,还能用于其他目的:如作为一个闹钟,用于测量时间等。需要注意的是,当处理器在调试期间被喊停(halt)时,则SysTick 定时器亦将暂停运作。

## 1.2 SysTick 定时器寄存器

**SysTick定时器（STK）**

处理器有一个24位系统定时器，SysTick，它从装载值开始倒数，直到倒数到零，在下一个时钟边沿时重新加载（回绕到）LOAD寄存器中的值，然后在随后的时钟上继续倒数。
当处理器因调试而停止时，计数器不会递减。

### 1.2.1 STK_CTRL

**SysTick控制和状态寄存器（STK_CTRL）**

- 地址偏移：0x00
- 复位值：0x0000 0000
- 所需权限：特权级
- SysTick CTRL 寄存器启用 SysTick 功能。

这意味着 SysTick 控制和状态寄存器（STK_CTRL）的地址偏移为0x00，在复位后，它的初始值为0x0000 0000。访问这个寄存器需要特权级权限。这个寄存器用于启用和配置 SysTick 定时器的各种功能。

![image-20240621173025893](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202406211730026.png)

**位 31:17 保留，必须保持清零。**

**位 16 `COUNTFLAG`：**
如果自上次读取以来定时器计数到了0，则返回1。

**位 15:3 保留，必须保持清零。**

**位 2 `CLKSOURCE`：时钟源选择**
选择时钟源。

- 0: AHB/8  外部
- 1: 处理器时钟 (AHB)  内核

**位 1 `TICKINT`：SysTick异常请求使能**

- 0: 倒计时到零时不发送SysTick异常请求
- 1: 倒计时到零时发送SysTick异常请求
  注意：软件可以使用`COUNTFLAG`来确定SysTick是否曾经计数到零。

**位 0 `ENABLE`：计数器使能**
启用计数器。当`ENABLE`设置为1时，计数器从LOAD寄存器加载RELOAD值并开始倒计时。当计数到0时，它将`COUNTFLAG`设置为1，并根据`TICKINT`的值选择是否发送SysTick请求。然后再次加载RELOAD值并开始新的倒计时。

- 0: 计数器禁用
- 1: 计数器启用

### 1.2.2 STK_LOAD

**SysTick重装值寄存器（STK_LOAD）**

- 地址偏移：0x04
- 复位值：0x0000 0000
- 所需权限：特权级

![image-20240621180656090](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202406211806178.png)

**位 31:24 保留，必须保持清零。**

**位 23:0 `RELOAD[23:0]`：重装值**

- `LOAD`寄存器指定在计数器启用和计数到0时加载到`VAL`寄存器的初始值。

**计算`RELOAD`值：**
`RELOAD`值可以是范围0x00000001到0x00FFFFFF内的任何值。初始值为0是可能的，但没有效果，因为从1计数到0时会激活SysTick异常请求和`COUNTFLAG`。

根据用途计算`RELOAD`值：

- 要生成周期为N个处理器时钟周期的多次触发定时器，使用`RELOAD`值N-1。例如，如果每100个时钟脉冲需要一个SysTick中断，则将`RELOAD`设置为99。
- 要在经过N个处理器时钟周期后发送一个SysTick中断，使用`RELOAD`值N。例如，如果在400个时钟脉冲后需要一个SysTick中断，则将`RELOAD`设置为400。

### 1.2.3 STK_VAL

**SysTick当前值寄存器（STK_VAL）**

- 地址偏移：0x08
- 复位值：0x0000 0000
- 所需权限：特权级

![image-20240621180730097](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202406211807175.png)

**位 31:24 保留，必须保持清零。**

**位 23:0 `CURRENT[23:0]`：当前计数器值**

- `VAL`寄存器包含SysTick计数器的当前值。
- 读取操作返回SysTick计数器的当前值。
- 写入任意值将把该字段清零，并同时将`STK_CTRL`寄存器中的`COUNTFLAG`位清零。

### 1.2.4 STK_CALIB

**SysTick校准值寄存器（STK_CALIB）**

- 地址偏移：0x0C
- 复位值：0x0002328
- 所需权限：特权级

![image-20240621180747434](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202406211807485.png)

**该CALIB寄存器指示SysTick校准属性**

**位 31 `NOREF`：无参考标志**

- 读取为零。指示提供了一个独立的参考时钟。此时钟的频率为 HCLK/8。

**位 30 `SKEW`：倾斜标志**

- 读取为一。因为不知道1毫秒的不精准定时的校准值TENMS，所以不清楚校准值。这可能会影响SysTick作为软件实时钟的适用性。

**位 29:24 保留，必须保持清零。**

**位 23:0 `TENMS[23:0]`：校准值**

- 指示当SysTick计数器在HCLK最大值的八分之一频率（HCLK max/8）作为外部时钟运行时的校准值。此值依产品而定，请参考产品参考手册中关于SysTick校准值的章节。当HCLK被设置为最大频率时，SysTick的周期是1毫秒。
- 如果校准信息未知，可根据处理器时钟或外部时钟的频率计算所需的校准值。

**SysTick设计提示和技巧**

1. **SysTick计数器运行在处理器时钟上**：如果此时钟信号因低功耗模式而停止，SysTick计数器也会停止。
2. **确保软件使用对齐的字访问来访问SysTick寄存器**。

**SysTick寄存器地图**
下表提供了SysTick寄存器地图及复位值。SysTick寄存器块的基地址为0xE000 E010。



| 寄存器名称 | 地址偏移 | 复位值     | 权限 |
| ---------- | -------- | ---------- | ---- |
| STK_CTRL   | 0x00     | 0x00000004 | 特权 |
| STK_LOAD   | 0x04     | 0x00000000 | 特权 |
| STK_VAL    | 0x08     | 0x00000000 | 特权 |
| STK_CALIB  | 0x0C     | 0x00002328 | 特权 |



## 1.3 SysTick 定时器应用

上一节LED流水灯控制程序中延时程序是通过软件延时的方法来实现的,这个时间很不精确,只能大概估计。根据上述分析,本节利用SysTick定时器可以分别编写delay_us()延时函数和delay_ms()延时函数,供流水灯控制程序调用,实现精确延时。本项目具体操作步骤如下:
第二步:将原工程模板编译一下,直到没有错误和警告为止。新建两个文件,将其改名为systick.c和systick,h并保存到工程模板下的APP文件夹中。并将systick.c文件添加到APP项目组下,并再次编译一下。
第一步:复制上一节项目文件夹到桌面,并将文件夹改名为“3SysTick 定时器”
第三步:在systick,c文件中输人如下源程序,在程序中首先包含systick.h头文件,然后创建两个延时函数,一个是微秒延时雨数:delay_us(u32i),另一个是毫秒延时函数delay_ms(u32 i)。

# 代码

Delay.h

````c
#ifndef __DELAY_H
#define __DELAY_H

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#endif

````

Delay.c

````c
#include "stm32f10x.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，2位使用内部72MHz时钟，0位ENABLE 启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 

````



````
好的，接下来我将详细解释你的Delay_us函数的各个部分及其作用：
c
Copy
void Delay_us(uint32_t xus)
{
    SysTick->LOAD = 72 * xus;                //设置定时器重装值
    SysTick->VAL = 0x00;                     //清空当前计数值
    SysTick->CTRL = 0x00000005;              //设置时钟源为HCLK，启动定时器
    while(!(SysTick->CTRL & 0x00010000));    //等待计数到0
    SysTick->CTRL = 0x00000004;              //关闭定时器
}
详细解释
SysTick->LOAD = 72 * xus;
作用：设置SysTick计数器的重装载值（LOAD寄存器）。
原因：假设处理器的时钟频率为72 MHz（即HCLK = 72,000,000 Hz），那么每微秒应该计数72个周期。因此，延迟xus微秒需要的总周期数为72 * xus。
SysTick->VAL = 0x00;
作用：清空当前计数值寄存器（VAL寄存器）。
原因：在启动计数器之前将当前计数值清零，确保计数器从重装载值开始计数。
SysTick->CTRL = 0x00000005;
作用：配置SysTick计数器的控制寄存器（CTRL寄存器），并启动计数器。
原因：
0x5的二进制表示为00000101，即：
Bit 0 (ENABLE)：1，启用计数器。
Bit 1 (TICKINT)：0，禁止除错中断。
Bit 2 (CLKSOURCE)：1，选择处理器时钟（HCLK）作为时钟源。
while (!(SysTick->CTRL & 0x00010000));
作用：等待计数器计数到0。
原因：
Bit 16（COUNTFLAG）会在计数器计数到0时置位（变为1）。
通过检测COUNTFLAG，可以知道计数是否已经完成。
SysTick->CTRL = 0x00000004;
作用：关闭SysTick计数器。
原因：
0x4的二进制表示为00000100，即：
Bit 0 (ENABLE)：0，禁用计数器。
Bit 1 (TICKINT)：0，禁止中断。
Bit 2 (CLKSOURCE)：1，选择处理器时钟作为时钟源。
总结
你的代码通过SysTick计数器实现了一个基于处理器时钟的精确微秒延迟函数。它通过设置重装载值、清空当前值，并启用计数器，然后等待计数到0，最终达到延迟指定微秒数的效果。这种方法的优点是延迟精度较高，并且相对简单直接。但是请注意，如果使用不同的处理器时钟频率，需要相应地调整72这个常数。
````

