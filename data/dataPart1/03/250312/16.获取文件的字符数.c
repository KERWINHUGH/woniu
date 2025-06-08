#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp = fopen("new.txt", "r");
    if(fp == NULL){
        perror("打开文件失败");
        exit(1);
    }
    printf("%c",fgetc(fp));
    fseek(fp, -1, SEEK_END);   // 移动到文件末尾前1个字符
    printf("%c",fgetc(fp));
    
    fseek(fp, 0, SEEK_END);    // 移动到文件末尾
    long filesize = ftell(fp);
    printf("文件长度为：%ld\n", filesize);
    fclose(fp);
    return 0;
}