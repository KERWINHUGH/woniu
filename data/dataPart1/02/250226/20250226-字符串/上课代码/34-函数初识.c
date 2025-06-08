/***************************************************
# File Name:    31-字符串.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:04:09 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 函数的申明
void oneToTen();

int sum();

 
int main(int argc, char *argv[]) {

	oneToTen();
	
	puts("----------------");
	
	// 接收函数调用之后的，返回值。
	int result = sum();
	
	printf("函数调用的结果：%d \n", result );
	
    return 0;
}

// 申明函数有一个返回值
int sum(){
	int a = 100;
	int b = 50;
	int c = a + b;
	
	return c;
}


void oneToTen(){
	for(int i = 1; i <= 10; i++){
		printf("%d\n", i);
	}
}





















