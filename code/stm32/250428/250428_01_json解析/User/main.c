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
	
	
	OLED_Init();
	Serial_Init();
 // JSON �ַ���
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

	cJSON_Delete(root);//�ͷ�
	free(str);
	while(1)
	{
	
	}
}
