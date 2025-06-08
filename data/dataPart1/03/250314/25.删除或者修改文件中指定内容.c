#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*
文件users.txt内容如下，要求在子进程中修改user101的密码为123qwe，在主进程中删除user102的数据。
admin     admin123	管理员	13512345678	0-0-000	0	0	0	0
user101   admin123	张三	13512345678	0-0-000	1	0	0	0
user102   admin123	李四	13512345678	0-0-000	1	0	0	0
user103   admin123	王五	13512345678	0-0-000	1	0	0	0
user104   admin123	赵六	13512345678	0-0-000	1	0	0	0
*/
int main(){
    
}