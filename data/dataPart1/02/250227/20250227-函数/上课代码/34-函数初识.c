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

//          形参：定义函数的时候写的参数。必须写类型
void oneToX(int x){
	
	for(int i = 1; i <= x; i++){
		printf("%d\n", i);
	}
}

void xToY(int x , int y){
	
	for(int i = x; i <= y; i++){
		printf("%d\n", i);
	}
}

void xToY2(int x , int y, int z){
	for(int i = x; i <= y; i += z){
		printf("%d\n", i);
	}
}
 
int main(int argc, char *argv[]) {
	// 实参：调用函数时的，传递的参数。值符合类型即可。
	oneToX(6.666);
	
	puts("----------------");
	
	xToY2(1, 10 , 2);
	puts("----------------");

	xToY2(100, 200, 5);
	
	// 练习：写一个函数，实现从x 打印到 y ,步长可以自定义。

	
    return 0;
}



void oneToTen(){
	for(int i = 1; i <= 10; i++){
		printf("%d\n", i);
	}
}





















