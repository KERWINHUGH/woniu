/***************************************************
# File Name:    01-数据库操作.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Mar 2025 02:11:55 PM CST
****************************************************/

#ifndef SQL_CRUD_H
#define SQL_CRUD_H

#include <sqlite3.h>
#include "EMS.h"

// 针对参数，我们应该写一个结构体
typedef struct Param {
	// 枚举用来描述参数的类型：
	enum { 
		Type_int,
		Type_string,
		
	 }type;
	 
	// 共用体：用来描述参数的值
	//表示Admin表的字段
	union {
		int id;
		char *name;
		char *password;
	}value;

} Param;
/*
typedef struct User {
	int id;
	char userName[32];
	char password[32];
} User;
*/

extern char db_name[];


// 通用的增删改查函数：
int sql_admin_update( char *sql, Param params[],  int length );
// 通用的查询函数：
sqlite3_stmt* selectAdminData( char *sql, Param params[],  int length );
// 把数据转换成结构体的函数
Admin* dataToAdmin( sqlite3_stmt *stmt, int *count );






#endif





















