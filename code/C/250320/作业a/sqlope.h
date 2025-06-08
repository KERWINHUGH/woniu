/***************************************************
# File Name:    01-数据库操作.h
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Mar 2025 02:11:55 PM CST
****************************************************/
#ifndef SQL_OPERATE_H
#define SQL_OPERATE_H

typedef struct User {
	int id;
	char userName[32];
	char password[32];
} User;

// 插入操作
void insertData(char *sql);
// 删除操作
void deleteeData(char *sql);
// 增删改操作
void updateData(char *sql);
// 查询数据
User* selectData(char *sql , int *count );

#endif



