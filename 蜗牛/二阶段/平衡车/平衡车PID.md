## 认识PID

开环控制系统不需要算法，根据情况随意输出控制指令即可。

但闭环系统不行，在要求精确控制的场景下，必须要知道MCU在发出指令后，受控设备是否有按照预期的目标执行，如果没有，需要调整发出的指令。

常见的闭环控制系统就是PID

首先，要明白什么情况下要用到PID控制：用户设定一个期望值，我们希望控制一个受控物体，通常是一个物理量，能够尽可能快的达到一个值，并且能够稳定住。那么这个控制器就需要一个或多个输入值，一个是用户的期望值，其他则是测量物理量的传感器的值。

P：proportion，比例，就是用户期望值，与传感器返回值的**差值，偏差**。

I：integral，积分，记录了从某一时刻开始，所有的**偏差的累积**。

D：derivative，微分，是偏差的偏差，相当于**偏差的导数，偏差变化的速率**。

在实际的运用中，我们不一定要用这里面的所有，但是一定是基于P的控制，积分和微分都是在数据上对偏差进行处理，可以有PI控制，可以有PD控制，也存在PID控制。

![image-20240424214751161](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240424214751161.png)

https://bitbci.github.io/Tools/pidSimulation/

### 结合平衡车，深度理解PID

**比例控制：把握当下**

那么，究竟什么时候用PI，什么时候用PD呢？这就要从原理说起。

比如我做一个平衡车，希望通过一种控制算法来实现平衡，最容易想到的方法就是**比例控制**：

1. 我希望平衡车稳定达到平衡状态（用户期望值）是平衡车的机械平衡角度（目标物理量），以及受控物体的角度，MPU6050传感器的DMP度数，

2. 两个数据的**偏差，作为输入**控制器的值，在控制器中乘上一个**增益**，经过输出**限幅**，然后**输出给执行器件**：电机，

3. 电机的工作状态，反过来又会影响平衡车的角度，角度又会被传感器收集，重新计算偏差，输入控制器。

于是，这样一个偏差控制器就形成了一个**闭环**。

**理论上**，一个理想的P控制器，只能使受控物理量无限接近目标值，因为当偏差逐渐减小，趋于零时，控制器的输入趋于零，那么无论有多大增益，输出也会趋于零，这样就会停在一个固定值。

但是在**实际中**，我们要考虑多种因素

第一，输出趋于零，小车可不会静止在一个角度，而是迅速倒下

第二，实际上第一种情况也是不存在的，因为从控制器输出PWM给电机，到平衡车角度改变，本身就是有很长时间的延时，会有**惯性**，这种控制**影响总是延后造成**。

因此，真正的情况是，平衡车的角度已经很接近机械零度了，电机的输出也已经快要停止了，然而，平衡车却有一个**角速度**，方向正是最初纠正平衡车的方向，这样，**就算停掉电机，小车依然会越过平衡点**，越过平衡点之后，偏差为负数，但是数值却很小，**偏差**经过控制器增益、限幅、输出给电机，**电机却无法产生足够及时纠正偏离的转动**，于是到小车反向倒下足够大的角度时，电机输出的转速才足够纠正，最终的结果就是，小车开始出现大幅度的**震荡**，根本无法平衡。

**比例+微分控制：预测未来，控制平衡**

如何改善这种震荡呢，经过前面的分析，我们知道，出现震荡的根本原因是机械系统的惯性，导致输出对受控物体的影响总是延后的。问题就出在，当角度接近机械零度时，我们的P控制器不工作了，**控制器认为完成了任务，然而控制器忽略了一种对下一个时刻的预测**，那么这个对下一个时刻的预测，指的就是角度偏差的导数，角度变化的速率，就是**角速度**。

有了这个认识，我们继续分析，角度偏差接近零度，但是系统**存在角速度**，那么**下一刻就一定会有角度偏差**，并且方向与角速度方向相反，通过数据，获取到角速度，就能够通过角速度，来修正这种状态，有预见性的输出给电机，让电机在下一个时刻就开始纠正偏差的倾向。

于是，我们加入D控制，微分项，相当于一个阻尼力：**在偏差项P占主导时，微分项D的影响相对来说非常小，然而当偏差趋于零时，微分项的作用就是，减慢受控物理量的变化速率。**

这样做的核心原理就是，**既然控制存在滞后，那我就提前控制**，就达到了抑制震荡，促进系统在平衡点稳定的目的。

**比例+积分控制：总结过去，控制位置**

上面的PD控制系统，基本上可以让平衡小车处于一个短期稳定平衡的状态，但是肯定不能长时间平衡，原因呢，要从具体的平衡控制结构来分析。

