/***************************************************
# File Name:    hmwk5.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Feb 2025 07:48:07 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

    puts("请输入一个年份");

	int year;

	scanf("%d",&year);

	if(((year % 4 == 0) && (year % 100 !=0)) || (year % 400 == 0))
	{
		printf("%d是闰年 \n",year);
	}else
	{	
		printf("%d不是闰年 \n",year);
	}

    return 0;
}
