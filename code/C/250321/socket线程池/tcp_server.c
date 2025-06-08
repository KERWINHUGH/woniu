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
#include "threadpool.h"

typedef struct Server{
	int server_fd;
	struct sockaddr_in client_addr;
	socklen_t client_length;
}Server;

//线程函数，执行socket服务器通信
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
			//11.回复客户端消息
			puts("回复客户端：");
			scanf("%s",str);
			
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


// 提交任务函数：
void submit_task(void *args){
	Server server = *(Server *)args;
	printf("线程：%ld --> 正在运行任务。。。 \n", pthread_self());
	while(1){
		//执行接收客户端连接操作
		int client_fd = accept(server.server_fd, (struct sockaddr *)&server.client_addr,&server.client_length);
		if(client_fd <0){
			perror("接收客户端连接失败");
		 	close(server.server_fd);
		 	exit(EXIT_FAILURE);
		}
		//8.接收客户端成功
		printf("客户端连接成功！id是：%d \n",server.server_fd);
	
	}
	free(args);

	//sleep(3);
}


int main(int argc, char *argv[]){

	//定义一个Server类型的结构体
	Server server = {0};
	
	server.server_fd =0;
	//server.client_addr ={0};
	server.client_length =sizeof(server.client_addr);
	//1.创建套接字
	//第三个参数:为0代表自动选择
	 //int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
	 server.server_fd = socket(AF_INET, SOCK_STREAM, 0); 
	 
	 if(server.server_fd <0){
	 	perror("创建套接字失败");
	 	close(server.server_fd);
	 	exit(EXIT_FAILURE);
	 }
	 
	 //2.创建服务器端口结构体并设置端口协议，地址等信息
	 struct sockaddr_in server_addr = {0};	//创建空地址结构体
	 server_addr.sin_family = AF_INET;	//设置协议为ipv4
	 server_addr.sin_addr.s_addr = INADDR_ANY;	//代表接受任意ipv4的信息
	 server_addr.sin_port = htons(8080);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
	//3.绑定端口号
	if( bind(server.server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("绑定端口号失败");
	 	close(server.server_fd);
	 	exit(EXIT_FAILURE);
	}
	//4.监听端口
	if( listen(server.server_fd, 5)<0){
		perror("监听端口失败");
	 	close(server.server_fd);
	 	exit(EXIT_FAILURE);
	}
	
	//5.到这代表有客户端连接
	puts("服务器正在监听8080");
	
	//定义一个线程池结构体类型
	ThreadPool pool;
	//调用初始化函数初始化线程池
	//设置线程数为2，任务队列容量为5
	thread_pool_init(&pool, 2, 3);

	//6.接收客户端连接，可能是多个客户端，利用线程和循环去处理

		
		//struct sockaddr_in client_addr = {0};	//创建客户端端口结构体
		//socklen_t client_length = sizeof(client_addr);	//定义变量存储客户端结构体大小，用于accept函数作为参数

		//int *args = malloc(sizeof(int));
		for(int i=0; i<2; i++){
		
		//*args = i;
		// 提交任务到线程池
			if(thread_pool_submit( &pool, submit_task , &server )){
				puts("任务已经提交到线程池。。。");
			}else {
				puts("对不起，任务队列已经满了！！！");
				//free(server);
				}
	
		}
	//13.关闭连接
	close(server.server_fd);
	
	// 销毁线程池：
	thread_destroy( &pool );
	
	return 0;
	
}



