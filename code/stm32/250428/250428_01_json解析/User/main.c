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
	
	
	OLED_Init();
	Serial_Init();
 // JSON 字符串
	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"name","zhangsan");
	cJSON_AddNumberToObject(root,"age",1);
	
	cJSON *address = cJSON_CreateObject();
	cJSON_AddStringToObject(address,"street","caihonglu");
	cJSON_AddStringToObject(address,"city","nanjing");
	cJSON_AddStringToObject(address,"postalCode","10001");
	
	cJSON_AddItemToObject(root,"address",address);
	
	cJSON *hobby = cJSON_CreateArray();
	cJSON_AddItemToArray(hobby,cJSON_CreateString("reading"));
	cJSON_AddItemToArray(hobby,cJSON_CreateString("basketball"));
	cJSON_AddItemToArray(hobby,cJSON_CreateString("cooking"));
	
	cJSON_AddItemToObject(root,"hobby",hobby);
	
	char *str = cJSON_Print(root);
	printf("%s",str);

	cJSON_Delete(root);//释放
	free(str);
	while(1)
	{
	
	}
}
