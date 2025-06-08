/***************************************************
# File Name:    74-线程初识.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 17 Mar 2025 10:56:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>   // sleep

// 线程函数：可以接收参数，可以有返回值。
void* one( void* args ){
	puts("----one线程执行运算-----");	
	char *result = malloc(sizeof(char) * 32);
	if(result == NULL){
		perror("内存分配失败！");
		pthread_exit(NULL);
	}
	// 参数是无类型的指针，要先转成目标类型：
	strcpy(result , (char*)args);
	strcat(result, "======");
	
	return result;
}
int main(int argc, char *argv[]) {
	pthread_t pid;
	char param[] = "hello,c";
	if(pthread_create( &pid , NULL, one , param ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	for(int i = 1; i<= 10; i++){
		printf("main函数里：%d ====================\n ", i);
	}
	char *result = NULL;
	// 等待线程执行完成：通过pthread_join得到 one（线程）函数的执行结果。
	if(pthread_join( pid , (void**)&result) != 0){
		perror("join线程失败！");
		return 1;
	}
	printf("线程函数执行的结果是：%s \n", result );
	// 释放内存
	free(result);
	puts("----end----");
    return 0;
}





