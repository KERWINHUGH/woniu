/***************************************************
# File Name:    01-数据库操作.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Mar 2025 02:11:55 PM CST
****************************************************/

#ifndef SQL_CRUD_H
#define SQL_CRUD_H

#include <sqlite3.h>
#include "data.h"

// 针对参数，我们应该写一个结构体
typedef struct Param {
	// 枚举用来描述参数的类型：
	enum { 
		Type_int,
		Type_float,
		Type_string,
		Type_gender,
		Type_department,
		Type_title,
		Type_role	
	 }Type;
	 
	// 共用体：用来描述参数的值
	//表示Employee表的字段
	union {
		int id;						//- 工号
		char *name;		//- 名字
		char *password;	//- 密码 
		int age;					//- 年龄
		float salary;				//- 工资
		//枚举性别
		Gender genders;				//- 性别  使用枚举  - `MALE`、`FEMALE`
		//枚举部门
		Department departments;		//- 部门  - `SALES`、`MARKETING`、`AFTER_SALE`
		//枚举职位
		Title titles;				//- 职位  - `MANAGER`、`SALES`、`CAPTAIN`、`WORKER`、`AFTER_SALE`
		//枚举角色
		Role roles;					//- 角色  - Admin   employees
	}value;

} Param;

extern char db_name[];


// 通用的增删改查函数：
int sql_Employee_update( char *sql, Param params[],  int length );
// 通用的查询函数：
sqlite3_stmt* selectEmployeeData( char *sql, Param params[],  int length );
// 把数据转换成结构体的函数
Employee* dataToEmployee( sqlite3_stmt *stmt, int *count );






#endif





















