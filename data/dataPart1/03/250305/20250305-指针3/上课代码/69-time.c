/***************************************************
# File Name:    69-time.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 05 Mar 2025 05:40:35 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char* getTime(  ){
	char *t = (char *)malloc(128);
	
    time_t rawtime;
    struct tm *now;

    // 获取当前时间
    time(&rawtime);
    now = localtime(&rawtime);

    // 格式化日期和时间，但不包括星期
    strftime(t, 128, "%Y年%m月%d日 %H:%M:%S ", now);

	printf("getTime: %s \n", t);
	
	return t;
}
 
int main(int argc, char *argv[]) {

	char *tt = getTime();
	
	// 输出最终结果
    printf("main: %s \n", tt);

	free(tt);
	tt = NULL;

    return 0;
}







