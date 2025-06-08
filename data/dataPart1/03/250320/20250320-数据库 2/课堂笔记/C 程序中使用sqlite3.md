## C 程序中使用sqlite3

### 1：使用步骤

- **安装**：使用`sudo apt install libsqlite3-dev`让Linux安装sqlite3开发库
- **引入**：c文件引入`sqlite3.h`头文件
- **打开数据库**：使用`sqlite3_open`函数打开数据库
- **执行**：使用`sqlite3_exec`来执行sql语句,比如创建表、增删查改数据等
- **关闭数据库**：使用`sqlite3_close`来关闭数据库
- 编译：代码写好后进行gcc编译时，需要加上`-lsqlite3`参数。比如`gcc xxx.c -o sqldemo -lsqlite3`

### 2：操作函数

api大全：https://sqlite.readdevdocs.com/cintro.html

#### （1）sqlite3_open

- 语法

  ```c
  int sqlite3_open(const char *filename, sqlite3 **ppDb);
  
  例子：
  sqlite3 *db;
  int rc;
  //链接数据库
  rc = sqlite3_open("stu.db",&db);
  ```

- 功能:链接数据库

- 参数

  - `filename`: 数据库文件的名称。如果文件不存在，SQLite 会尝试创建它。
  - `ppDb`: 是指向 `sqlite3` 结构体指针的指针。当函数执行成功后，这个指针会被设置为指向一个打开的数据库实例

- 返回值

  - 函数返回一个整数状态码。`SQLITE_OK` (0) 表示成功，其他任何返回值都表示失败

#### （2）sqlite3_exec

- 功能：执行sql语句

- 语法-

  ```c
  int sqlite3_exec(
    sqlite3*,                                  /* 打开的数据库指针 */
    const char *sql,                           /* sql语句 */
    int (*callback)(void*,int,char**,char**),  /* 回调函数:返回查询结果 */
    void *pArg,                                /* 传递给回调函数的参数,可以设置为NULL */
    char **errmsg                              /* 错误信息 */
  );
  
  /* 回调函数说明：*/
  sqlite3_callback 通常指的是传递给 sqlite3_exec() 函数的第三个参数，这是一个用户定义的回调函数。当 sqlite3_exec() 执行一个 SQL 查询（如 SELECT 语句）并返回结果行时，它会调用这个回调函数来处理每一行的数据。
  回调函数的签名是固定的，以便 SQLite 能够正确地调用它。这个签名通常如下：
  typedef int (*sqlite3_callback)(
    void*,    /* 用户提供的上下文指针，对应于 sqlite3_exec() 的第四个参数 */
    int,      /* 结果集中的列数 */
    char**,   /* 指向结果行中各列数据的指针数组 */
    char**    /* 指向结果行中各列名称的指针数组 */
  
  ```

- 参数

  - 第一个参数是一个打开的数据库实例，之前由 `sqlite3_open` 打开。
  - 第二个：`sql` 是要执行的SQL语句字符串。可以包含一个或多个由分号分隔的SQL命令。
  - 第三个：callback是一个指向函数的指针，这个函数会被每一行结果调用一次。如果不需要处理结果集，则可以为NULL。
    - 该回调函数的签名应该符合`int callback(void *NotUsed, int argc, char **argv, char **azColName)`，其中：
      - `NotUsed` 是sqlite3_exec中用户提供的第四个参数。
      - `argc` 表示结果集中的列数。
      - `argv` 是一个字符串数组，包含每一列的值。
      - `azColName` 是一个字符串数组，包含每一列的名称。
  - 第四个参数: pArg
    - 这是一个用户提供的上下文指针，它将被传递给回调函数（如果提供了回调函数的话）。
    - 您可以使用这个指针来传递任何您希望在回调函数中访问的数据或状态信息。
    - 如果不需要传递任何上下文信息给回调函数，可以将此参数设置为 `NULL`。
  - `errmsg` 如果不为NULL，任何错误信息都会被写入到它指向的位置。使用 `sqlite3_free()` 来释放这个错误信息的内存

- 返回值

  - 返回 `SQLITE_OK` (0) 表示成功，其他值表示失败。失败时，如果 `errmsg` 不为NULL，它将指向一个错误消息

#### （3）sqlite3_free

- 功能：释放内存,一般指sql语句执行后分配给errmsg的内存。

- 语法

  ```c
  void sqlite3_free(void*);
  
  例子：sqlite3_free(err_message);
  //err_message 是执行sql失败之后的错误信息
  ```

- 参数

  - 接受一个指针，该指针必须是由sqlite分配的内存块的指针，通常是在之前的 `sqlite3_exec` 调用中通过 `errmsg` 返回的错误消息.如果sql语句执行成功，一般不用执行该函数

- 返回值：无

#### （4）sqlite3_close

- 功能:关闭一个打开的数据库连接

- 语法

  ```c
  int sqlite3_close(sqlite3*);
  例子：
  sqlite3_close(db);
  ```

- 参数

  - 接受一个指向 `sqlite3` 结构体的指针，这个指针代表一个打开的数据库实例

- 返回值

  - 如果成功关闭数据库，返回 `SQLITE_OK`。如果作为参数传递给 `sqlite3_close` 的数据库实例有尚未完成的操作（例如，未完成的准备语句、未关闭的BLOB句柄等），则返回 `SQLITE_BUSY`

#### （4）sqlite3_changes

- 功能：得到数据库连接上次调用`sqlite3_exec`以来被修改、插入或删除的行数

- 语法

  ```c
  int  sqlite3_changes(db);
  ```

- 参数

  - db:接受一个指向 `sqlite3` 结构体的指针，这个指针代表一个打开的数据库实例

- 返回值

  - 得到数据库连接上次调用`sqlite3_exec`以来被修改、插入或删除的行数，如果没有更改，则返回0



#### （5）增删改操作：

> 因为，增删改操作，都是影响数据的行的，所以，它们可以归为一类操作：

``` c
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

void insertData(){
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
		
	char sql[] = "insert into user (user_name, password) values ('admin', 'a1234') ";
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
 
int main(int argc, char *argv[]) {

	insertData();

    return 0;
}
```

### 3: 使用预处理：

- 示例代码：

  ``` c
  #include <stdio.h>
  #include <stdbool.h>
  #include <string.h>
  #include <stdlib.h>
  
  #include <sqlite3.h>
  
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
  	//sqlite3_bind_text(stmt , 1, "mike", -1 , SQLITE_STATIC );
  	//sqlite3_bind_text(stmt , 2, "1234", -1 , SQLITE_STATIC );
  	
  	sqlite3_bind_int(stmt , 1, 4 );
  		
  	// 执行sql
  	int rc2 = sqlite3_step(stmt);		
  	/*
  	if(rc2 != SQLITE_OK){
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
  
  int main(int argc, char *argv[]) {
  	char username[32];
  	char password[32];
  	
      // 传两个字符参数
  	//char sql[] = "insert into user (user_name, password) values ( ? , ? )";
      
      // 传一个int 参数
  	char sql[] = "delete from user where id >= ? ";
  	
  	updateData(sql);
  	
      return 0;
  }
  
  ```

  

- 查询并把数据封装成结构体数组：

  ``` c
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
  ```

  



