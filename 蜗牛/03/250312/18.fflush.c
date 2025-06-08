#include <stdio.h>
#include <stdlib.h>
/*
文件students.txt内容如下，要求输入学生信息并写入到文件中，能实时显示写入的内容
1   张三    289
2   李四    234
3   王五    123
4   赵六    456
5   孙七    789
6	孙千	387
*/
int main(){
    FILE *fp = fopen("students.txt", "a");
    if(fp == NULL){
        // 打印错误信息，会将系统错误信息跟再提示信息后打印出来
        perror("打开文件失败");   // 打开文件失败: No such file or directory
        return -1;
    }
    int id, score;
    char name[20],flag = '1';
    while(flag == '1'){
        printf("请输入学号:");
        scanf("%d", &id);
        printf("请输入姓名:");
        scanf("%s", name);
        printf("请输入成绩:");
        scanf("%d", &score);
        fprintf(fp, "%d\t%s\t%d\n", id, name, score);  // 写入文件
        fflush(fp);   // 每次写入后，需要刷新缓冲区，否则写入的内容不会立即显示
        printf("继续输入请按1,结束请按其他键: ");
        scanf(" %c", &flag);
    }
    fclose(fp);
    return 0;
}