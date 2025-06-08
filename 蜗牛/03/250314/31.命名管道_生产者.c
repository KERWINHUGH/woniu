#include <stdio.h>
#include <unistd.h>   // write()
#include <stdlib.h>
#include <sys/stat.h> // mkfifo()
#include <fcntl.h>    // open()
#include <string.h>

#define PIPE_NAME "/tmp/myfifo"  // 命名管道文件名
#define BUFFER_SIZE 1024

int main(){
    char buffer[BUFFER_SIZE];   // 缓冲区
    int fd;
    // 检查命名管道文件是否存在，如果不存在则创建，并设置权限
    if(access(PIPE_NAME, F_OK) == -1){
        if(mkfifo(PIPE_NAME, 0666) == -1){
            perror("mkfifo");
            exit(1);
        }
    }

    // 打开管道的写端
    fd = open(PIPE_NAME, O_WRONLY);  // 当前进程会被阻塞，直到另一个进程打开同一个管道用于读取数据
    if(fd == -1){
        perror("open");
        exit(1);
    }

    // 向管道写入数据
    char *data = "这是来自生产者的测试数据！！！！！！";
    if(write(fd, data, strlen(data)) == -1){
        perror("write");
        close(fd);  // 关闭文件描述符
        exit(1);
    }
    close(fd);
    return 0;
}