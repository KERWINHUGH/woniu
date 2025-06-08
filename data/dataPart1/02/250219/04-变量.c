/***************************************************
# File Name:    04-变量.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 11:50:56 AM CST
****************************************************/

#include <stdio.h>
 
void one(){
	int num = 10;
	printf("one num: %d \n", num);
}

void two(){
	int num = 100;
	printf("two num: %d \n", num);
}

int main(int argc, char *argv[]) {

	int num; // 这样写，只定义了变量，没有初始化
	// 变量应该初始化之后，再使用；
	num = 0;

	printf("main num: %d \n", num);
    	
	return 0;
}
