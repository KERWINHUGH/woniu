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

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	//1.创建套接字
	//第三个参数:为0代表自动选择
	 int client_fd = socket(AF_INET, SOCK_DGRAM, 0); 
	 if(client_fd <0){
	 	perror("创建套接字失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	 }
	 
	 //2.创建服务器端口结构体并设置端口协议，地址等信息
	 struct sockaddr_in server_addr = {0};	//创建空地址结构体
	 server_addr.sin_family = AF_INET;	//设置协议为ipv4
	 server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);	//代表接受任意ipv4的信息
	 server_addr.sin_port = htons(PORT);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
	socklen_t server_length =sizeof(server_addr);
	//3.服务器进行交互
	//3.1向服务器发送消息
	
	char str[128]="hello,server";
		ssize_t count;
		//count用于判断接受客户端的消息
		count = sendto(client_fd,str,strlen(str),0,(struct sockaddr *)&server_addr,server_length);	
		//10.接收服务端消息，count大于0说明客户端一直在发送信息
		if(count <0){
			perror("向客户端发送信息错误");
			close(client_fd);
		 	exit(EXIT_FAILURE);
		}
		
		
	printf("向服务器发送消息： %s\n",str);
		 	
		 	
	//3.2 接收客户端连接，可能是多个客户端
	char buf[BUFFER_SIZE];	//增大缓冲区大小
		
	//执行接收客户端连接操作
	socklen_t client_length = recvfrom(client_fd, buf ,sizeof(buf)-1, 0,(struct sockaddr *)&server_addr,&server_length);
		
		if(client_length <0){
			perror("接收服务端消息失败");
		 	close(client_fd);
		 	exit(EXIT_FAILURE);
		}
		//接收客户端成功
		printf("服务器连接成功！收到消息是：%s \n",buf);


	
	//13.关闭连接
	close(client_fd);
	
	return 0;
	
}
