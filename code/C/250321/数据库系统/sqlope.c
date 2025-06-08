#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "sqlope.h"

char db_name[] = "system.db";

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
*/

	// 查询 ---------------------------------------
	//char sql[] = "select * from user";
	//char sql[] = "select * from user where id = ?";
	char sql[] = "select * from user limit ?, ?";
	
	Param params[2];
	params[0].type = Type_int;
	params[0].value.i = 0 ;
	params[1].type = Type_int;
	params[1].value.i = 3 ;
	
	int length = sizeof(params) / sizeof(params[0]);
	sqlite3_stmt *stmt = selectData(sql, params, length );
	
	int count = 0;
	User *user = dataToUser(stmt, &count); 	
	for(int i = 0; i < count; i++){
		printf("id=%d , name=%s , password=%s \n", user[i].id, user[i].userName, user[i].password );
	}


	free(user);
	
    return 0;
}
// ------------------------------------------------------------
// 通用的增删改查函数：
int updateData( char *sql, Param params[],  int length ){
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

// 通用的查询
sqlite3_stmt* selectData( char *sql, Param params[],  int length ){
	// 1: 打开数据库
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
	//使用循环给问号赋值：
	for(int i = 0; i < length; i++){
		if( params[i].type == Type_int ){
			sqlite3_bind_int(stmt , i + 1, params[i].value.i );
		
		}else if( params[i].type == Type_string ){
			sqlite3_bind_text(stmt , i+ 1, params[i].value.s , -1 , SQLITE_STATIC );
		}
	}
	// 关闭数据库连接
	sqlite3_close(db);
	
	return stmt;
}

// 写一个函数，把stmt转换成我们需要的数据
User* dataToUser( sqlite3_stmt *stmt , int *count ){
	User *user = NULL;
	int index = 0;
	while(sqlite3_step(stmt) == SQLITE_ROW){
		(*count)++;
		user = realloc( user, sizeof(User) * (*count));
		
		user[index].id = sqlite3_column_int(stmt,0);
		strcpy( user[index].userName , sqlite3_column_text(stmt,1) );
		strcpy( user[index].password , sqlite3_column_text(stmt,2) );
		
		index++;
	}
	// 回收掉stmt
	sqlite3_finalize(stmt);
	// 返回转换好的数据
	return user;
}

