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
 
int main(int argc, char *argv[]) {
	// 1: 创建套接字：
	int client_fd = socket(AF_INET, SOCK_STREAM , 0 );
	if(client_fd < 0 ){
		perror("socket()客户端失败！");
		exit(EXIT_FAILURE);
	}

	// 2: 连接到服务端：
	// 2-1: 先创建地址：
	struct sockaddr_in server_add = {0}; // 直接初始化
	server_add.sin_family = AF_INET;         // ipv4
	server_add.sin_port = htons(8081) ; // 主机序转成网络序
	server_add.sin_addr.s_addr = inet_addr("127.0.0.1") ;  
	// 2-2: 连接
	if(connect(client_fd,  (struct sockaddr *)&server_add , sizeof(server_add) ) != 0){
		perror("连接失败");
        close(client_fd);
        exit(EXIT_FAILURE);
	}
	
	// 3: 交互信息 -------------------------------------
	// 3-1: 向服务端发送信息：
	char str[128] = {0};
	char buf[128] = {0};
	ssize_t count;
	while(true){
		puts("你说：");
		scanf("%s", str);
		
		if(strcmp("exit", str) ==0 ){
			break;
		}
		
		int count = write(client_fd , str , strlen(str) );
		printf("发送了：%d 个字节。", count);
		printf("向服务器发送了信息：%s \n", str);
		
		// 3-2: 接收服务端的信息
		// 每次接收信息之前，应该清空缓存
		memset(buf, 0 , sizeof(buf));
		
		count = read( client_fd , buf , sizeof(buf) - 1 );
		if( count > 0){
			printf("服务器说：%s \n", buf );
		}else if(count == 0){
			printf("服务器关闭了！");
			break;
		}else {
			perror("读取服务器信息错误");
			break;
		}
	}

	// 4: 
	close(client_fd);

    return 0;
}

























