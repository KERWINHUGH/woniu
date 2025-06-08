/***************************************************
# File Name:    sqlite.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月20日 星期四 14时33分03秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
 
void insertData(){
	//1.先定义要打开数据库函数的两个参数
	//2.定义要打开数据库的名称
	char filename[] = "system.db";
	//3.定义打开数据库的指针
	sqlite3 *db;
	//4.打开数据库,参数传的是指针地址
	//5.再定义一个变量用于判断打开数据库是否成功
	int rc;
	rc = sqlite3_open(filename,&db);
	if(rc != SQLITE_OK){
		perror("打开数据库失败");
		return;
	}
	//6.打开数据库成功之后,先要定义sqlite3_exec执行sql语句的参数
	//7.先定义要执行的sql语句
	char sql[] ="insert into user (id,username,password,age,phone,address) values (1,'admin','admin123',23,13433334444,'江苏南京')";
	//8.定义要打印的错误信息
	char *errmsg = 0;
	//9.使用sqlite3_exec执行sql语句
	int result =0;
	result = sqlite3_exec(
				  db,                                  /* 打开的数据库指针 */
				  sql,                           		/* sql语句 */
				  NULL,  								/* 回调函数:返回查询结果 */
				  NULL,                               /* 传递给回调函数的参数,可以设置为NULL */
				  &errmsg                              /* 错误信息 */
				);
	//10.判断执行操作sql语句是否成功
	if(result == SQLITE_OK){
		printf("操作执行成功\n");
	}else{
	//11.如果错误，打印错误信息，并释放
		fprintf(stderr,"SQL执行错误：%s\n",errmsg);
	//12.释放内存,一般指sql语句执行后分配给errmsg的内存。
		sqlite3_free(errmsg);
	}
	
	//13.关闭数据库
	sqlite3_close(db);
	 
} 

int main(int argc, char *argv[]) {
	insertData();
    return 0;
}


