#include <stdio.h>
#include <stdlib.h>
/*
文件students.txt内容如下，要求读取每个学生的信息，并输出
1   张三    289
2   李四    234
3   王五    123
4   赵六    456
5   孙七    789
6	孙千	387
*/

// feof函数，检测文件流是否已经到达文件末尾，如果到达文件末尾，则返回非0值，否则返回0值
// ferror函数，检测文件流操作是否发生错误，如果发生错误，则返回非0值，否则返回0值
int main(){
    FILE *fp = fopen("./students.txt", "r");  // 以只读方式打开当前目录下的students.txt文件
    if(fp == NULL){
        // 打印错误信息，会将系统错误信息跟再提示信息后打印出来
        perror("打开文件失败");   // 打开文件失败: No such file or directory
        return -1;
    }
    char buffer[1024];
    // fgets(buffer, sizeof(buffer), fp);  // 从fp文件中读取一行内容到buffer中，每调用1次光标会往下移动一行
    // printf("%s\n", buffer);
    // fgets(buffer, sizeof(buffer), fp);  
    // printf("%s\n", buffer);
    // 循环读取文件内容
    while(fgets(buffer, sizeof(buffer), fp) != NULL){
        printf("%s", buffer);
    }

    if(feof(fp) != 0){
        printf("文件读取完毕\n");
    }else if(ferror(fp) != 0){
        printf("文件读取出错\n");
    }
    
    fclose(fp);
    return 0;
}