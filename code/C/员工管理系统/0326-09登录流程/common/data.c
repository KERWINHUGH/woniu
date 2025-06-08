/***************************************************
# File Name:    emploee_system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月23日 星期日 17时16分10秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>	//引入正则表达式
//自定义头文件
#include "sysOpera.h"
#include "data.h"


//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
char *op_to_string(OP op){
	switch(op){
		case ADD_EMPLOYEE:	return "ADD_EMPLOYEE";
		case DELETE_EMPLOYEE:	return "DELETE_EMPLOYEE";
		case UPDATE_EMPLOYEE:	return "UPDATE_EMPLOYEE";
		case INQUR_EMPLOYEE:	return "INQUR_EMPLOYEE";
		default:	return "EMPLOYEE_UNKNOWN";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的OP枚举值
*/
OP string_to_op(const char *str){
	if(strcmp(str,"ADD_EMPLOYEE") == 0 )
	return ADD_EMPLOYEE;
	if(strcmp(str,"DELETE_EMPLOYEE") == 0 )
	return DELETE_EMPLOYEE;
	if(strcmp(str,"UPDATE_EMPLOYEE") == 0 )
	return UPDATE_EMPLOYEE;
	if(strcmp(str,"INQUR_EMPLOYEE") == 0 )
	return INQUR_EMPLOYEE;
	return EMPLOYEE_UNKNOWN;	//默认返回
}

//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *gender_to_string(Gender gender){
	switch(gender){
		case MALE:	return "MALE";
		case FEMALE:	return "FEMALE";
		default:	return "GENDER_UNKNOWN";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Gender枚举值
*/
Gender string_to_gender(const char *str){
	if(strcmp(str,"MALE") == 0 )
	return MALE;
	if(strcmp(str,"FEMALE") == 0 )
	return FEMALE;
	return GENDER_UNKNOWN;	//默认返回男性
}
//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *department_to_string(Department department){
	switch(department){
		case SALES:	return "SALES";
		case MARKETING:	return "MARKETING";
		case AFTER_SALE:	return "AFTER_SALE";
		default:	return "DEPT_UNKNOWN";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Department枚举值
*/
Department string_to_department(const char *str){
	if(strcmp(str,"SALES") == 0 )
	return SALES;
	if(strcmp(str,"MARKETING") == 0 )
	return MARKETING;
	if(strcmp(str,"AFTER_SALE") == 0 )
	return AFTER_SALE;
	return DEPT_UNKNOWN;	//默认返回
}
//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *title_to_string(Title title){
	switch(title){
		case MANAGER:	return "MANAGER";
		case CAPTAIN:	return "CAPTAIN";
		case SALES_WORKER:	return "SALES_WORKER";
		case MARKETING_WORKER:	return "MARKETING_WORKER";
		case AFTER_SALE_WORKER:	return "AFTER_SALE_WORKER";
		default:	return "TITLE_UNKNOWN";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Title枚举值
*/
Title string_to_title(const char *str){
	if(strcmp(str,"MANAGER") == 0 )
	return MANAGER;
	if(strcmp(str,"CAPTAIN") == 0 )
	return CAPTAIN;
	if(strcmp(str,"SALES_WORKER") == 0 )
	return SALES_WORKER;
	if(strcmp(str,"MARKETING_WORKER") == 0 )
	return MARKETING_WORKER;
	if(strcmp(str,"AFTER_SALE_WORKER") == 0 )
	return AFTER_SALE_WORKER;
	return TITLE_UNKNOWN;	//默认返回
}
//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *role_to_string(Role role){
	switch(role){
		case ROLE_ADMIN:	return "ROLE_ADMIN";
		case ROLE_EMPLOYEE:	return "ROLE_EMPLOYEE";
		default:	return "ROLE_UNKNOWN";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Role枚举值
*/
Role string_to_role(const char *str){
	if(strcmp(str,"ROLE_ADMIN") == 0 )
	return ROLE_ADMIN;
	if(strcmp(str,"ROLE_EMPLOYEE") == 0 )
	return ROLE_EMPLOYEE;
	return ROLE_UNKNOWN;	//默认返回
}










