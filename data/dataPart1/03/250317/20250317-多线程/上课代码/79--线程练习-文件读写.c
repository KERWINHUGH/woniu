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

void* writeThread(void* args){
	char *fileName = (char*)args;
	printf("当前线程：%ld , 进行写操作。\n", pthread_self() );
	// 1: 打开文件：
	FILE *fp = fopen( fileName, "w" );
	// 2: 使用函数操作文件：
	fputs("hello.world!", fp );
	
	// 3: 关闭
	fclose(fp);

	return NULL;
}

void* readThread(void* args){
	char *fileName = (char*)args;
	printf("当前线程：%ld , 进行 读 操作。\n", pthread_self() );
	// 1: 打开文件：
	FILE *fp = fopen( fileName, "r" );
	// 2: 使用函数操作文件：
	char buffer[128];
	
	fgets( buffer , sizeof(buffer), fp );
	
	printf("读到的数据是：%s \n", buffer);
	// 3: 关闭
	fclose(fp);

	return NULL;
}


int main(int argc, char *argv[]) {
	
	
	pthread_t writePid, readPid ;
	
	char fileName[] = "data.txt";

	// 先写操作
	if(pthread_create( &writePid , NULL, writeThread , fileName ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	// 再读操作
	if(pthread_create( &readPid , NULL, readThread , fileName ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	
	
	// 等待线程结束
	pthread_join(writePid, NULL);
	pthread_join(readPid, NULL);
	
	
	
	
	puts("----end----");

    return 0;
}