我们的传感器是单一的MPU6050，通过DMP库，输出的是角度以及角速度信号，而我们控制的是电机，也就是说，我们不考虑电机的感受，只要求平衡车的角度能够保持在机械零度，那么一旦平衡车收到扰动，或者控制闭环的任何一个环节，出现了微小的干扰，平衡车就会向一个方向加速，角度还是平衡的，但是平移的速度却没有限制，这样一旦驱动电机的PWM信号达到了限幅的数值，电机不再加速旋转，小车的执行器件就失去了执行能力，就会向这个方向倒下。

经过分析，我们需要再参考一个**物理量**，就是**编码器的读数**，既然使用编码电机，编码器的读数就需要纳入测量范围。然后问题又来了，如何处理读到的编码器数据呢？我们设置定时器模式为AB相编码器模式，那么每次读编码器，得到的是0-65535这个区间的一个值，电机转动，编码器的读数就会变化，我们希望小车在一个位置静止，就需要在平衡PD控制的基础上，加上一个**位置控制**，两种信号经过处理，输入控制器，控制器经过融合，输出给电机。

现在的问题是，**位置控制**使用什么样的方法？显然，**位置控制并不像角度的平衡控制，电机转动就能够较快地达到效果**，因此，我们需要一段时间，一步一步地接近我们设定的位置，也就是说，需要使用**速度控制，对速度的一步步累积**，使小车的位置（编码器的读数）逐渐趋于某一个值，这就要用到PI算法，即**比例+积分**控制来实现速度控制。

继续分析，我们假设用户输入的目标值是放下小车时刻，编码器的读数就是小车（车轮）的速度，这里可能就有点问题了，明明编码器的读数是脉冲信号，是位置啊，为什么说是速度呢？这就涉及到对编码器的数据处理，我们每隔一段时间，我们读取CNT寄存器，然后软件清零，意味着我们每次读取的数据，都是一段时间的计数值变化，不就是速度吗。弄清楚这个，我们开始分析怎么实现比例+积分的控制。

每隔一定周期，我们获取一次编码器的速度，然后与用户期望的速度，得到一个偏差，这个偏差就是P（比例），很显然偏差越大，我们需要的回复力就越大。到这里，我们吧前面的平衡PD控制，加上速度P控制，经过调整三个增益的大小以及比例，在控制器中对信号进行简单的叠加（叠加式PID，另外还有串联式，这里没有用到），就能够完美的实现小车的长时间稳定了。完美的状态是，推动小车，小车会前进一段距离，然后重新进入平衡。

那么，我们如果想要实现小车能够记住自己的位置，在受到外部干扰后自动回复到初始位置，该如何操作呢？注意，这里我提到了记住这么一个概念，就不难想到，这种控制，需要历史的全部速度信息，对离散的速度进行积分，得到从初始时刻，到当前时刻的位置信息。为了做到这一点，我们需要引入速度PI控制，比例+积分。具体的操作就是：从开始时刻，固定周期将速度偏差进行累加（具体可能需要滤波，这里讲解原理，略去），这个累加的值，就是偏离的距离，把这个距离，经过一个增益，也叠加进前面的3个参数，一共4个参数，共同作为输入，经过控制器输出给电机，这样就实现了在一个位置的PD+PI控制算法。

### 通过代码，分析PID的各个组成部分

### 1、单闭环PID

根据第一章的分析，我们直立环的程序如下：

```c
int Banlance(float Angle,float Mechanical_balance,float Gyroy)
{
    float Bias;
    int out;
    Bias = Angle - Mechanical_balance;
    out = PID_Banlance.Kp*Bias+PID_Banlance.Kd*Gyroy;
 return out;
}
```

- 此函数三个入口参数分别为角度值，机械中值和角速度值，机械中值的获得会在后面介绍。
  速度环程序如下：

```c
int Velocity(int Encoder_Left,int Encoder_Right)
{
    static float out,Encoder_Least,Encoder;
    static float Encoder_Integral;
    Encoder_Least =(Encoder_Left+Encoder_Right)-0;                   
    Encoder *= 0.7;       //上一次的权重占得是0.7                                              
    Encoder += Encoder_Least*0.3;   //当前权重占得是0.3                                           
    Encoder_Integral +=Encoder;                                      
//    Encoder_Integral=Encoder_Integral;                      
	if(Encoder_Integral>10000)      Encoder_Integral=10000;             
	if(Encoder_Integral<-10000)     Encoder_Integral=-10000;           
	out=Encoder*PID_Velocity.Kp+Encoder_Integral*PID_Velocity.Ki;                        
	return out;
}
```

