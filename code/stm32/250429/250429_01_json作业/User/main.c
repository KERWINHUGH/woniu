#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "cJSON.h"
#include "stdlib.h"
#include "Serial.h"

/****************
**	1.经常判断是否为null
**	2.需要释放root，cJSON_Delete
**	3.cJSON解析：cJSON_Parse
**	4.获取cJSON中值：cJSON_GetObjectItem
**	5.获取数组大小：cJSON_GetArraySize	获取数组的元素：cJSON_GetArrayItem
**	6.创建json对象：cJSON_CreateObject		创建数组：cJSON_CreateArray
**	7.打印：cJSON_Print
*/


int main()
{
	
	//作业：取出content值
	OLED_Init();
	Serial_Init();

	// JSON字符串
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
	cJSON_Delete(root);//释放
	while(1)
	{
	
	}
}
