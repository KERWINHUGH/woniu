#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
文件users.txt内容如下，要求在子进程中输入1个用户名，返回命令执行结果，在主进程中根据该结果中判断用户是否存在。
admin     admin123	管理员	13512345678	0-0-000	0	0	0	0
user101   admin123	张三	13512345678	0-0-000	1	0	0	0
user102   admin123	李四	13512345678	0-0-000	1	0	0	0
user103   admin123	王五	13512345678	0-0-000	1	0	0	0
user104   admin123	赵六	13512345678	0-0-000	1	0	0	0
*/

int main(){
    int fd[2];   // 创建管道描述符数组
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
        // 子进程执行命令，并且将命令执行结果写入管道
        dup2(fd[1], STDOUT_FILENO);  // 将标准输出重定向到管道的写端
        close(fd[1]);   // 关闭原管道写端，可以不写
        execlp("grep", "grep", "-c", "^user101", "./users.txt", NULL);  // 执行命令，并将命令执行结果写入管道
    }else{
        wait(NULL);
        close(fd[1]);    // 关闭管道写端
        read(fd[0], buffer, 1);   // 读取管道数据
        buffer[1] = '\0';
        printf("读取的数据是：%s\n", buffer);
        if(atoi(buffer) == 0){    // atoi，将一个字符串转换为整数
            printf("用户不存在\n");
        }else{
            printf("用户存在\n");
        }
    }
    return 0;
}