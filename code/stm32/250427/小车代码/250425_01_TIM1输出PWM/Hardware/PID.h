#ifndef _PID_H
#define _PID_H


int16_t PID_Banlance(int16_t pitch,int16_t gyroY);
int16_t Velocity(int Encoder_Left,int Encoder_Right);
int Turn(float gyroz);

#endif
