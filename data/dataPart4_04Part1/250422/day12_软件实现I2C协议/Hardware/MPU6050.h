#ifndef __MPU6050_H
#define __MPU6050_H
#include "I2C_Model.h"

#define WHO_AM_I 0x75
//配置相关的寄存器地址宏定义
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define SMPLRT_DIV 0x19 
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

//获取数据的寄存器地址宏定义
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

void MPU6050_Init(void);
void MPU6050_Write(uint8_t registerAddress,uint8_t data);
uint8_t MPU6050_Read(uint8_t registerAddress);
#endif

