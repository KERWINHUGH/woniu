#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/*
1. time(NULL)，返回当前时间戳，数据类型为time_t
2. localtime(const time_t *timer)， 返回当前时间的结构体指针，类型为struct tm
3. strftime()函数根据struct tm结构体返回指定格式的字符串
4. difftime()，返回两个时间戳的差
*/

int main(){
    printf("当前时间戳：%ld\n", time(NULL));
    srand(time(NULL));   // 设置随机种子
    printf("随机数：%d\n", rand()%10);
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    printf("当前时间：%d年%d月%d日 %d:%d:%d，", p->tm_year+1900, p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    printf("是这一年的第%d天\n", p->tm_yday+1);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", p);
    printf("当前时间：%s\n", buffer);

    sleep(2);

    printf("%lf\n", difftime(time(NULL), t));
    return 0;
}