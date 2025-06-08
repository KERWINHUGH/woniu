#include <stdio.h>

/*
文件students.txt内容如下，要求读取每个学生的信息，并且按：姓名: xxx,总分: xxx格式输出
1   张三    289
2   李四    234
3   王五    123
4   赵六    456
5   孙七    789
*/
int main(){
    FILE *fp = fopen("./students.txt", "r");  // 以只读方式打开当前目录下的students.txt文件
    if(fp == NULL){
        // 打印错误信息，会将系统错误信息跟再提示信息后打印出来
        perror("打开文件失败");   // 打开文件失败: No such file or directory
        return -1;
    }
    // 格式化读取文件内容
    char name[20];
    int id,score;
    // fscanf，将文件中的一行内容按指定的格式读取到变量中，返回读取到的字符数
    while(fscanf(fp, "%d %s %d", &id, name, &score) != EOF){
        printf("姓名: %s, 总分: %d\n", name, score);
    }
    fclose(fp);
    return 0;
}