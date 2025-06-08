#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int fd[2];   // 创建管道
    char buffer[1024];  // 创建缓冲区
    if(pipe(fd) == -1){  // 创建管道
        perror("创建管道失败");
        exit(1);
    }   
    pid_t pid = fork();   // 创建子进程
    if(pid == -1){
        perror("创建子进程失败");
        exit(1);
    }else if(pid == 0){
        close(fd[0]);    // 关闭管道读端
        printf("子进程写入数据\n");
        write(fd[1], "测试消息！！！！！！！！！", 30);   // 子进程写入数据
    }else{
        wait(NULL);
        close(fd[1]);    // 关闭管道写端
        printf("父进程读取数据\n");
        read(fd[0], buffer, 1024);
        printf("读取的数据是：%s\n", buffer);
    }
    return 0;
}