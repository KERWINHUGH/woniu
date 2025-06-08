#include "stm32f10x.h"                  // Device header
#include "PID.h"

#define Machine_Banlance   -2 

int16_t Banlance_KP = -935;
float Banlance_KD = -2.78;
int16_t Velocity_Kp = 15;
float Turn_Kp = 1.8;


int16_t PID_Banlance(int16_t pitch,int16_t gyroY)
{
	int16_t speed = (pitch - Machine_Banlance) * Banlance_KP + gyroY * Banlance_KD;
	return speed;
}
//速度环--保证平衡车不动，所以电机不动
int16_t Velocity(int Encoder_Left,int Encoder_Right)
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
//转向环，就是z轴上面的速度差，让两个轮子差不多的运行
int Turn(float gyroz)
{
	float Turn,Kp = 1,Bias;
	Bias = gyroz - 0;
	Turn = Bias*Turn_Kp;
	return Turn;
}
