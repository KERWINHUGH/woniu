/***************************************************
# File Name:    PersonToJson.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 18 Mar 2025 08:52:38 PM CST
****************************************************/
#ifndef JSON_H
#define JSON_H

#include "EMS.h"			//引入系统所需要的结构体

// Admin结构体转JSON
char* Admin_to_json(const Admin* p);
// JSON转Amdin结构体
Admin* json_to_Admin(const char* json_str);

// Employee结构体转JSON
char* Employee_to_json(const Employee* p); 
// JSON转Employee结构体
Employee* json_to_Employee(const char* json_str);

// Admin数组转JSON字符串
char* Admin_array_to_json(const Admin* admins, int count);
// JSON转Admin结构体数组
Admin* json_to_Admin_array(const char* json_str, int* count); 

// Employee数组转JSON字符串
char* Employee_array_to_json(const Employee* employees, int count);
// JSON转Employee结构体数组
Employee* json_to_Employee_array(const char* json_str ,int *count);



#endif






