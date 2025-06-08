#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void func1(){
    printf("函数1被调用\n");
}
void func2(){
    printf("函数2被调用\n");
}
void func3(){
    printf("函数3被调用\n");
}

int main(){
	pid_t pid = fork();   // 创建子进程，返回子进程id

	if(pid == 0){
		atexit(func1);    // 注册退出时调用的函数
        atexit(func2);
        atexit(func3);
        sleep(2);
	}else{
        wait(NULL);
        atexit(func2);
		printf("父进程结束\n");
	}
	return 0;
}
