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


int main(int argc, char *argv[]){
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
	 server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//127.0.0.1代表客户端本机
	 server_addr.sin_port = htons(8080);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
	//4.连接
	if( connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("连接失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	}

	puts("连接成功");
	//9.客户端进行交互
	char buf[128];	//增大缓冲区大小
	char str[128];
	ssize_t count;
	ssize_t len;
	
	while(1){
		
		puts("你说：");
		scanf("%s",str);
		//设计如果输入exit则退出客户端，负责一直处于和服务器通信状态
		if(strcmp("exit",str) == 0){
			break;
		}
		//向服务器发送信息
		len = write(client_fd, str, strlen(str));
		printf("发送了：%ld个字节。",len);
		printf("向服务器发送了信息：%s \n",str);
		
		//每次接受信息之间，应该先清空数组中的缓存
		memset(buf,0,sizeof(buf));
		
		//count用于判断接受客户端的消息
		count = read(client_fd,buf,sizeof(buf)-1);	
		//10.接收客户端消息，count大于0说明客户端一直在发送信息
		if(count >0){
			printf("服务器说：%s\n",buf);
			//count等于0说明服务器正常退出
		}else if(count == 0){
			puts("服务器关闭了。");
			break;
			//否则count小于0说明读取服务器信息出错
		}else{
			perror("读取服务器信息错误");
			break;
		}
	}
	//关闭客户端
	close(client_fd);
	

	return 0;
	
}
