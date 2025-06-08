/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

void one(){
	for( int i = 100; i >= 1; i-- ){
		printf("%d \n", i);
	}
}

void two(){
	// 循环 -> 判断 
	for( int i = 1; i <= 30; i++ ){
		// 在输出之前，应该对数据进行筛选
		if( i % 2 != 0){
			printf("%d \n", i);
		}
	}
	puts("--------------------------");
	
	for( int i = 1; i <= 30; i+=2 ){
		printf("%d \n", i);
	}
}


void three(){
	// 循环 -> 判断(筛选)
	for( int i = 0; i <= 20; i++ ){
		// 在输出之前，应该对数据进行筛选
		if( i % 2 == 0){
			printf("%d \n", i);
		}
	}
	puts("--------------------------");
	
	for( int i = 0; i <= 20; i+=2 ){
		printf("%d \n", i);
	}
}
 
int main(int argc, char *argv[]) {
	// 当我们在写程序中，遇到可能要执行多次的代码，可以使用循环
	/*
	for( int i = 1; i <= 10  ; i++ ){
	
		printf("%d \n", i);
	
	}
	*/
	
	//one();
	//two();
	three();
	
	puts("---end---");

    return 0;
}
