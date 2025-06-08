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
#include "sysOpera.h"		//引入用户输入验证
#include "tcp_client.h"
//#include "tcp_server.h"
//#include "common.h"



void client_write(){
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
	
	//puts("请输入想要的操作：");
	//puts("0.增加管理员 1.删除管理员 2.修改管理员 3.查询管理员 4.增加用户 5.删除用户 6.修改用户 7.查询用户");
	//scanf("%d",&op);
	OP op = ADD_ADMIN;		//测试，假设是增加用户操作
	
		switch(op){
			case ADD_ADMIN:
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
						//将枚举转为字符串，然后进行发送（字符串不用考虑字节序问题）
						char *op_str = op_to_string( op );
						if(write(client_fd, op_str, strlen(op_str)) < 0){
							perror("向服务端发送操作失败！\n");
						}
						
				 		usleep(500000);//模拟间隔发送
				 			
				 		//通过json先转换用户信息
						char* json_str = Admin_to_json( &admin );
						//向服务器发送用户信息
				 		if(write(client_fd, json_str, strlen(json_str)) < 0){
				 			perror("向服务端发送用户信息失败！\n");
				 		}	
				 		
				 		//usleep(500000);//等待消息
				 		//读取服务端数据，并将得到的数据转换为Admin结构体数组
				 		Admin *p = client_read(client_fd);
				 		int count = sizeof(p)/sizeof(p[0]);			//用于判断服务器是否返回数据
				 		for (int i = 0; i < count; i++) {
            				printf("返回数据成功：Admin id：%d\tname %s\tpassword：%s\n", p[i].id, p[i].name, p[i].password);
        				}
				 		
						break;
			
			default:
					puts("输入操作不在区间内");
						return ;	
		}
	close(client_fd);	
}	
Admin * client_read(int client_fd){
		char json_str[BUFF_SIZE];			//服务器返回数据的缓冲区
		int count = 0;			//用于判断服务器是否返回数据
	
		//每次接受信息之间，应该先清空数组中的缓存
		memset(json_str,0,BUFF_SIZE);
		//count用于判断接收服务器的消息
		char buffer[4096];
		int total_received = 0;
		
		//处理可能导致接收数据不完整
		count =	read(client_fd,json_str,sizeof(json_str)-1);	
		//接收服务器消息，count大于0说明客户端一直在发送信息
		if(count >0){
			//接收成功则将服务器返回的json字符串解析为Admin结构体数组
			printf("服务器说：%s\n",json_str);
			//得到结构体数组
			Admin *p = json_to_Admin_array( json_str, &count);
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


int main(int argc, char *argv[]){
	client_write();
	//readFromServer();
	return 0;
	
}







