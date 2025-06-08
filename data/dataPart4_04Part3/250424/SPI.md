# 一、SPI通信

![image-20250107105910142](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202501071059631.png)



## 1.1 SS 片选

选择一个从设备(Slave Select)，每个从设备，都一个SS线

![image-20250107100137397](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202501071001007.png)



## 1.2 时钟 SCK

* 规范什么时候放数据，什么时候读数据

参数1：空闲状态的时候：高电平，还是低电平

参数2：第一个边沿放数据，还是读数据

![image-20250107103814884](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202501071038254.png)

## 1.3 MOSI和MISO

![image-20250107102649060](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202501071026562.png)

# 二、W25Q64

* 大小：64M bit =8M byte
* 块：8M byte 分成了128Block，每个Block=64K
* 扇区：每个块分16个扇区，每个扇区64/16 = 4K 
* 页：page,地址从000000-0000FF，每个地址指向一个Byte,所以一个page是256个byte，一个扇区里面有16个Page
* 地址：是使用24位二进制的地址也就是6位16进制的地址。

## 2.1 地址

![](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202501071500493.png)

## 2.2 写保护

每次写入数据的时候，都要关闭写保护，关闭写保护有两个办法，不管用什么办法，都需要控制Status Register，来打开和关闭写保护

1.通过引脚，走write protect control logic单元。

2.通过SPI指令，也可以关闭写保护 

## 2.3 Page Buffer(Busy,overflow)

* BUSY是状态寄存器（S0）中的一个只读位，当设备正在执行页编程(写)、扇区擦除、块擦除、芯片擦除或写状态寄存器指令时，BUSY被置为1。在此期间，设备将忽略其他指令，除了读取状态寄存器和擦除暂停指令（参见AC特性中的tW, tPP, tSE, tBE和tCE）。当编程Page_Program、擦除或写状态寄存器指令完成时，BUSY位将被清除为0，表示设备已准备好接受进一步的指令。



![image-20250107153411485](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202501071534869.png)

## 2.4 擦除

* 如果要写入数据，必须先擦除，最小擦除单元是扇区
* 如果不擦除，存储芯片没有能力把0改写成1，可以把1改成0
* 擦除完后，所有的数据都是1
* 擦除注意按照某个地址开始擦除
* 擦除的时候，要把写保护关闭
* 擦除的时候，也有Busy的状态

## 2.5 操作W25Q64

* SPI_Start
* 发送一个指令
* 按照指令的后续逻辑操作
* SPI_End













