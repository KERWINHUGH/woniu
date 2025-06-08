#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Timer.h"
#include "EncoderInterface.h"
#include "PWM.h"
#include "IMU.h"
#include "PID.h"

int16_t encoder_Left_Speed = 0;
int16_t encoder_Right_speed = 0;
int main()
{	
	OLED_Init();
	
	MPU6050_Init();

	Motor_Init();
	//初始化编码器测速
	EncoderInit();
	//初始化定时器中断，实时测速
	Timer2_Init();
	
//	Left_SetSpeed(2000);
//	Right_SetSpeed(-2000);
//	
	OLED_ShowString(1,1,"Left :");
	OLED_ShowString(2,1,"Right:");
	OLED_ShowString(3,1,"pitch:");//俯仰角，前倾是负，后仰是正
	OLED_ShowString(4,1,"GyroY:");//y轴角速度
	

	
	while(1)
	{
		IMU_getEuleranAngles();
		OLED_ShowSignedNum(1,7,encoder_Left_Speed,4);
		OLED_ShowSignedNum(2,7,encoder_Right_speed,4);
		OLED_ShowSignedNum(3,7,imu_Angle.Pitch,4);
		OLED_ShowSignedNum(4,7,mpu6050.GyroY,4);
		
		//控制速度
		int16_t speed = PID_Banlance(imu_Angle.Pitch,mpu6050.GyroY) ;//直立环
		speed += Velocity(encoder_Left_Speed,encoder_Right_speed);//速度环
		Left_SetSpeed(speed + Turn(mpu6050.GyroZ));//转向环
		Right_SetSpeed(speed - Turn(mpu6050.GyroZ));//转向环
		
	}
	
}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		
		encoder_Left_Speed = TIM_GetCounter(TIM4);
		TIM_SetCounter(TIM4,0);
		
		encoder_Right_speed = TIM_GetCounter(TIM3);
		TIM_SetCounter(TIM3,0);
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
