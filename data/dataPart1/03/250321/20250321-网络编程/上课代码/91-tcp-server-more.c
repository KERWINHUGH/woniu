/***************************************************
# File Name:    89-tcp-server.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Mar 2025 03:35:50 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h> 	// read(),write()和close()等api
#include <arpa/inet.h>
#include <sys/socket.h>
//用于互联网地址族，包括 sockaddr_in 结构和 IP 地址定义。
#include <netinet/in.h>
#include <pthread.h>    // 引入多线程

void* handle_client(void* args){
	int client_fd = *(int *)args;

	// 5: 交互信息 ------------------------------------------
	// 5-1: 读取客户端发送过来的信息：
	ssize_t count;
	char buf[128] = {0};
	char str[128] = {0};
	
	while(true){
		// 每次接收信息之前，应该清空缓存
		memset(buf, 0 , sizeof(buf));
		count = read(client_fd , buf , sizeof(buf) - 1 );
		if( count > 0){
			printf("客户端说：%s \n", buf );
			// 5-2: 回复客户端：
			puts("回复客户端：");
			scanf("%s", str);
			
			if(strcmp("exit", str) == 0){
				break;
			}
			
			if(write(client_fd , str , strlen(str) ) < 0){
				puts("write() error");
			} 
		}else if(count == 0){
			puts("客户端关闭了。");
			break;
		}else {
			perror("读取客户端信息错误");
			break;
		}
	}
	// 关闭客户端：
	close(client_fd);
	free(args);
	return NULL;
}



 
int main(int argc, char *argv[]) {
	// 1: 创建套接字：
	int server_fd = socket(AF_INET, SOCK_STREAM , 0 );
	if(server_fd < 0){
		perror("socket()服务器失败！");
		exit(EXIT_FAILURE);
	}
	
	// 2: 设置端口和ip地址，并绑定
	struct sockaddr_in server_add = {0}; // 直接初始化
	
	server_add.sin_family = AF_INET;         // ipv4
	server_add.sin_addr.s_addr = INADDR_ANY;  // 代表接收所有的ipv4地址的信息
	server_add.sin_port = htons(8081) ; // 主机序转成网络序
	
	if( bind(server_fd, (struct sockaddr *)&server_add , sizeof(server_add)) != 0 ){
		perror("bind()失败！");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	
	// 3: 监听：
	if(listen( server_fd , 5 ) !=0 ){
		perror("listen()失败！");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	puts("服务器正在监听8081端口：");
	
	
	// 4: 接收客户端的连接(可能是多个)：
	while(true){
		struct sockaddr_in client_add = {0}; // 准备一个空的地址结构体
		
		int client_length = sizeof(client_add);
		
		int *client_fd = malloc(sizeof(int));
		
		*client_fd = accept( server_fd , (struct sockaddr *)&client_add , &client_length ); 
		
		if(*client_fd < 0){
			perror("accept()失败！");
			close(server_fd);
			exit(EXIT_FAILURE);
		}
		printf("有客户端成功连接！id是：%d \n", *client_fd);
		
		//  创建线程来和连接上来的客户端对话。
		// 交互信息, 能过多线程来完成------------------------------------------
		pthread_t pid ;
		if(pthread_create(&pid, NULL, handle_client, client_fd ) != 0){
			perror("pthread_create() error!");
			free(client_fd);
		}
		// 分离线程
		pthread_detach(pid);
	
	}
	
	// 6: 关闭连接
	close(server_fd);

    return 0;
}























