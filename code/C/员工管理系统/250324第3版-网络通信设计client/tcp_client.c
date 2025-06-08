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

#include "cJSON.h"
#include "json.h"
//#include "EMS.h"			//引入系统所需要的结构体
#include "sysOpera.h"

#define SERVER_ADDR "127.0.0.1"		//定义服务器地址
#define SERVER_PORT 8080			//定义服务器端口号
#define BUFF_SIZE 1024				//定义缓冲区大小



void writeToServer(){
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
	 
	//4.连接
	if( connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("连接失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	}

	puts("连接成功");
	//9.客户端进行交互
	char str[BUFF_SIZE];	//客户端发送消息的缓冲区
	ssize_t count;			//用于判断服务器是否返回数据
	
	//puts("请输入想要的操作：");
	//puts("0.增加管理员 1.删除管理员 2.修改管理员 3.查询管理员 4.增加用户 5.删除用户 6.修改用户 7.查询用户");
	//scanf("%d",&op);
	OP op = add_admin;		//测试，假设是增加用户操作
	
		switch(op){
			case add_admin:
						Admin admin = {0};
						printf("请输入用户名：\n");
						char *ret_name = name_verifi( admin.name );		
						if(ret_name == NULL){
							printf("用户名输入不合法 \n");
							return ;
						}else{
							printf("请输入密码：\n");
							char *ret_pass = password_verifi( admin.password );
							if(ret_pass == NULL){
								printf("密码输入不合法 \n");
								return ;
							}
						}
						//向服务器发送操作信息
				 		//write(client_fd, op_str[0], strlen(op_str[0]));
				 		write(client_fd, &add_admin, sizeof(int));
				 		usleep(500000);
				 		//通过json传送用户数据
						char* json_str = Admin_to_json( &admin );
						//向服务器发送用户信息
				 		write(client_fd, json_str, strlen(json_str));
						break;
			case delete_admin:
						//通过json传送用户数据
						
						//向服务器发送操作信息
				 		write(client_fd, op_str[1], strlen(op_str[1]));
						break;
			case modify_admin:
						//通过json传送用户数据
						
						//向服务器发送操作信息
				 		write(client_fd, op_str[2], strlen(op_str[2]));
						break;
			case inqur_admin:
						//通过json传送用户数据
						
						//向服务器发送操作信息
				 		write(client_fd, op_str[3], strlen(op_str[3]));
						break;
			case add_user:
						//通过json传送用户数据
						
						//向服务器发送操作信息
				 		write(client_fd, op_str[4], strlen(op_str[4]));
						break;
			case delete_user:
						//通过json传送用户数据
						
						//向服务器发送操作信息
				 		write(client_fd, op_str[5], strlen(op_str[5]));
						break;
			case modify_user:
						//通过json传送用户数据
						
						//向服务器发送操作信息
				 		write(client_fd, op_str[6], strlen(op_str[6]));
						break;
			case inqur_user:
						//通过json传送用户数据
						
						//向服务器发送操作信息
				 		write(client_fd, op_str[7], strlen(op_str[7]));
						break;	
			default:
					puts("输入操作不在区间内");
						return ;	
		}
	close(client_fd);	
}	
void readFromServer(){
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
	 
	//4.连接
	if( connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("连接失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	}

	puts("连接成功");
	//9.客户端进行交互
	char str[BUFF_SIZE];	//客户端发送消息的缓冲区
	char buf[BUFF_SIZE];	//服务器返回数据的缓冲区
	ssize_t count;			//用于判断服务器是否返回数据
	
		//每次接受信息之间，应该先清空数组中的缓存
		memset(buf,0,BUFF_SIZE);
		//count用于判断接收服务器的消息
		count = read(client_fd,buf,BUFF_SIZE-1);	
		//10.接收服务器消息，count大于0说明客户端一直在发送信息
		if(count >0){
			printf("服务器说：%s\n",buf);
			//count等于0说明服务器正常退出
		}else if(count == 0){
			puts("服务器关闭了。");
			
			//否则count小于0说明读取服务器信息出错
		}else{
			perror("读取服务器信息错误");
			
		}
	//关闭客户端
	close(client_fd);
}


	
int main(int argc, char *argv[]){
	writeToServer();
	//readFromServer();
	return 0;
	
}







