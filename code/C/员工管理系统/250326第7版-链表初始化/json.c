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



// Admin结构体转JSON
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
// JSON转Admin结构体
Admin* json_to_Admin(const char* json_str) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Admin* p = (Admin*)malloc(sizeof(Admin));
    memset(p, 0, sizeof(Admin));

    // 提取字段（需检查字段是否存在且类型正确）
    
    cJSON* item = cJSON_GetObjectItem(root, "id");
    if (item && cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }
    
    item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

    item = cJSON_GetObjectItem(root, "password");
    if (item && cJSON_IsString(item)) {
        strncpy(p->password, item->valuestring, sizeof(p->password) - 1);
    }

    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
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
    cJSON_AddNumberToObject(root, "salary", p->salary);
    
    cJSON_AddStringToObject(root, "gender", gender_to_string( p->genders ));//枚举
    cJSON_AddStringToObject(root, "department", department_to_string(p->departments));//
    cJSON_AddStringToObject(root, "title", title_to_string(p->titles));//
    cJSON_AddStringToObject(root, "role", role_to_string(p->roles));// 
    
    // 生成JSON字符串
    //char* json_str = cJSON_Print(root);
    // 生成无格式化的JSON字符串（紧凑格式）
    char* json_str = cJSON_PrintUnformatted(root);    
    
    cJSON_Delete(root);  // 释放JSON对象内存

    return json_str;  // 需调用者手动 free(json_str)
}

// JSON转Employee结构体
Employee* json_to_Employee(const char* json_str) {
	//Employee employee = {0};
	
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {	
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }
	//确保解析成功
    Employee* p = (Employee*)malloc(sizeof(Employee));
    //memset(p, 0, sizeof(Employee));

    // 提取字段（需检查字段是否存在且类型正确）
    cJSON* item = cJSON_GetObjectItem(root, "id");
    
    if (item && cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }
    
    item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

    item = cJSON_GetObjectItem(root, "password");
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
    if (item && cJSON_IsString(item)) {
        p->genders = string_to_gender( item->valuestring ) ;//枚举
    }
    
    item = cJSON_GetObjectItem(root, "department");
    if (item && cJSON_IsString(item)) {
         p->departments = string_to_department( item->valuestring ) ;//枚举
    }
    
    item = cJSON_GetObjectItem(root, "title");
    if (item && cJSON_IsString(item)) {
         p->titles = string_to_title( item->valuestring ) ;//枚举
    }
     
    item = cJSON_GetObjectItem(root, "role");
    if (item && cJSON_IsString(item)) {
         p->roles = string_to_role( item->valuestring ) ;//枚举
    }
    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}


// Admin数组转JSON字符串
char* Admin_array_to_json(const Admin* admins, int count) {
	// 创建JSON数组
    cJSON* array = cJSON_CreateArray();
     
    // 把结构体数组里的数据，转换成到json数组里面去
    for (int i = 0; i < count; i++) {
    	
    	// 创建每个Admin的JSON对象
        cJSON* admin_obj = cJSON_CreateObject();  

        // 添加字段
        cJSON_AddNumberToObject(admin_obj, "id", admins[i].id);
        cJSON_AddStringToObject(admin_obj, "name", admins[i].name);
        cJSON_AddStringToObject(admin_obj, "password", admins[i].password);

		
		// 将Admin对象添加到数组中
        cJSON_AddItemToArray(array, admin_obj);  
    }

	// 数据转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
}


// JSON转Admin结构体数组
/*
**参数：json_str：输入的JSON字符串，需要符合特定格式；count：输出参数，返回解析出的管理员数量
**返回值：成功时返回Admin数组指针，需要调用者使用free()释放内存；失败时返回NULL，并通过count返回0
*/
Admin* json_to_Admin_array(const char* json_str, int* count) {
    // 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);
    if (!root) {
        return NULL; // 解析失败
    }

    // 验证根节点是否为数组
    if (!cJSON_IsArray(root)) {
        cJSON_Delete(root);
        return NULL;
    }

    // 获取数组大小并分配内存
    *count = cJSON_GetArraySize(root);
    Admin* admins = (Admin*)malloc(sizeof(Admin) * (*count));
    if (!admins) {
        cJSON_Delete(root);
        return NULL;
    }

    // 遍历数组元素
    for (int i = 0; i < *count; i++) {
        cJSON* item = cJSON_GetArrayItem(root, i);
        if (!cJSON_IsObject(item)) {
            free(admins);
            cJSON_Delete(root);
            *count = 0;
            return NULL;
        }

        // 提取各字段
        cJSON* id_item = cJSON_GetObjectItem(item, "id");
        cJSON* name_item = cJSON_GetObjectItem(item, "name");
        cJSON* password_item = cJSON_GetObjectItem(item, "password");

        // 验证字段存在性和类型
        if (!cJSON_IsNumber(id_item) || 
            !cJSON_IsString(name_item) || 
            !cJSON_IsString(password_item)) {
            free(admins);
            cJSON_Delete(root);
            *count = 0;
            return NULL;
        }

        // 赋值到结构体
        admins[i].id = id_item->valueint;
        strncpy(admins[i].name, name_item->valuestring, sizeof(admins[i].name)-1);
        admins[i].name[sizeof(admins[i].name)-1] = '\0';
        strncpy(admins[i].password, password_item->valuestring, sizeof(admins[i].password)-1);
        admins[i].password[sizeof(admins[i].password)-1] = '\0';
    }

    cJSON_Delete(root);
    return admins;
}

/*
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
    	cJSON_AddNumberToObject(employee_obj, "salary", employees[i].salary);
    
		cJSON_AddStringToObject(employee_obj, "gender", gender_to_string( p->genders ));//枚举----?
    	cJSON_AddStringToObject(employee_obj, "department", department_to_string(p->departments));//
    	cJSON_AddStringToObject(employee_obj, "title", title_to_string(p->titles));//
    	cJSON_AddStringToObject(employee_obj, "role", role_to_string(p->roles));// 
		
		
		
		// 将Employee对象添加到数组中
        cJSON_AddItemToArray(array, employee_obj);  
    }

	// 数据转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
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
