/***************************************************
# File Name:    hmwk2.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Feb 2025 06:02:49 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	puts("请输入一个整数！");
	
	int num;

	scanf("%d",&num);

	num >= 0 ? (printf("%d是一个正数\n",num)) :(printf("%d是一个负数\n",num));

    return 0;
}
