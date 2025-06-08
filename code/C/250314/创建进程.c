/***************************************************
# File Name:    创建进程.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Fri 14 Mar 2025 10:14:46 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
 
int main(int argc, char *argv[]) {
	
	pid_t pid = fork();	//创建子进程，返回子进程pid
	if(pid == -1){//父进程中返回-1
		perror("子进程创建失败\n");
		return -1;
	}
	if(pid ==0 ){//子进程中返回0
		printf("子进程创建成功，进程id为：%d,父进程id为：%d \n",getpid(),getppid());
		//sleep();
	}else{
		printf("子进程创建成功，子进程id为：%d\n",pid);
	}
	
    return 0;
}


