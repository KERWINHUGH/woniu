/***************************************************
# File Name:    线程.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月17日 星期一 11时11分57秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
 
 
//利用同步和互斥来解决以下问题；定义三个线程，分别可以打印A、B、C。利用同步和互斥来实现最终打印BCABCABCA
sem_t  sem1;
sem_t  sem2;
sem_t  sem3;


void* one(){
	for(int i =1;i<10;i++){
		sem_wait(&sem1);
		printf("%c",'A');
		sem_post(&sem2);
	}
	return NULL;
}
void* two(){
	for(int i =1;i<10;i++){
		sem_wait(&sem2);
		printf("%c",'B');
		sem_post(&sem3);
	}
	return NULL;
}
void* three(){
	for(int i =1;i<10;i++){
		sem_wait(&sem3);
		printf("%c",'C');
		sem_post(&sem1);
	}
	return NULL;
}
 
int main(int argc, char *argv[]) {
	pthread_t pid1;
	pthread_t pid2;
	pthread_t pid3;
	
	sem_init(&sem1,0,0);
	sem_init(&sem2,0,1);
	sem_init(&sem3,0,0);
	
	if(pthread_create(&pid1,NULL,one,NULL) != 0){
		perror("线程1创建失败");
		return 1;
	}
	if(pthread_create(&pid2,NULL,two,NULL) != 0){
		perror("线程2创建失败");
		return 1;
	}
	if(pthread_create(&pid3,NULL,three,NULL) != 0){
		perror("线程2创建失败");
		return 1;
	}
	
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	pthread_join(pid3,NULL);
	
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	sem_destroy(&sem3);
	
	puts("-------end--------");
	
    return 0;
}
	


