#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
wait(NULL)，等待某个子进程结束，返回子进程的id，适用于单个子进程的情况
waitpid(pid,&status,0)，等待指定的子进程结束，返回子进程的id，适用于多个子进程的情况
*/

int main(){
	pid_t pid1 = fork();   // 创建子进程，返回子进程id
    int status;
	// 检查子进程是否创建成功

	if(pid1 == 0){
		// 子进程中pid为0，此部分代码在子进程中运行
		printf("子进程1创建成功,进程ID为: %d,父进程的ID为: %d\n",getpid(), getppid());
        sleep(3);
        printf("子进程1结束\n");
	}else{
        pid_t pid2 = fork();   // 创建子进程，返回子进程id
        if(pid2 == 0){
            printf("子进程2创建成功,进程ID为: %d,父进程的ID为: %d\n",getpid(), getppid());
            sleep(1);
        }else{
            // wait(NULL);
            waitpid(pid1,&status,0);
            if(WIFEXITED(status)){
                printf("子进程1正常退出，退出码为：%d\n",WEXITSTATUS(status));
            }else if(WIFSIGNALED(status)){
                printf("子进程1被信号%d终止\n",WTERMSIG(status));
            }
            printf("父进程结束\n");
        }
	}
	return 0;
    
}
