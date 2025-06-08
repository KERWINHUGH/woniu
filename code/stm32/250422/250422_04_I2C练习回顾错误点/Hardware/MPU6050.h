#ifndef _MPU6050_H
#define _MPU6050_H

#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C

#define SMPLRT_DIV 0x19 
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

void MPU6050_Init(void);
void MPU6050_Write(uint8_t RegAdd,uint8_t data);
uint8_t MPU6050_Read(uint8_t RegAdd);

#endif
