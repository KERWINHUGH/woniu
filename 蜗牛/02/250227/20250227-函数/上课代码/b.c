/***************************************************
# File Name:    b.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 27 Feb 2025 05:37:51 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

// 引入外部文件(这里是a.c文件)的变量：
extern int a;  // 这个变量来自于外部

//extern static int b;  // 静态的全局变量，不能被外部的文件引用

// 引入外部文件(这里是a.c文件)的函数
extern void seeVar();

 
int main(int argc, char *argv[]) {

	a += 10;
	
	printf("改变a.c文件里的a的值：%d \n", a);
	
	seeVar();


    return 0;
}
