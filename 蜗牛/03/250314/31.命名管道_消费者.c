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
    // 打开命名管道的读端
    int fd = open(PIPE_NAME, O_RDONLY);  // 运行后生产者程序的阻塞状态会解除
    if(fd == -1){
        perror("open");
        exit(1);
    }
    // 从管道中读取数据
    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
    if(bytesRead == -1){
        perror("read");
        exit(1);
    }
    buffer[bytesRead] = '\0';
    printf("读取的数据: %s\n", buffer);
    close(fd);
    return 0;
}