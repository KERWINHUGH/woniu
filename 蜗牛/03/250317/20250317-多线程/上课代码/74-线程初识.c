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

void* one(){
	for(int i = 1; i<= 100; i++){
		
		if(i == 10){
			pthread_exit(NULL);
		}
		printf("one函数里：%d ------\n ", i);
		//sleep(1);
		usleep( 100000 );
	}
	return NULL;
}

void* two(){
	for(int i = 1; i<= 100; i++){
		
		if(i == 20){
			pthread_exit(NULL);
		}
		printf("two函数里：%d ------\n ", i);
		//sleep(1);
		usleep( 100000 );
	}
	return NULL;
}
 
int main(int argc, char *argv[]) {
	
	pthread_t pid;
	pthread_t pid2;

	if(pthread_create( &pid , NULL, one , NULL) != 0 ){
		perror("线程创建失败!");
		return 1;
	}	
	
	if(pthread_create( &pid2 , NULL, two , NULL) != 0 ){
		perror("线程创建失败!");
		return 1;
	}

	for(int i = 1; i<= 100; i++){
		printf("main函数里：%d ====================\n ", i);
		//sleep(1);
		usleep( 100000 );

	}
	// 等待线程执行完成：
	pthread_join( pid , NULL );
	pthread_join( pid2 , NULL );
	
	puts("----end----");

    return 0;
}





