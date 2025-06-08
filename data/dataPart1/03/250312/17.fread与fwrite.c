#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp = fopen("students.txt", "r");
    FILE *fp1 = fopen("new1.txt", "w");
    if(fp == NULL || fp1 == NULL){
        perror("打开文件失败");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);     // 移动到文件末尾
    long filesize = ftell(fp);  // 获取文件大小
    rewind(fp);    // 移动到文件开头
    char buffer[filesize];
    fread(buffer, 1, sizeof(buffer), fp);     // 读取文件内容到缓冲区中
    fwrite(buffer, 1, sizeof(buffer), fp1);   // 将文件内容写入到新文件中
    fclose(fp);
    fclose(fp1);
    return 0;
}