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
#include <semaphore.h>

sem_t sem1;
sem_t sem2;

void* one(){

	for(int i = 0; i < 10; i ++){
		sem_wait(&sem1);
		printf("%s", "你");
		sem_post(&sem2);
	}

	return NULL;
}


void* two(){

	for(int i = 0; i < 10; i ++){
		sem_wait(&sem2);
		printf("%s", "好!\n");
		sem_post(&sem1);
	}

	return NULL;
}



int main(int argc, char *argv[]) {

	sem_init( &sem1 , 0, 1 );  // one应该是先执行的
	sem_init( &sem2 , 0, 0 );  // two一开始是不执行的。

	
	pthread_t pid01, pid02 ;
	
	if(pthread_create( &pid01, NULL, one , NULL ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	
	if(pthread_create( &pid02 , NULL, two , NULL ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	
	// 等待线程结束
	pthread_join(pid01, NULL);
	pthread_join(pid02, NULL);
	
	// 使用完毕，要销毁信号量：
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	
	
	puts("----end----");

    return 0;
}





