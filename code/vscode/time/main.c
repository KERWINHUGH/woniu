#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t time_cnt;//存储时间戳long
struct tm *time_info;//存储时间戳转换后的结构体
char *time_str;//存储转换后的字符串

int main()
{
    time_t now = time(NULL);
    struct tm*nowtime = localtime(&now);
    char *time_str ;
    strftime(time_str,100,"%Y%m%d %H:%M:%S\n",nowtime);
    printf("%s\n",time_str);

    //1.获取当前时间戳
    time_cnt = time(NULL);
    printf("%s\n",time_cnt);

    //2.将时间戳转换为tm结构体，格林威治时间和北京时间相差8小时
    time_info = localtime(&time_cnt);
    printf("%s\n",time_info->tm_year);
    printf("%s\n",time_info->tm_mon);
    printf("%s\n",time_info->tm_yday);

    //3.将tm 结构体转换为long值
    time_cnt = mktime(time_info);
    printf("%s\n",time_cnt);

    //4.格式化标准时间
    strftime(time_str,200,"%Y/%m/%d %H:%M:%S\n",time_info);
    printf("%s\n",time_str);
   
    system("pause");    // 防止运行后自动退出，需头文件stdlib.h
    return 0;

}