- 此函数的入口参数为俩编码器测得的脉冲数。

```c
int Turn(int encoder_left,int encoder_right,float gyroz)
{
	float Turn,Kp = 1,Bias;
	Bias = gyro - 0;
	Turn = -Bias*Kp;
	return Turn;
}
```

### 2、抗积分饱和

程序中10000是积分上限值，当Encoder_Integral>10000时，取Encoder_Integral=10000，10000是积分的上限值，当Encoder_Integral<-10000时，取Encoder_Integral=-10000，-10000是积分的下限值,这样做是为了防止积分饱和，这种方法叫做“积分限幅法”；因为实际的执行器只能在一定的输入范围内有效，所以PID控制器的输出幅度需要限制。

```c
 if(Encoder_Integral>10000)      Encoder_Integral=10000;             
 if(Encoder_Integral<-10000)     Encoder_Integral=-10000;    
```

### 3、串级PID

通过第一章的推导，输出方程可以将串级PID的算法转化成为：一个单独的负反馈的直立环 + 一个单独的正反馈的速度环。

```c
 Velocity_Pwm=Velocity_PID(enc1,enc2);
 Balance_Pwm=Banlance_PID(Angle_Y,-2,Velocity_Angle_Y);
 Turn_Pwm =Angle_Z*30;
 Moto1=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                 
 Moto2=Balance_Pwm-Velocity_Pwm+Turn_Pwm;
```

## 参数整定及极性判断

### 1、机械中值

> 由于小车结构的问题，小车的重心不一定与0角度在一条直线上，所以我们需要找到让重心平衡的角度，即机械中值。

首先，把小车放在地面上，从前向后以及从后向前绕电机轴旋转平衡小车，两次向另一边倒下的角度的中值，即为机械中值。

***(举例：往后倒在2度，往后倒在-3度左右，本系统的机械中值为-1度。)***

### 2、直立环：

1. Kp极性：

- 极性错误：小车往哪边倒，车轮就往反方向开，会使得小车加速倒下。
- 极性正确：小车往哪边倒，车轮就往哪边开，以保证小车有直立的趋势。
- Kp大小：
- Kp一直增加，直到出现大幅低频振荡。**（即小车平衡时出现抖动）**
- Kd极性：
- 极性错误：拿起小车绕电机轴旋转，车轮反向转动，无跟随。
- 极性正确：拿起小车绕电机轴旋转，车轮同向转动，有跟随。
- Kd大小：
- Kd一直增加，直到出现高频振荡。（即触碰小车出现剧烈抖动）
  **直立环调试完毕后，对所有确立的参数乘以0.6作为最终参数。**
- 原因：之前得到的参数都是Kp、Kd最大值，根据工程经验平衡小车的理想参数为最大参数乘以0.6求得。
- 结果：乘0.6后，小车抖动消失，但同时直立效果也变差。待下面加入速度环就能得到更好的性能。

### 3、速度环：（Velocity Loop）

速度环用于控制平衡车的前进和后退速度，它是基于平衡环之上的另一个控制环路。速度环的目的是：

- **保持设定的速度**：如果目标是静止，那么速度环会不断调整电机的转速，抵消因为平衡调整而引起的前后移动，使车子保持原地不动。
- **控制前进或后退**：根据目标速度和当前速度的差值，调整电机的转速，实现期望的前进或后退速度。

**线性关系：Ki=(1/200)\*Kp，仅调Kp即可。**

1. Kp、Ki极性：

- **在调节【速度环参数极性】时，需要去掉【直立环运算】**
- 极性错误：手动转动其中一个车轮，另一车轮会以同样速度反向旋转——典型负反馈。
- 极性正确：手动转动其中一个车轮，两个车轮会同向加速，直至电机最大速度——典型正反馈。
- Kp、Ki大小：
- 增加Kp&Ki，直至：小车保持平衡的同时，速度接近于0，且回位效果好。

````c
//速度环--保证平衡车不动，所以电机不动
int Velocity(int Encoder_Left,int Encoder_Right)
{
    static float out,Encoder_Least,Encoder;
    static float Encoder_Integral;
    Encoder_Least =(Encoder_Left+Encoder_Right)-0;                   
    Encoder *= 0.7;                                                     
    Encoder += Encoder_Least*0.3;                                       
    Encoder_Integral +=Encoder;                                      
    Encoder_Integral=Encoder_Integral;                      
	if(Encoder_Integral>10000)      Encoder_Integral=10000;             
	if(Encoder_Integral<-10000)     Encoder_Integral=-10000;           
	out=Encoder*Velocity_Kp+Encoder_Integral*(Velocity_Kp/200);                        
	return out;
}
````



