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



// Amdin结构体转JSON
char* Admin_to_json(const Admin* p){
	// 创建JSON对象
    cJSON* root = cJSON_CreateObject();  

    // 添加字段
    cJSON_AddNumberToObject(root, "id", p->id);
    cJSON_AddStringToObject(root, "name", p->name);
    cJSON_AddStringToObject(root, "password", p->password);

    // 生成JSON字符串
    char* json_str = cJSON_Print(root);
    
    cJSON_Delete(root);  // 释放JSON对象内存

    return json_str;  // 需调用者手动 free(json_str)
}
// Employee结构体转JSON
char* Employee_to_json(const Employee* p) {
	// 创建JSON对象
    cJSON* root = cJSON_CreateObject();  

    // 添加字段
    cJSON_AddNumberToObject(root, "id", p->id);
    cJSON_AddStringToObject(root, "name", p->name);
    cJSON_AddStringToObject(root, "password", p->password);
    cJSON_AddNumberToObject(root, "age", p->age);
    
    cJSON_AddNumberToObject(root, "gender", p->gender);//?
    
    cJSON_AddNumberToObject(root, "salary", p->salary);
    
    cJSON_AddStringToObject(root, "department", p->department);//?
    cJSON_AddStringToObject(root, "title", p->title);//?
    cJSON_AddStringToObject(root, "role", p->role);//?   
    
    // 生成JSON字符串
    char* json_str = cJSON_Print(root);
    
    cJSON_Delete(root);  // 释放JSON对象内存

    return json_str;  // 需调用者手动 free(json_str)
}

// JSON转Amdin结构体
Admin* json_to_Admin(const char* json_str) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Amdin* p = (Amdin*)malloc(sizeof(Amdin));
    memset(p, 0, sizeof(Amdin));

    // 提取字段（需检查字段是否存在且类型正确）
    
    item = cJSON_GetObjectItem(root, "id");
    if (item && cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }
    
    cJSON* item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

     cJSON* item = cJSON_GetObjectItem(root, "password");
    if (item && cJSON_IsString(item)) {
        strncpy(p->password, item->valuestring, sizeof(p->password) - 1);
    }

    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}

// JSON转Employee结构体
Employee* json_to_Employee(const char* json_str) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Employee* p = (Employee*)malloc(sizeof(Employee));
    memset(p, 0, sizeof(Employee));

    // 提取字段（需检查字段是否存在且类型正确）
    item = cJSON_GetObjectItem(root, "id");
    if (item && cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }
    
    cJSON* item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

     cJSON* item = cJSON_GetObjectItem(root, "password");
    if (item && cJSON_IsString(item)) {
        strncpy(p->password, item->valuestring, sizeof(p->password) - 1);
    } 

    item = cJSON_GetObjectItem(root, "age");
    if (item && cJSON_IsNumber(item)) {
        p->age = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "salary");
    if (item && cJSON_IsNumber(item)) {
        p->salary = item->valuedouble;
    }

    item = cJSON_GetObjectItem(root, "gender");
    if (item && cJSON_IsBool(item)) {
        p->gender = item->valueint;//?
    }
    
    item = cJSON_GetObjectItem(root, "department");
    if (item && cJSON_IsBool(item)) {
        p->department = item->valueint;
    }
    
    item = cJSON_GetObjectItem(root, "title");
    if (item && cJSON_IsBool(item)) {
        p->title = item->valueint;
    }
     
    item = cJSON_GetObjectItem(root, "role");
    if (item && cJSON_IsBool(item)) {
        p->role = item->valueint;
    }
    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}

// Amdin数组转JSON字符串
char* Admin_array_to_json(const Admin* admins, int count) {
	// 创建JSON数组
    cJSON* array = cJSON_CreateArray();
     
    // 把结构体数组里的数据，转换成到json数组里面去
    for (int i = 0; i < count; i++) {
    	
    	// 创建每个Amdin的JSON对象
        cJSON* amdin_obj = cJSON_CreateObject();  

        // 添加字段
        cJSON_AddNumberToObject(amdin_obj, "id", amdins[i].id);
        cJSON_AddStringToObject(amdin_obj, "name", amdins[i].name);
        cJSON_AddStringToObject(amdin_obj, "password", amdins[i].password);

		
		// 将Amdin对象添加到数组中
        cJSON_AddItemToArray(array, amdin_obj);  
    }

	// 数据转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
}

