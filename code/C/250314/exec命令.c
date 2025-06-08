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
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main(int argc, char *argv[]) {
	pid_t pid1 = fork();
	int status;
	if(pid1 == 0){
		printf("子进程1创建成功\n");
		sleep(3);
		printf("子进程1结束\n");
	}else{
		pid_t pid2 = fork();
		if(pid2 == 0){
			printf("子进程2创建成功\n");
			sleep(1);
		}else{
			wait(NULL);
			waitpid(pid1,&status,0);
			if(WIFEXITED(status)){
				printf("子进程1正常退出,退出码为:%d\n",WEXITSTATUS(status));
				
			}else if(WIFSIGNALED(status)){
			printf("子进程1被信号%d终止\n",WTERMSIG(status));
			}
			printf("父进程结束");
		}
	}
    return 0;
}


