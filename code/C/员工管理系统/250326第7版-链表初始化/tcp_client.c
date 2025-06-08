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

#include <arpa/inet.h>
#include <sys/socket.h>
//用于互联网地址族，包括 sockaddr_in 结构和 IP 地址定义。
#include <netinet/in.h>
#include <unistd.h>

#include "cJSON.h"
#include "json.h"
#include "data.h"			//引入系统所需要的结构体
#include "sysOpera.h"		//引入用户输入验证
#include "tcp_client.h"
//#include "tcp_server.h"
//#include "common.h"

//创建客户端连接并发送用户操作
Admin * create_client(OP op, int *Admin_quantity){
	//1.创建套接字
	//第三个参数:为0代表自动选择
	 int client_fd = socket(AF_INET, SOCK_STREAM, 0); 
	 if(client_fd <0){
	 	perror("创建套接字失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	 }	 
	 //2.创建服务器端口结构体并设置端口协议，地址等信息
	 struct sockaddr_in server_addr = {0};	//创建空地址结构体
	 server_addr.sin_family = AF_INET;	//设置协议为ipv4
	 server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);	//127.0.0.1代表客户端本机
	 server_addr.sin_port = htons(SERVER_PORT);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
	//3.连接
	if( connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("连接失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	}
	puts("连接成功");
	//向客户端发送Admin表的操作请求，并接收返回的新Admin表(结构体数组)
	Admin *admin = client_write( client_fd, op,Admin_quantity);
	close(client_fd);	
	return admin;
}	

//客户端通信发送用户Admin的操作与用户数据
Admin* client_write(int client_fd ,OP op, int *Admin_quantity){
	//客户端进行交互
	//puts("0.增加管理员 1.删除管理员 2.修改管理员 3.查询管理员 4.增加用户 5.删除用户 6.修改用户 7.查询用户");
	//向服务器发送操作信息
	//将枚举转为字符串，然后进行发送（字符串不用考虑字节序问题）
	char *op_str = op_to_string( op );
	if(write(client_fd, op_str, strlen(op_str)) < 0){
		perror("向服务端发送操作失败！\n");
	}
	Admin *p =NULL;
	switch(op){
		case ADD_ADMIN:	
				//增Admin操作
				puts("增Admin操作");
				p = clientAddAdmin(client_fd);
				return p;	 
		case DELETE_ADMIN:
				//删Admin操作
				puts("删Admin操作");
				p = clientDeleteAdmin(client_fd);
				return p;
		case MODIFY_ADMIN:
				//改Admin操作
				puts("改Admin操作");
				p = clientUpdateAdmin(client_fd);
				return p;
		case INQUR_ADMIN:
				//查Admin操作
				puts("查Admin操作");
				p = clientInqurAdmin(client_fd,Admin_quantity);
				 return p;;			
		default:
			puts("op error!");
			return NULL;	
		}
}

//查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
bool adminName_is_exist( int client_fd, char *name ){
	//应先查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
	int Admin_quantity= 0;
	Admin *p = clientInqurAdmin(client_fd,&Admin_quantity);
	int len = sizeof(p)/sizeof(p[0]);
	//循环遍历数据表结构体数组是否存在该用户
	for(int i=0; i<len; i++){
		if(strcmp(p[i].name ,name) != 0){
			printf("用户名不存在 \n");
			return false;
		}else{
			printf("找到该用户 \n");
			return true;
		}
	}			
}
//查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
bool adminPassword_is_exist(int client_fd, char *password){
	//应先查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
	int Admin_quantity= 0;
	Admin *p = clientInqurAdmin(client_fd,&Admin_quantity);
	int len = sizeof(p)/sizeof(p[0]);
	//循环遍历数据表结构体数组判断该用户密码是否正确
	for(int i=0; i<len; i++){
		if(strcmp(p[i].password ,password) != 0){
			printf("用户密码错误 \n");
			return NULL;
		}else{
				printf("密码正确 \n");
				return true;
			}
	}
}
//跟新管理员用户操作-----增操作
Admin *clientAddAdmin(int client_fd){
	char str[BUFF_SIZE];	//客户端发送消息的缓冲区	
	char *ret_name ;		//判断用户名验证
	char *ret_pass ;		//判断用户密码验证
	//查询数据库，根据返回的表，遍历查询用户名是否存在，不存在则继续判断密码是否正确
	Admin admin = {0};
	printf("请输入用户名：\n");
	ret_name = name_verifi( admin.name );
	if(ret_name == NULL){
		printf("用户名输入不合法 \n");
		return NULL;
	}else{
		if(adminName_is_exist(client_fd,admin.name) ==false ){
			printf("请输入密码：\n");
			ret_pass = password_verifi( admin.password );
			if(ret_pass == NULL){
				printf("密码输入不合法 \n");
				return NULL;
			}
		}
	}
	//向服务器发送操作信息
	//usleep(500000);//模拟间隔发送
	//通过json先转换用户信息
	char* json_str = Admin_to_json( &admin );
	//向服务器发送用户信息
	if(write(client_fd, json_str, strlen(json_str)) < 0){
		perror("向服务端发送用户信息失败！\n");
	}	
	//读取服务端数据，并将得到的数据转换为Admin结构体数组
	int Admin_quantity= 0;
	Admin *p = client_read(client_fd,&Admin_quantity);
	return p;
}
//跟新管理员用户操作-----删操作
Admin *clientDeleteAdmin(int client_fd){
	char str[BUFF_SIZE];	//客户端发送消息的缓冲区	
	char *ret_name ;		//判断用户名验证
	char *ret_pass ;		//判断用户密码验证
	Admin admin = {0};
	printf("请输入要删除用户的用户名：\n");
	ret_name = name_verifi( admin.name );
	if(ret_name == NULL){
			printf("用户名输入不合法 \n");
			return NULL;
		}else{
			if(adminName_is_exist(client_fd,admin.name) !=false ){
				printf("请输入密码：\n");
				ret_pass = password_verifi( admin.password );
				if(ret_pass == NULL){
					printf("密码输入不合法 \n");
					return NULL;
				}else{
					if(adminPassword_is_exist(client_fd, admin.password) ==false ){
						return NULL;
					}
				}
			}
		}
	//向服务器发送操作信息
	//通过json先转换用户信息
	char* json_str = Admin_to_json( &admin );
	//向服务器发送用户信息
	if(write(client_fd, json_str, strlen(json_str)) < 0){
		perror("向服务端发送用户信息失败！\n");
	}	
	//读取服务端数据，并将得到的数据转换为Admin结构体数组
	int Admin_quantity= 0;
	Admin *p = client_read(client_fd,&Admin_quantity);
	return p;
}
//跟新管理员用户操作-----改操作
Admin *clientUpdateAdmin(int client_fd){
	char str[BUFF_SIZE];	//客户端发送消息的缓冲区	
	char *ret_name ;		//判断用户名验证
	char *ret_pass ;		//判断用户密码验证
	char* json_str ;		//通过json先转换用户信息
	Admin admin = {0};
	//操作为修改需要输入修改用户的用户名，查询数据库并判断用户是否存在
	printf("请输入要修改用户的用户名：\n");
	ret_name = name_verifi( admin.name );
	if(ret_name == NULL){
			printf("用户名输入不合法 \n");
			return NULL;
		}else{
			if(adminName_is_exist(client_fd, admin.name) !=false ){
				printf("请输入密码：\n");
				ret_pass = password_verifi( admin.password );
				if(ret_pass == NULL){
					printf("密码输入不合法 \n");
					return NULL;
				}else{
					if(adminPassword_is_exist(client_fd, admin.password) ==false ){
						return NULL;
					}
				}
			}
		}
	//用户信息验证完成则输入新的用户名和密码
	printf("请输入用户名：\n");
	ret_name = name_verifi( admin.name );
	if(ret_name == NULL){
		printf("用户名输入不合法 \n");
		return NULL;
	}else{
		printf("请输入密码：\n");
		ret_pass = password_verifi( admin.password );
		if(ret_pass == NULL){
			printf("密码输入不合法 \n");
			return NULL;
		}
	}
	//通过json先转换用户信息
	json_str = Admin_to_json( &admin );
	//向服务器发送用户信息
	if(write(client_fd, json_str, strlen(json_str)) < 0){
		perror("向服务端发送用户信息失败！\n");
	}	
	//读取服务端数据，并将得到的数据转换为Admin结构体数组
	int Admin_quantity= 0;
	Admin *p = client_read(client_fd,&Admin_quantity);
	return p;
}

//查询Admin表并返回结构体数组
Admin *clientInqurAdmin(int client_fd,int *Admin_quantity){
	//读取服务端数据，并将得到的数据转换为Admin结构体数组
	//puts("查前");
	Admin *p = client_read(client_fd,Admin_quantity);
	//puts("查后");
	return p;
}

//接收服务端发送的数据表，并转为Admin结构体数组
Admin * client_read(int client_fd ,int *Admin_quantity){
	char json_str[BUFF_SIZE];			//服务器返回数据的缓冲区
	int count = 0;			//用于判断服务器是否返回数据
	//每次接受信息之间，应该先清空数组中的缓存
	memset(json_str,0,BUFF_SIZE);
	//count用于判断接收服务器的消息
	char buffer[4096];
	int total_received = 0;
	//处理可能导致接收数据不完整
	//puts("读服务端前");
	//多层调用Admin_quantity，在这里改变值，得到结构体数组长度
	read(client_fd,Admin_quantity,sizeof(Admin_quantity));
	//网络字节序转为主机字节序,得到结构体数组长度
	*Admin_quantity = ntohl(*Admin_quantity);
	//读取传来的josn数据（包含查询的用户表）
	count =	read(client_fd,json_str,sizeof(json_str)-1);
	//puts("读服务端后");	
	//接收服务器消息，count大于0说明客户端一直在发送信息
	if(count >0){
		//接收成功则将服务器返回的json字符串解析为Admin结构体数组
		printf("服务器说：%s\n",json_str);
		//得到结构体数组
		Admin *p = json_to_Admin_array( json_str, &count);
		/*
		puts("得到数组");
		//循环遍历数据表结构体数组判断该用户密码是否正确
		for(int i=0; i<Admin_quantity; i++){
			printf("数据库操作后返回结构体数组：\n%d %s %s\n",p[i].id,p[i].name,p[i].password);
		}
		*/
		return p;	
	}else if(count == 0){
		//count等于0说明服务器正常退出
		puts("服务器关闭了。");	
		return NULL;
	}else{
		//count小于0说明读取服务器信息出错
		perror("读取服务器信息错误");
		return NULL;	
	}	
}

/*
int main(int argc, char *argv[]){
	client_write();
	//readFromServer();
	return 0;
	
}
*/






