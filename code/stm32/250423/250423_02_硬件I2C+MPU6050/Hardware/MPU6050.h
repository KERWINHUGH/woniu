#ifndef _MPU6050_H
#define _MPU6050_H



#define WHO_AM_I  			0x75

//配置相关的寄存器地址的宏
#define PWR_MGMT_1  		0x6B
#define PWR_MGMT_2  		0x6C

#define SMPLRT_DIV  		0x19
#define CONFIG		 	 		0x1A
#define GYRO_CONFIG			0x1B
#define ACCEL_CONFIG  	0x1C	

//获取数据的寄存器地址的宏
typedef struct MPU6050_Data
{
	int16_t AccX;
	int16_t AccY;
	int16_t AccZ;
	
	int16_t GyroX;
	int16_t GyroY;
	int16_t GyroZ;
}MPU6050_Data;

#define ACCEL_XOUT_H 		0x3B
#define ACCEL_XOUT_L 		0x3C
#define ACCEL_YOUT_H 		0x3D
#define ACCEL_YOUT_L 		0x3E
#define ACCEL_ZOUT_H 		0x3F
#define ACCEL_ZOUT_L 		0x40

#define GYRO_XOUT_H 		0x67
#define GYRO_XOUT_L 		0x68
#define GYRO_YOUT_H 		0x69
#define GYRO_YOUT_L 		0x70
#define GYRO_ZOUT_H 		0x71
#define GYRO_ZOUT_L 		0x72



void MPU6050_Init(void);

void MPU6050_Write(uint8_t RegAdd,uint8_t data);

uint8_t MPU6050_Read(uint8_t RegAdd);

void getMpu6050Data(MPU6050_Data *MPU6050_speedRegData);


#endif
