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
#include <unistd.h>

//用户数据库名称
char db_name[] = "EMS.db";


// Employee结构体增删改函数：
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
	//puts("sql_Employee_update问号赋值----------------------------");
	//使用循环给问号赋值：
	// 按参数顺序依次绑定（每个Param对应一个?占位符）
    for (int i = 0; i < length; i++) {
        int param_index = i + 1; // SQLite参数索引从1开始

        if (params[i].Type == Type_int) {
            // 假设Param的value.id/int_value存储整数值
            sqlite3_bind_int(stmt , param_index, params[i].value.age );
        } else if (params[i].Type == Type_float) {
            // 假设Param的value.str_value存储字符串
            sqlite3_bind_int(stmt , param_index, params[i].value.salary);
        }else if (params[i].Type == Type_string) {
            // 假设Param的value.str_value存储字符串
            sqlite3_bind_text(stmt , param_index, params[i].value.name , -1 , SQLITE_STATIC );
            param_index =i+1;
			sqlite3_bind_text(stmt , param_index, params[i].value.password , -1 , SQLITE_STATIC );
        } else if (params[i].Type == Type_gender) {
            // 枚举类型转字符串
           const char* gender_str = gender_to_string(params[i].value.genders);
           sqlite3_bind_text(stmt, param_index, gender_str, -1, SQLITE_STATIC);
        } else if (params[i].Type == Type_department) {
            const char* department_str = department_to_string(params[i].value.departments);
            sqlite3_bind_text(stmt,param_index , department_str, -1, SQLITE_STATIC);
        }else if (params[i].Type == Type_title) {
            const char* title_str = title_to_string(params[i].value.titles);
            //printf("=================数据库新增title_str===========%s",title_str);
            sqlite3_bind_text(stmt, param_index, title_str, -1, SQLITE_STATIC);
        }else if (params[i].Type == Type_role) {
            const char* role_str = role_to_string(params[i].value.roles);
            // printf("=================数据库新增role_str===========%s",role_str);
            sqlite3_bind_text(stmt, param_index, role_str, -1, SQLITE_STATIC);
        }
    }	
    int retries = 3;
	while (retries--) {
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_BUSY) {
		    usleep(100000);  // 等待 100ms
		    continue;
		}
		break;
	}	/*	
	// 执行sql
	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE ){
		fprintf(stderr, "SQL执行失败: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
	}
	*/
	//puts("sql_Employee_update得到行数----------------------------");
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
	if(params != NULL){	
		//使用循环给问号赋值：
	//使用循环给问号赋值：
	// 按参数顺序依次绑定（每个Param对应一个?占位符）
		   for (int i = 0; i < length; i++) {
		    int param_index = i + 1; // SQLite参数索引从1开始

		    if (params[i].Type == Type_int) {
		        // 假设Param的value.id/int_value存储整数值
		        sqlite3_bind_int(stmt , param_index, params[i].value.age );
		    } else if (params[i].Type == Type_float) {
		        // 假设Param的value.str_value存储字符串
		        sqlite3_bind_int(stmt , param_index, params[i].value.salary );
		    }else if (params[i].Type == Type_string) {
		        // 假设Param的value.str_value存储字符串
		        sqlite3_bind_text(stmt , param_index, params[i].value.name , -1 , SQLITE_STATIC );
		        param_index =i+1;
				sqlite3_bind_text(stmt , param_index, params[i].value.password , -1 , SQLITE_STATIC );
		    } else if (params[i].Type == Type_gender) {
		        // 枚举类型转字符串
		       const char* gender_str = gender_to_string(params[i].value.genders);
		       sqlite3_bind_text(stmt, param_index, gender_str, -1, SQLITE_STATIC);
		    } else if (params[i].Type == Type_department) {
		        const char* department_str = department_to_string(params[i].value.departments);
		        sqlite3_bind_text(stmt,param_index , department_str, -1, SQLITE_STATIC);
		    }else if (params[i].Type == Type_department) {
		        const char* title_str = title_to_string(params[i].value.titles);
		        sqlite3_bind_text(stmt, param_index, title_str, -1, SQLITE_STATIC);
		    }else if (params[i].Type == Type_department) {
		        const char* role_str = role_to_string(params[i].value.roles);
		        sqlite3_bind_text(stmt, param_index, role_str, -1, SQLITE_STATIC);
		    }
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
		//printf("枚举操作--------------------------------count:%d--------------------\n",*count);
		const char* gender_str = sqlite3_column_text(stmt,5);
		//printf("gender_str:%s\n",gender_str);
		p[index].genders = string_to_gender(gender_str);

		const char* department_str = sqlite3_column_text(stmt,6);
		//printf("department_str:%s\n",department_str);
		p[index].departments = string_to_department(department_str);
		
		const char* title_str = sqlite3_column_text(stmt,7);
		//printf("title_str:%s\n",title_str);		
		p[index].titles = string_to_title(title_str);

		const char* role_str = sqlite3_column_text(stmt,8);
		//printf("role_str:%s\n",role_str);	
		p[index].roles = string_to_role(role_str);
		
		index++;
	}
	//puts("dataToEmployee---------------------------");
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

















