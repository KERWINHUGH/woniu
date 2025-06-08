/***************************************************
# File Name:    01-数据库操作.h
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Mar 2025 02:11:55 PM CST
****************************************************/
#ifndef SQL_OPERATE_H
#define SQL_OPERATE_H

// 针对参数，我们应该写一个结构体
typedef struct Param {
	// 枚举用来描述参数的类型：
	enum { 
		Type_int,
		Type_string,
		
	 }type;
	 
	// 共用体：用来描述参数的值
	union {
		int i;
		char *s;
	}value;

} Param;

typedef struct User {
	int id;
	char userName[32];
	char password[32];
} User;


extern char db_name[] = "system.db";


// 通用的增删改查函数：
int updateData( char *sql, Param params[],  int length );
// 能用的查询函数：
sqlite3_stmt* selectData( char *sql, Param params[],  int length );
// 把数据转换成结构体的函数
User* dataToUser( sqlite3_stmt *stmt, int *count );

#endif



