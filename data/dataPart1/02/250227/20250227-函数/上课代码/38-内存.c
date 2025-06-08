/***************************************************
# File Name:    31-字符串.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:04:09 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>  // 包含这个头文件以使用 rand() 和 srand()

// 全局变量
char name[] = "jack";
int a = 100;

// 静态变量
static int c = 9999;


void two(){
	printf("函数two === 全局变量 a= %d\n", a);
	printf("函数two === 静态变量 c= %d\n", c);
}

void one(){
	// 局部静态变量：
	static int b = 11;
	b += 10;
	// 
	printf("函数one --- 静态局部变量 b= %d\n", b );
	
	// 局部变量
	printf("函数one --- 全局变量 a= %d\n", ++a);
	printf("函数one --- 静态变量 c= %d\n", ++c);
	
}

int main(){
	
	one();
	one();
	one();
	
	/*
	puts("---------------------");
	
	two();
	puts("---------------------");

	
	printf("main函数 **** 全局变量 a= %d\n", a);
	printf("main函数 **** 静态变量 c= %d\n", c);
	*/
	return 0;
}








	
