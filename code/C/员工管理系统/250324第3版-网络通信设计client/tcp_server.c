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

void *handle_client(void *args){
	int client_fd = *(int *)args;
	//9.服务器进行交互
	char buf[128];	//增大缓冲区大小
	char str[128];
	ssize_t count;
	
	while(1){
		//每次接受信息之间，应该先清空数组中的缓存
		memset(buf,0,sizeof(buf));
		//count用于判断接受客户端的消息
		count = read(client_fd,buf,sizeof(buf)-1);	
		//10.接收客户端消息，count大于0说明客户端一直在发送信息
		if(count >0){
			printf("客户端说：%s\n",buf);
			
			//设计如果输入exit则退出服务器，否则一直等待客户端连接
			if(strcmp("exit",str) == 0){
				break;
			}
			
			if(write(client_fd,str,strlen(str)) < 0){
				perror("回复客户端失败");
			}
			//count等于0说明客户端正常退出
		}else if(count == 0){
			puts("客户端关闭了。");
			break;
			//否则count小于0说明读取客户端信息出错
		}else{
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
	 server_addr.sin_port = htons(8080);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
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
				if(pthread_create(&pid ,NULL ,handle_client ,client_fd) !=0){
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
