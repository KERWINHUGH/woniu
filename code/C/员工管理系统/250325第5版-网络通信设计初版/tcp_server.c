/***************************************************
# File Name:    system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月20日 星期四 21时55分11秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//1.引入头文件
#include <arpa/inet.h>
#include <sys/socket.h>
//用于互联网地址族，包括 sockaddr_in 结构和 IP 地址定义。
#include <netinet/in.h>
#include <unistd.h>
//使用线程
#include <pthread.h>
//自定义文件
//引入数据库操作文件
#include "sqlCRUD.h"
//引入系统用户结构体和json操作
#include "json.h"
//引入sql操作
#include "sqlCRUD.h"
#include "tcp_server.h"
//#include "common.h"

#define SERVER_ADDR "127.0.0.1"		//定义服务器地址
#define SERVER_PORT 8080			//定义服务器端口号
#define BUFF_SIZE 1024				//定义缓冲区大小

//处理用户发送的请求，并返回数据库查询结果
void server_write( int client_fd,char *op_str, char *json_buf){

	ssize_t count;
	//将传进来的op_str字符串（即用户相应的操作）转为枚举类型
	OP op = string_to_op( op_str );
	//通过操作选择相应的数据库操作
	switch(op){
		case ADD_ADMIN:
				//将传进来的json字符串转为对应结构体类型
				Admin  *p =json_to_Admin(json_buf);
				//取出sql操作需要的用户数据
				char *name = p->name;
				char *password = p->password; 
				// 新增的sql语句
				char sql[] = "insert into Admin (name, password)values (?, ?)";
				//定义参数类型和参数内容，然后将客户端传来的用户数据放入param结构体中（param结构体用于数据库的增删改查）
				Param params[2];
				params[0].type = Type_string;
				params[0].value.name = name;
				params[1].type = Type_string;
				params[1].value.password = password;
				//求出操作中的param结构体包含几个成员,即表中有几个字段
				int length = sizeof(params) / sizeof(params[0]);
				//执行数据库新增成员操作
				int rows = sql_admin_update(sql, params , length );
				if(rows < 0){
					printf( "数据库新增成员出错！\n" );
					return;
				}else{
					printf("sql执行影响行数是：%d \n", rows );
				} 
				free(p);
				break;
		default:
			printf("没有该操作");
				break;
		
	}
	//每次进行完增删改查操作都需要返回两张用户表
	//查询数据库，返回结构体
	char sql[] = "select * from Admin";
	//查询Admin表中全部数据
	sqlite3_stmt *stmt = selectAdminData(sql, NULL, 0 );
	
	//dataToAdmin函数返回一个结构体
	int Admin_quantity = 0;
	Admin *p = dataToAdmin(stmt, &Admin_quantity); 	
	//将数据库中查到的数据转为json字符串（结构体数组）
	char *json_str = Admin_array_to_json( p, Admin_quantity );
	printf("服务端查询后生成的json字符串是%s \n",json_str);
	//向客户端发送json消息	
    if(write(client_fd, json_str, strlen(json_str)) < 0){
    	perror("向客户端发送消息失败！\n");
    	return ;
    }
	free(json_str);		
}

//接收线程
//接收用户发送的请求，并使用write返回数据库查询结果
void *server_read(void *args){
	int client_fd = *(int *)args;
	while(1){
	//服务器进行交互
	char op_buf[128];	//客户端发送的操作字符串缓冲区
	char json_buf[BUFF_SIZE];	//客户端发送的json数据缓冲区
	char str[128];
	ssize_t count;		//count用于判断接受客户端发送的用户的消息大小
	
	//接收客户端发送的操作op
	read(client_fd,op_buf,sizeof(op_buf)-1);	
	printf("操作：%s\n",op_buf);
	
		//每次接受信息之前，应该先清空数组中的缓存
		memset(json_buf,0,sizeof(json_buf));
		count =	read(client_fd,json_buf,sizeof(json_buf)-1);
		//10.接收客户端消息，count大于0说明客户端一直在发送信息
		if(count >0){
			//接收到客户端发送的用户消息
			printf("json字符串：%s\n",json_buf);
			//处理用户发送的请求，根据操作对数据库进行相应操作，最后查询整个数据库，返回数据库修改后的查询结果
			server_write(client_fd, op_buf, json_buf);
		}else if(count == 0){
			printf("客户端关闭了\n");
			break;
		}else {
			perror("读取客户端信息错误");
			break;
		}
	}
	//关闭客户端
	close(client_fd);
	//释放线程参数
	free(args);
	return NULL;
}



int main(int argc, char *argv[]){
	//1.创建套接字
	//第三个参数:为0代表自动选择
	 int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
	 if(server_fd <0){
	 	perror("创建套接字失败");
	 	close(server_fd);
	 	exit(EXIT_FAILURE);
	 }
	 
	 //2.创建服务器端口结构体并设置端口协议，地址等信息
	 struct sockaddr_in server_addr = {0};	//创建空地址结构体
	 server_addr.sin_family = AF_INET;	//设置协议为ipv4
	 server_addr.sin_addr.s_addr = INADDR_ANY;	//代表接受任意ipv4的信息
	 server_addr.sin_port = htons(SERVER_PORT);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
	//3.绑定端口号
	if( bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("绑定端口号失败");
	 	close(server_fd);
	 	exit(EXIT_FAILURE);
	}
	//4.监听端口
	if( listen(server_fd, 5)<0){
		perror("监听端口失败");
	 	close(server_fd);
	 	exit(EXIT_FAILURE);
	}
	
	//5.到这代表有客户端连接
	puts("服务器正在监听8080");
	
	//6.接收客户端连接，可能是多个客户端，利用线程和循环去处理
	while(1){
		struct sockaddr_in client_addr = {0};	//创建客户端端口结构体
		socklen_t client_length = sizeof(client_addr);	//定义变量存储客户端结构体大小，用于accept函数作为参数
		//因为线程需要将client作为参数传递到线程函数中，故需要定义一个指针
		int *client_fd = malloc(sizeof(int));
		//执行接收客户端连接操作
		*client_fd = accept(server_fd, (struct sockaddr *)&client_addr,&client_length);
		if(*client_fd <0){
			perror("接收客户端连接失败");
		 	close(server_fd);
		 	exit(EXIT_FAILURE);
		}
		//8.接收客户端成功
		printf("客户端连接成功！id是：%d \n",*client_fd);
		
		//创建线程来和连接上来的客户端进行通信
		pthread_t pid;
				if(pthread_create(&pid ,NULL ,server_read ,client_fd) !=0){
			perror("pthread_create() error!");
			//创建线程失败则释放参数
			free(client_fd);
		}
		//分离线程,让系统自动去回收线程
		pthread_detach(pid);
	}
	
	//13.关闭连接
	close(server_fd);
	
	return 0;
	
}
