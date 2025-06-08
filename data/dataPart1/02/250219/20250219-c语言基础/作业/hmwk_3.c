/***************************************************
# File Name:    hmwk_3.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 08:34:11 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	puts("++运算符写在变量前，程序运行计算时先累加一次然后再使用变量,");
	puts("++运算符写在变量后，程序运行计算时先使用变量再累加。");

	puts("------------------------示例-------------------------");

	int a=1,b=2;

	printf("初始数值为a=%d,b=%d \n",a,b);

	printf("使用++a和b++后\n a=%d ,b=%d\n",++a,b++);

	printf("初始数值为a=%d,b=%d \n",a,b);

	printf("使用--a和b--后\n a=%d ,b=%d\n",--a,b--);
    
	return 0;
}
