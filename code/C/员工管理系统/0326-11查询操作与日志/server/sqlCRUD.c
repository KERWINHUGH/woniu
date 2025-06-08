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
#include "sqlCRUD.h"

//用户数据库名称
char db_name[] = "EMS.db";


// aEmployee结构体增删改函数：
int sql_Employee_update( char *sql, Param params[],  int length ){
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
			sqlite3_bind_int(stmt , i + 1, params[i].value.id );
			sqlite3_bind_int(stmt , i + 2, params[i].value.age );
			sqlite3_bind_int(stmt , i + 3, params[i].value.salary );
		}else if( params[i].type == Type_string ){
			sqlite3_bind_text(stmt , i+ 1, params[i].value.name , -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 2, params[i].value.password , -1 , SQLITE_STATIC );
			//共用体枚举赋值
			sqlite3_bind_text(stmt , i+ 3, gender_to_string(params[i].value.genders ), -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 4, department_to_string(params[i].value.departments ), -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 5, title_to_string(params[i].value.titles ), -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 6, role_to_string(params[i].value.roles ), -1 , SQLITE_STATIC );
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

// Employee结构体的查询
sqlite3_stmt* selectEmployeeData( char *sql, Param params[],  int length ){
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
			sqlite3_bind_int(stmt , i + 1, params[i].value.id );
			sqlite3_bind_int(stmt , i + 2, params[i].value.age );
			sqlite3_bind_int(stmt , i + 3, params[i].value.salary );
		}else if( params[i].type == Type_string ){
			sqlite3_bind_text(stmt , i+ 4, params[i].value.name , -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 5, params[i].value.password , -1 , SQLITE_STATIC );
			//共用体枚举赋值
			sqlite3_bind_text(stmt , i+ 6, gender_to_string(params[i].value.genders ), -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 7, department_to_string(params[i].value.departments ), -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 8, title_to_string(params[i].value.titles ), -1 , SQLITE_STATIC );
			sqlite3_bind_text(stmt , i+ 9, role_to_string(params[i].value.roles ), -1 , SQLITE_STATIC );
		}
	}
	// 关闭数据库连接
	sqlite3_close(db);
	
	return stmt;
}

// 写一个函数，把查询到的数据转换成我们需要的结构体数据，接收数据库查询返回的表,即结构体数组
Employee* dataToEmployee( sqlite3_stmt *stmt , int *count ){
	Employee *p = NULL;
	int index = 0;
	while(sqlite3_step(stmt) == SQLITE_ROW){
		(*count)++;
		p = realloc( p, sizeof(Employee) * (*count));
	
		p[index].id = sqlite3_column_int(stmt,0);
		strcpy( p[index].name, sqlite3_column_text(stmt,1) );
		strcpy( p[index].password , sqlite3_column_text(stmt,2) );
		
		p[index].age = sqlite3_column_int(stmt,3);
		p[index].salary = sqlite3_column_double(stmt,4);
		//枚举操作
		p[index].genders = sqlite3_column_int(stmt,5);
		p[index].departments = sqlite3_column_int(stmt,6);
		p[index].titles = sqlite3_column_int(stmt,7);
		p[index].roles = sqlite3_column_int(stmt,8);
		/*
		string_to_gender(p[index].genders ) = sqlite3_column_int(stmt,5);
		string_to_department(p[index].departments ) = sqlite3_column_int(stmt,6);
		string_to_title(p[index].titles ) = sqlite3_column_int(stmt,7);
		string_to_role(p[index].roles ) = sqlite3_column_int(stmt,8);
		*/
		index++;
	}
	// 回收掉stmt
	sqlite3_finalize(stmt);
	// 返回转换好的数据
	return p;
}

/*
// -----------------------------------------------------------
int main(int argc, char *argv[]) {

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
	
	int rows = sql_Employee_update(sql,params , length );
	printf("sql执行影响行数是：%d \n", rows );


	// 查询 ---------------------------------------
	//char sql[] = "select * from user";
	//char sql[] = "select * from user where id = ?";
	char sql[] = "select * from user limit ?, ?";
	
	Param params[2];
	params[0].type = Type_int;
	params[0].value.i = 3 ;
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

*/

















