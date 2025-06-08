/***************************************************
# File Name:    a.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 27 Feb 2025 05:37:44 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
// 全局变量，可以被外部文件引用。
int a = 100;

//静态的全局变量，不能被外部的文件引用
static int b = 999;


void seeVar(){
	printf("a 里面的全局变量：a=%d \n", a);
	printf("a 里面的静态全局变量：b=%d \n", b);
}
