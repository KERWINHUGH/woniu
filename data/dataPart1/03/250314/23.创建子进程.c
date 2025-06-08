#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid = fork();   // 创建子进程，返回子进程id
	// 检查子进程是否创建成功
	if(pid == -1){
		perror("子进程创建失败");
		return -1;
	}
	if(pid == 0){
		// 子进程中pid为0，此部分代码在子进程中运行
		printf("子进程创建成功，进程ID为: %d，父进程的ID为: %d\n",getpid(), getppid());
		sleep(3);
	}else{
		// 父进程中pid为子进程的ID号，此部分代码在父进程中运行
		printf("子进程创建成功，子进程的ID为: %d\n",pid);
		system("ps -ef");
		sleep(3);

	}
	return 0;
}
