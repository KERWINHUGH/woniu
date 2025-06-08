#ifndef _DHT_H
#define _DHT_H

typedef struct
{
	uint8_t Humi_int;
	uint8_t Humi_deci;
	uint8_t Tem_int;
	uint8_t Tem_deci;
	uint8_t CheckSum;
}TemHumi;

void DHT_Init(void);
//设置主机
void DHT_SetOutputMode(void);
void DHT_SetInputMode(void);
//发送请求
void DHT_Req(void);
//等待回复
uint8_t DHT_Resp(void);
//处理一个字节
uint8_t DHT_GetByte(void);
void DHT_GetNowTemHumi(TemHumi *NowTemHumi);

#endif
