/***************************************************
# File Name:    01-数据库操作.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Mar 2025 02:11:55 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "sqlope.h"

// 插入操作
void insertData(char *sql){
	char db_name[] = "system.db";
	// 1: 打开数据库
	sqlite3 *db;
	int rc;
	//链接数据库
	rc = sqlite3_open(db_name, &db);
	if(rc != SQLITE_OK){
		perror("数据库打开失败！");
		return;
	}
	
	// 2: 执行sql语句
	char *errmsg = 0;
	
	// 预处理：对带问号的sql进行处理 ------------------------------------------	
	sqlite3_stmt *stmt;
	int result =  sqlite3_prepare_v2(
				  db,             	   /* Database handle */
				  sql,			       /* SQL statement, UTF-8 encoded */
				  -1,           	   /* Maximum length of zSql in bytes. */
				  &stmt,               /* OUT: Statement handle */
				  NULL                 /* OUT: Pointer to unused portion of zSql */
				);
	if(result != SQLITE_OK){
		fprintf(stderr, "SQL准备失败: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;	
	}	
				
	// 把值写到，把问号中
	sqlite3_bind_text(stmt , 1, "mike", -1 , SQLITE_STATIC );	//写用户名
	sqlite3_bind_text(stmt , 2, "1234", -1 , SQLITE_STATIC );	//写入密码
	sqlite3_bind_int(stmt , 3, 4 );		//写入年龄
		
	// 执行sql
	int rc2 = sqlite3_step(stmt);
	printf("执行的状态码：%d \n", rc2 );
	
	/*
	if(rc2 != SQLITE_DONE){
		fprintf(stderr, "SQL执行失败: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;	
	}
	*/
	// 得到影响行数：
	int num = sqlite3_changes(db);
	printf("影响行数：%d \n", num);
	
	// 3: 关闭连接
	sqlite3_close(db);
}



// 查询数据
User* selectData(char *sql , int *count ){
	char db_name[] = "system.db";
	// 打开数据库: 1
	sqlite3 *db;
	int rc;
	//链接数据库
	rc = sqlite3_open(db_name, &db);
	if(rc != SQLITE_OK){
		perror("数据库打开失败！");
		return NULL;
	}
	// 2: 执行sql语句
	char *errmsg = 0;
	// 预处理：对带问号的sql进行处理 ------------------------------------------	
	sqlite3_stmt *stmt;
	int result =  sqlite3_prepare_v2(
				  db,             	   /* Database handle */
				  sql,			       /* SQL statement, UTF-8 encoded */
				  -1,           	   /* Maximum length of zSql in bytes. */
				  &stmt,               /* OUT: Statement handle */
				  NULL                 /* OUT: Pointer to unused portion of zSql */
				);
	if(result != SQLITE_OK){
		fprintf(stderr, "SQL准备失败: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;	
	}	
	
	User *user = NULL;
	//int count = 0;
	printf("-begin:%d--------- \n", *count );

	int index = 0;
	while(sqlite3_step(stmt) == SQLITE_ROW){
		(*count)++;
		
		printf("-------%d--------- \n", *count );
		
		user = realloc( user, sizeof(User) * (*count));
		
		user[index].id = sqlite3_column_int(stmt,0);
		strcpy( user[index].userName , sqlite3_column_text(stmt,1) );
		strcpy( user[index].password , sqlite3_column_text(stmt,2) );
		
		index++;
	}

	// 3: 关闭连接
	sqlite3_close(db);
	
	printf("一共有 %d 个数据\n", *count);
	return user;
}






