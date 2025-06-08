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
	 int server_fd = socket(AF_INET, SOCK_DGRAM, 0); 
	 if(server_fd <0){
	 	perror("创建套接字失败");
	 	close(server_fd);
	 	exit(EXIT_FAILURE);
	 }
	 
	 //2.创建服务器端口结构体并设置端口协议，地址等信息
	 struct sockaddr_in server_addr = {0};	//创建空地址结构体
	 server_addr.sin_family = AF_INET;	//设置协议为ipv4
	 server_addr.sin_addr.s_addr = INADDR_ANY;	//代表接受任意ipv4的信息
	 server_addr.sin_port = htons(PORT);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
	//3.绑定端口号
	if( bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("绑定端口号失败");
	 	close(server_fd);
	 	exit(EXIT_FAILURE);
	}
	
	printf("UDP服务器已启动，等待客户端连接。。。 \n");
	
	//4.服务器进行交互
	//4.1 接收客户端连接，可能是多个客户端
	
	char buf[BUFFER_SIZE];	//增大缓冲区大小

		struct sockaddr_in client_addr = {0};	//创建客户端端口结构体
		socklen_t client_length = sizeof(client_addr);	//定义变量存储客户端结构体大小，用于accept函数作为参数
		
		//执行接收客户端连接操作
		client_length = recvfrom(server_fd, buf ,sizeof(buf)-1, 0,(struct sockaddr *)&client_addr,&client_length);
		
		if(client_length <0){
			perror("接收客户端连接失败");
		 	close(server_fd);
		 	exit(EXIT_FAILURE);
		}
		//接收客户端成功
		printf("客户端连接成功！收到消息是：%s \n",buf);


	//4.2向客户端回复消息
	
	char str[BUFFER_SIZE]="hello,UDP,Client";
		ssize_t count;
		//count用于判断接受客户端的消息
		count = sendto(server_fd,str,strlen(str),0,(struct sockaddr *)&client_addr,client_length);	
		//10.接收客户端消息，count大于0说明客户端一直在发送信息
		if(count <0){
			perror("向客户端发送信息错误");
			close(server_fd);
		 	exit(EXIT_FAILURE);
		}
		printf("向客户端发送消息： %s\n",str);

	//13.关闭连接
	close(server_fd);
	
	return 0;
	
}
