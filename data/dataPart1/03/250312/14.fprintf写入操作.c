#include <stdio.h>

/*
文件students.txt内容如下，要求从键盘输入学号、姓名、成绩，然后将输入的信息写入到文件中
1   张三    289
2   李四    234
3   王五    123
4   赵六    456
5   孙七    789
*/
int main(){
    FILE *fp = fopen("students.txt", "a");
    if(fp == NULL){
        // 打印错误信息，会将系统错误信息跟再提示信息后打印出来
        perror("打开文件失败");   // 打开文件失败: No such file or directory
        return -1;
    }
    int id, score;
    char name[20];
    printf("请输入学号:");
    scanf("%d", &id);
    printf("请输入姓名:");
    scanf("%s", name);
    printf("请输入成绩:");
    scanf("%d", &score);
    if(fprintf(fp, "%d\t%s\t%d\n", id, name, score) < 0){
        perror("写入文件失败");
        return -1;
    }
    fclose(fp);
    return 0;
}