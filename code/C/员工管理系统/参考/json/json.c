/***************************************************
# File Name:    PersonToJson.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 18 Mar 2025 08:52:38 PM CST
****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "json.h"

// 结构体转JSON
char* person_to_json(const Person* p) {
	// 创建JSON对象
    cJSON* root = cJSON_CreateObject();  

    // 添加字段
    cJSON_AddStringToObject(root, "name", p->name);
    cJSON_AddNumberToObject(root, "age", p->age);
    cJSON_AddNumberToObject(root, "height", p->height);
    cJSON_AddBoolToObject(root, "is_student", p->is_student);

    // 生成JSON字符串
    char* json_str = cJSON_Print(root);
    
    cJSON_Delete(root);  // 释放JSON对象内存

    return json_str;  // 需调用者手动 free(json_str)
}

// JSON转结构体
Person* json_to_person(const char* json_str) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Person* p = (Person*)malloc(sizeof(Person));
    memset(p, 0, sizeof(Person));

    // 提取字段（需检查字段是否存在且类型正确）
    cJSON* item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

    item = cJSON_GetObjectItem(root, "age");
    if (item && cJSON_IsNumber(item)) {
        p->age = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "height");
    if (item && cJSON_IsNumber(item)) {
        p->height = item->valuedouble;
    }

    item = cJSON_GetObjectItem(root, "is_student");
    if (item && cJSON_IsBool(item)) {
        p->is_student = cJSON_IsTrue(item);
    }

    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}

// Person数组转JSON
char* person_array_to_json(const Person* persons, int count) {
	// 创建JSON数组
    cJSON* array = cJSON_CreateArray();
     
    // 把结构体数组里的数据，转换成到json数组里面去
    for (int i = 0; i < count; i++) {
    	
    	// 创建每个Person的JSON对象
        cJSON* person_obj = cJSON_CreateObject();  

        // 添加字段
        cJSON_AddStringToObject(person_obj, "name", persons[i].name);
        cJSON_AddNumberToObject(person_obj, "age", persons[i].age);
        cJSON_AddNumberToObject(person_obj, "height", persons[i].height);
        cJSON_AddBoolToObject(person_obj, "is_student", persons[i].is_student);
		
		// 将Person对象添加到数组中
        cJSON_AddItemToArray(array, person_obj);  
    }

	// 转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
}

int main() {
	puts("---------------结构体转json-----------------");
	Person p = {"李四", 33, 178.8 , 1};
	char *json = person_to_json(&p);
	printf("json:%s \n", json);

	puts("---------------json转结构体-----------------");
	Person *p2 = json_to_person(json);
	printf("姓名：%s , 年龄：%d , 身高：%f , 是否学生：%d \n", p2->name, p2->age, p2->height, p2->is_student);

	puts("---------------测试数组-----------------");
    Person persons[] = {
        {"Alice", 25, 1.65, 1},
        {"Bob", 30, 1.80, 0}
    };
    int count = sizeof(persons) / sizeof(persons[0]);

    char* json_str = person_array_to_json(persons, count);
    if (json_str) {
        printf("JSON: %s\n", json_str);
        free(json_str);
    }

    return 0;
}    
