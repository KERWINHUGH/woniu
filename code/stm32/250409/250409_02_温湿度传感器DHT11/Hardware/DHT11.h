#ifndef _DHT11_H
#define _DHT11_H

typedef struct TemHum
{
	uint8_t Hum_Integer;//湿度整数位
	uint8_t Hum_decimal;//湿度小数位
	uint8_t Tem_Integer;//温度整数位
	uint8_t Tem_decimal;//温度小数位
	uint8_t checksum;		//校验和
}TemHum;

void DHT11_Init(void);
void DHT11_SetPP(void);
void DHT11_SetIPU(void);
void DHT11_Req(void);
uint8_t DHT11_Resp(void);
uint8_t DHT11_GetByteData(void);
void DHT11_GetTemperAndHumidity(TemHum *NowTemHum);

#endif

