#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "cJSON.h"
#include "stdlib.h"
#include "Serial.h"

/****************
**	1.�����ж��Ƿ�Ϊnull
**	2.��Ҫ�ͷ�root��cJSON_Delete
**	3.cJSON������cJSON_Parse
**	4.��ȡcJSON��ֵ��cJSON_GetObjectItem
**	5.��ȡ�����С��cJSON_GetArraySize	��ȡ�����Ԫ�أ�cJSON_GetArrayItem
**	6.����json����cJSON_CreateObject		�������飺cJSON_CreateArray
**	7.��ӡ��cJSON_Print
*/


int main()
{
	
	//��ҵ��ȡ��contentֵ
	OLED_Init();
	Serial_Init();

	// JSON�ַ���
  const char *json_string = "{\"results\":[{\"location\":{\"id\":\"WT3Q0FW9ZJ3Q\",\"name\":\"Wuhan\",\"country\":\"CN\",\"path\":\"Wuhan,Wuhan,Hubei,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"now\":{\"text\":\"Sunny\",\"code\":\"0\",\"temperature\":\"28\"},\"last_update\":\"2024-04-26T15:04:17+08:00\"}]}";
	
	cJSON *root = cJSON_Parse(json_string);
	if(root == NULL)
	{
		printf("error");
	}
	
	cJSON *results = cJSON_GetObjectItem(root,"results");
	if(results == NULL)
	{
		printf("error");
	}
	
	cJSON *results0 = cJSON_GetArrayItem(results,0);
	if(results0 == NULL)
	{
		printf("error");
	}
	
	cJSON *now = cJSON_GetObjectItem(results0,"now");
	if(now == NULL)
	{
		printf("error");
	}
	
	cJSON *text = cJSON_GetObjectItem(now,"text");
	if(text == NULL)
	{
		printf("error");
	}

	OLED_ShowString(1,1,text->valuestring);
	printf("%s",text->valuestring);
	cJSON_Delete(root);//�ͷ�
	while(1)
	{
	
	}
}
