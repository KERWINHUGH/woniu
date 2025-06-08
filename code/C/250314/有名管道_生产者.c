/***************************************************
# File Name:    exec命令.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Fri 14 Mar 2025 11:20:05 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	//write()
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>	//mkfifo()  打开管道
#include <fcntl.h>	//open()

#define PIPE_NAME "/tmp/myfifp"	//命名管道文件名
#define BUFFER_SIZE 1024
 
int main(int argc, char *argv[]) {
	
	char buffer[BUFFER_SIZE];	//创建缓冲区
	if(pipe(fd) == -1){	//创建管道，成功返回0，失败返回-1。
		perror("创建管道失败");
		exit(1);
	}
	pid_t pid = fork();	//创建子进程
	if(pid == -1){
		perror("进程创建失败");
		exit(1);
	}else if(pid == 0){
		close(fd[0]);	//关闭管道读端
		printf("子进程写入数据\n");
		write(fd[1],"测试消息",12);	//子进程写入数据
	}else{
		wait(NULL);
		close(fd[1]);	//关闭管道写端
		printf("父进程读取数据\n");
		read(fd[0],buffer,1024);	//父进程读取数据
		printf("读取的数据是：%s\n",buffer);
	}
	
    return 0;
}


