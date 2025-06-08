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

typedef struct User {
	int id;
	char userName[32];
	char password[32];
} User;


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

 
int main(int argc, char *argv[]) {
	char sql[] = "select * from user";
	
	int count = 0;
	
	//User *user = NULL;
	//selectData(sql, user, &count );
	User *user = selectData(sql, &count);
	
	
	printf("out:%d\n",count );
	
	for(int i = 0; i < count; i ++){
		printf("id=%d , name=%s , password=%s \n", user[i].id, user[i].userName, user[i].password );
	}
	
	free(user);
	
    return 0;
}






