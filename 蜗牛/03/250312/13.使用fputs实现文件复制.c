#include <stdio.h>

/*
文件students.txt内容如下，要求将这个文件的内容复制到new.txt中
1   张三    289
2   李四    234
3   王五    123
4   赵六    456
5   孙七    789
6	孙千	387
*/
int main(){
    FILE *fp1 = fopen("students.txt", "r");
    FILE *fp2 = fopen("new.txt", "w");
    if(fp1 == NULL || fp2 == NULL){
        // 打印错误信息，会将系统错误信息跟再提示信息后打印出来
        perror("打开文件失败");   // 打开文件失败: No such file or directory
        return -1;
    }
    char buffer[1024];
    // 循环从students.txt读取每一个学生的信息，然后将这一行的内容追加写入到new.txt中
    while(fgets(buffer, sizeof(buffer), fp1) != NULL){
        fputs(buffer, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}