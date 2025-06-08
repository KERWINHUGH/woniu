#ifndef _MPU6050_H
#define _MPU6050_H

void MPU6050_Init(void);
void MPU6050_Write(uint8_t regArr,uint8_t data);
uint8_t MPU6050_Read(uint8_t regArr);
	
#endif