// Employee数组转JSON字符串
char* Employee_array_to_json(const Employee* employees, int count) {
	// 创建JSON数组
    cJSON* array = cJSON_CreateArray();
     
    // 把结构体数组里的数据，转换成到json数组里面去
    for (int i = 0; i < count; i++) {
    	
    	// 创建每个Employee的JSON对象
        cJSON* employee_obj = cJSON_CreateObject();  

        // 添加字段
		
		cJSON_AddNumberToObject(employee_obj, "id", employees[i].id);
    	cJSON_AddStringToObject(employee_obj, "name", employees[i].name);
    	cJSON_AddStringToObject(employee_obj, "password", employees[i].password);
    	cJSON_AddNumberToObject(employee_obj, "age", employees[i].age);
    
   		cJSON_AddNumberToObject(employee_obj, "gender", employees[i].gender);//?
    
    	cJSON_AddNumberToObject(employee_obj, "salary", employees[i].salary);
    
    	cJSON_AddStringToObject(employee_obj, "department", employees[i].department);//?
    	cJSON_AddStringToObject(employee_obj, "title", employees[i].title);//?
    	cJSON_AddStringToObject(employee_obj, "role", employees[i].role);//? 
		
		
		
		// 将Employee对象添加到数组中
        cJSON_AddItemToArray(array, employee_obj);  
    }

	// 数据转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
}
/*
// JSON转Amdin结构体数组
Admin* json_to_Admin_array(const char* json_str ,int count) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }
	
	for (int i = 0; i < count; i++) {
		Amdin* p = (Amdin*)malloc(sizeof(Amdin));
		memset(p, 0, sizeof(Amdin));

		// 提取字段（需检查字段是否存在且类型正确）
		
		item = cJSON_GetObjectItem(root, "id");
		if (item && cJSON_IsNumber(item)) {
		    p->id = item->valueint;
		}
		
		cJSON* item = cJSON_GetObjectItem(root, "name");
		if (item && cJSON_IsString(item)) {
		    strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
		}

		 cJSON* item = cJSON_GetObjectItem(root, "password");
		if (item && cJSON_IsString(item)) {
		    strncpy(p->password, item->valuestring, sizeof(p->password) - 1);
		}
	}
    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}
*/
/*
// JSON转Employee结构体数组
Employee* json_to_Employee_array(const char* json_str ,int count) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Employee* p = (Employee*)malloc(sizeof(Employee));
    memset(p, 0, sizeof(Employee));

    // 提取字段（需检查字段是否存在且类型正确）
    item = cJSON_GetObjectItem(root, "id");
    if (item && cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }
    
    cJSON* item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

     cJSON* item = cJSON_GetObjectItem(root, "password");
    if (item && cJSON_IsString(item)) {
        strncpy(p->password, item->valuestring, sizeof(p->password) - 1);
    } 

    item = cJSON_GetObjectItem(root, "age");
    if (item && cJSON_IsNumber(item)) {
        p->age = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "salary");
    if (item && cJSON_IsNumber(item)) {
        p->salary = item->valuedouble;
    }

    item = cJSON_GetObjectItem(root, "gender");
    if (item && cJSON_IsBool(item)) {
        p->gender = item->valueint;//?
    }
    
    item = cJSON_GetObjectItem(root, "department");
    if (item && cJSON_IsBool(item)) {
        p->department = item->valueint;
    }
    
    item = cJSON_GetObjectItem(root, "title");
    if (item && cJSON_IsBool(item)) {
        p->title = item->valueint;
    }
     
    item = cJSON_GetObjectItem(root, "role");
    if (item && cJSON_IsBool(item)) {
        p->role = item->valueint;
    }
    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}
*/

/*
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
*/
