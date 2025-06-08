/***************************************************
# File Name:    84-生产者消费者-单次.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 18 Mar 2025 02:06:03 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>   // sleep

pthread_mutex_t mutex;  // 锁
pthread_cond_t cond;  // 条件变量

int sharedData = 0;
bool dataReady = false; 

void *product(){
	// 生产数据的时候，加上锁。
	pthread_mutex_lock(&mutex);

	sleep(1);  // 代表生产数据要花的时间。
	// 生产数据：
	sharedData = 9999;
	dataReady = true;
	
	printf("生产者已经生产了一个数据，消费者可以来消费了。\n");
	
	// 通知消费者来消费数据
	pthread_cond_signal(&cond);
	
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *consumer(){
	// 消费数据的时候，加上锁。
	pthread_mutex_lock(&mutex);
	
	while(!dataReady){
		puts("消费者正在等待数据。。。。");
		
		pthread_cond_wait(&cond, &mutex);
	}
	
	printf("消费者可以消费数据了：%d \n", sharedData );
	dataReady = false;  // 重置数据的状态

	pthread_mutex_unlock(&mutex);
	return NULL;
}
 
int main(int argc, char *argv[]) {

	// 初始化锁和条件变量：
	if(pthread_mutex_init(&mutex,NULL) != 0){
		perror("mutex error!");
		return 1;
	}
	if(pthread_cond_init(&cond, NULL ) != 0){
		perror("cond error!");
		return 1;
	}
	pthread_t one, two;
	
	if(pthread_create( &two, NULL, consumer, NULL) != 0){
		perror("thread error");
		return 1;
	}
	
	sleep(1);
	
	// 创建线程
	if(pthread_create( &one, NULL, product, NULL) != 0){
		perror("thread error");
		return 1;
	}
	
	// 等待线程结束
	pthread_join(one, NULL);
	pthread_join(two, NULL);

	// 销毁锁：
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

    return 0;
}