### 4、转向环



转向环用于控制平衡车的转向，它是通过调整左右车轮的速度差来实现的。转向环的目的是：

- **实现转向控制**：通过控制左右车轮的相对速度差，实现平衡车的转向。例如，左轮快右轮慢，车子就会向右转；反之亦然。
- **调整转向角速度**：根据当前的转向角速度和目标角速度的差值，调整车轮速度，达到期望的转向效果。

```c

//转向环，就是z轴上面的速度差，让两个轮子差不多的运行
int Turn(float gyroz)
{
	float Turn,Kp = 1,Bias;
	Bias = gyroz - 0;
	Turn = Bias*Turn_Kp;
	return Turn;
}

```



## 代码

````c
#include "stm32f10x.h"                  // Device header

//机械中值，平衡车在平衡的时候的俯仰角
#define Mechanical_balance -2 //大致平衡的时候的值

int Balance_Kp = -1700;//根据pitch计算Kp的值
float Balance_Kd = -2.1;//根据y轴的角速度，也就是倒下去的速度，测出来的D值
float PID_Velocity_Kp = 15;//速度环的参数
float Turn_Kp = 1.8;

/**
 当前正在倒下的角度pitch，角速度Gyroy
*/
int16_t PID_Balance(float pitch,float Gyroy)
{
	float bias = pitch - Mechanical_balance;//假设往前倒pitch=-5,bias = -5 - (-1) = -4
	return bias * Balance_Kp + Gyroy * Balance_Kd;  //-700 * -6 = 2800
}

/**
   速度
*/
int Velocity(int Encoder_Left,int Encoder_Right)
{
    static float out,Encoder_Least,Encoder;
    static float Encoder_Integral;
    Encoder_Least =(Encoder_Left+Encoder_Right)-0;                   
    Encoder *= 0.7;                                                     
    Encoder += Encoder_Least*0.3;                                       
    Encoder_Integral +=Encoder;                                      
	if(Encoder_Integral>10000)      Encoder_Integral=10000;             
	if(Encoder_Integral<-10000)     Encoder_Integral=-10000;           
	out=Encoder*PID_Velocity_Kp+Encoder_Integral*(PID_Velocity_Kp/200);                        
	return out;
}

//转向环
int Turn(float gyroz)
{
	float Turn,Bias;
	Bias = gyroz - 0;
	Turn = Bias*Turn_Kp;
	return Turn;
}

````



````c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "MPU6050.h"
#include "IMU.h"
#include "Motor.h"
#include "EncoderInterfaceSpeed.h"
#include "MyTimer.h"
#include "PID.h"

int16_t LeftSpeed = 0;
int16_t RightSpeed = 0;
int16_t SpeedL;
int16_t SpeedR; 
int16_t speed;

int main(void)
{	
	OLED_Init();
	MPU6050_Init();//MPU6050设置好了
	Motor_Init();//PWM
	TIM3_InputCaptureInit();
	TIM4_InputCaptureInit();
	MyTimer_Init();
	
	while(1)
	{
		IMU_getEuleranAngles();
		OLED_ShowString(1,1,"P:");
		OLED_ShowSignedNum(1,3,imu_Angle.Pitch,5);
		OLED_ShowString(2,1,"GYROY:");
		OLED_ShowSignedNum(2,7,mpu6050.GyroY,5);
		OLED_ShowSignedNum(3,1,LeftSpeed,5);
		OLED_ShowSignedNum(4,1,RightSpeed,5);
		
		
		speed = PID_Balance(imu_Angle.Pitch,mpu6050.GyroY)*0.6 + Velocity(LeftSpeed,RightSpeed);
			
		
		
		SpeedL =  Turn(mpu6050.GyroZ);
		SpeedR = - Turn(mpu6050.GyroZ);
		
		if(SpeedL>7200)
			SpeedL = 7200;
		if(SpeedL<-7200)
		{
			SpeedL = -7200;
		}
		
		if(SpeedR>7200)
			SpeedR = 7200;
		if(SpeedR<-7200)
		{
			SpeedR = -7200;
		}
		
		//交给电机运行
		Left_SetSpeed(SpeedL);
		Right_SetSpeed(SpeedR);
	}
}

//定时器的中断函数,1秒一次产生中断
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		//计算出速度
		RightSpeed = TIM_GetCounter(TIM3);
		LeftSpeed = TIM_GetCounter(TIM4);
		
		//把CNT清零
		TIM_SetCounter(TIM3,0);
		TIM_SetCounter(TIM4,0);
		
		//清除中断标志位,这个函数是在中断中使用的
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}



````

