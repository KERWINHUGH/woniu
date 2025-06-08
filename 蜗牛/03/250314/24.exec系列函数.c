#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*
execlp函数语法: exec("程序名","参数1","参数2",...,NULL)，执行系统程序，自动在PATH中查找程序，参数1为程序名，
参数2为参数1的参数，依次类推。比如执行"ls -l /home"函数为execlp("ls","ls","-l","/home",NULL)

execvp函数语法: execvp("程序名","参数数组",NULL)，执行系统程序，参数数组为参数1，参数2，依次类推。
比如执行"ls -l /home"函数为execvp("ls",{"ls","-l","/home"},NULL)
*/

/*
文件students.txt内容如下，要求在子进程中查询并输出学生赵六的考试成绩，在主进程中输出除赵六以外的所有学生的考试成绩。
1   张三    289
2   李四    234
3   王五    123
4   赵六    456
5   孙七    789
*/
int main(){
    pid_t pid = fork();   // 创建子进程，返回子进程id
    if(pid == 0){
        printf("- - - - - - - 子进程 - - - - - -\n");
        execlp("grep","grep","赵六","./students.txt",NULL);  
    }else{
        sleep(3);
        printf("- - - - - - - 父进程 - - - - - -\n");
        char *argv[] = {"grep","-v","赵六","./students.txt",NULL};
        execvp("grep",argv);
    }
    return 0;
}