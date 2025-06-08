#ifndef _SPI_MODEL_H
#define _SPI_MODEL_H



//初始化
void SPI_ModelInit(void);
//启动
void SPI_ModelStart(void);
//停止
void SPI_ModelStop(void);

//交换数据
uint8_t SPI_ModelSwap(uint8_t data);


#endif
