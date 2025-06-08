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

// 查询要使用到的回调函数
int showInfo(
		  void*,    /* 用户提供的上下文指针，对应于 sqlite3_exec() 的第四个参数 */
		  int,      /* 结果集中的列数 */
		  char**,   /* 指向结果行中各列数据的指针数组 */
		  char**    /* 指向结果行中各列名称的指针数组 */
);

// 增删改操作
void updateData(char *sql){
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
	
	int result =  sqlite3_exec(
							  db,                                  /* 打开的数据库指针 */
							  sql,                           /* sql语句 */
							  NULL,  						/* 回调函数:返回查询结果 */
							  NULL,                                /* 传递给回调函数的参数,可以设置为NULL */
							  &errmsg                              /* 错误信息 */
							);
	
	if(result == SQLITE_OK){
		puts("操作成功！");
	}else{
		// 如果失败，打印出错信息．
		fprintf(stderr, "SQL错误: %s\n", errmsg );
		sqlite3_free(errmsg);
	}
	
	// 3: 关闭连接
	sqlite3_close(db);
}

// 查询数据
void selectData(char *sql){
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
	
	int result =  sqlite3_exec(
							  db,                                  /* 打开的数据库指针 */
							  sql,                           	   /* sql语句 */
							  showInfo,  						   /* 回调函数:返回查询结果 */
							  NULL,                                /* 传递给回调函数的参数,可以设置为NULL */
							  &errmsg                              /* 错误信息 */
							);
							
	
	if(result == SQLITE_OK){
		puts("操作成功！");
	}else{
		// 如果失败，打印出错信息．
		fprintf(stderr, "SQL错误: %s\n", errmsg );
		sqlite3_free(errmsg);
	}
	// 3: 关闭连接
	sqlite3_close(db);					
}

int showInfo(void* no_used,int cols,char** colValues,char** cloNames ){
	for( int i = 0; i < cols; i++ ){
		printf("列名：%s  : %s \n",  cloNames[i] , colValues[i]);
	}
	puts("-----------------------------");
	return 0;
}

 
int main(int argc, char *argv[]) {
	char username[32];
	char password[32];
	


	//printf("username: %s, password: %s \n", username, password);
	
	char sql[256]= {0};
	//sprintf( sql, "insert into user (user_name, password) values ('%s', '%s')",username, password );
	//char sql[] = "update user set user_name = 'jack', password = 'loverose' where id = 1 ";
	//char sql[] = "delete from user where id = 1";
	//updateData(sql);

	// 为了防止sql注入的问题，我们不应该使用字符串拼接的方式，生成sql语句。
	sprintf(sql, "select * from user where user_name = '%s' and password = '%s' " , "abc", "' or 1=1 or 2='2");
	
	selectData(sql);
	
    return 0;
}






