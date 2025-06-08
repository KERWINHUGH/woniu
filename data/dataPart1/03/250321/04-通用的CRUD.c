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



// 通用的增删改查函数：
int updateData( char *sql, Param params[],  int length );


void selectData(  );



// -----------------------------------------------------------
int main(int argc, char *argv[]) {
/*
	// 新增
	char sql[] = "insert into user (user_name, password)values (?, ?)";
	Param params[2];
	params[0].type = Type_string;
	params[0].value.s = "小丽丽";
	params[1].type = Type_string;
	params[1].value.s = "x123456";

	// 删除
	char sql[] = "delete from user where id = ? ";
	Param params[1];
	params[0].type = Type_int;
	params[0].value.i = 6 ;
	
*/
	// 修改
	char sql[] = "update user set user_name = ?, password = ? where id = ?";
	Param params[3];
	params[0].type = Type_string;
	params[0].value.s = "张三";
	params[1].type = Type_string;
	params[1].value.s = "z889900";
	params[2].type = Type_int;
	params[2].value.i = 7 ;
	
	int length = sizeof(params) / sizeof(params[0]);
	
	int rows = updateData(sql,params , length );
	printf("sql执行影响行数是：%d \n", rows );

	
    return 0;
}
// ------------------------------------------------------------
// 通用的增删改查函数：
int updateData( char *sql, Param params[],  int length ){
	char db_name[] = "system.db";
	// 1: 打开数据库
	sqlite3 *db;
	int rc;
	//链接数据库
	rc = sqlite3_open(db_name, &db);
	if(rc != SQLITE_OK){
		perror("数据库打开失败！");
		return -1;
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
        return -1;	
	}
	
	//使用循环给问号赋值：
	for(int i = 0; i < length; i++){
		if( params[i].type == Type_int ){
			sqlite3_bind_int(stmt , i + 1, params[i].value.i );
		
		}else if( params[i].type == Type_string ){
			sqlite3_bind_text(stmt , i+ 1, params[i].value.s , -1 , SQLITE_STATIC );
		}
	}
	
	// 执行sql
	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE ){
		fprintf(stderr, "SQL执行失败: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
	}
	// 如果正常执行，得到影响行数
	int rows = sqlite3_changes(db);
	// 回收资源
	sqlite3_finalize(stmt);
    sqlite3_close(db);

	return rows;
}

























