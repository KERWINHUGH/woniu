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

	const char *json_string = "{"
                              "  \"id\": \"chatcmpl-123\","
                              "  \"object\": \"chat.completion\","
                              "  \"created\": 1677652288,"
                              "  \"model\": \"gpt-4o-mini\","
                              "  \"system_fingerprint\": \"fp_44709d6fcb\","
                              "  \"choices\": [{"
                              "    \"index\": 0,"
                              "    \"message\": {"
                              "      \"role\": \"assistant\","
                              "      \"content\": \"Hello there, how may I assist you today?\""
                              "    },"
                              "    \"logprobs\": null,"
                              "    \"finish_reason\": \"stop\""
                              "  }],"
                              "  \"usage\": {"
                              "    \"prompt_tokens\": 9,"
                              "    \"completion_tokens\": 12,"
                              "    \"total_tokens\": 21"
                              "  }"
                              "}";
	
	cJSON *root = cJSON_Parse(json_string);
	if(root == NULL)
	{
		printf("error");
	}
	
	cJSON *choices = cJSON_GetObjectItem(root,"choices");
	if(choices == NULL)
	{
		printf("error");
	}
	
	cJSON *choices0 = cJSON_GetArrayItem(choices,0);
	if(choices0 == NULL)
	{
		printf("error");
	}
	
	cJSON *message = cJSON_GetObjectItem(choices0,"message");
	if(message == NULL)
	{
		printf("error");
	}
	
	cJSON *content = cJSON_GetObjectItem(message,"content");
	if(content == NULL)
	{
		printf("error");
	}

	OLED_ShowString(1,1,content->valuestring);
	printf("%s",content->valuestring);
	cJSON_Delete(root);//释放
	while(1)
	{
	
	}
}
