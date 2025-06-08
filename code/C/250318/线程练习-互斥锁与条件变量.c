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
 
 
pthread_mutex_t mutex;
pthread_cond_t cond;

int share_data = 0;
int dataReady =0;

int num=10;

void* producer(void *args){
	
	for(int i=0;i<10;i++){
		pthread_mutex_lock(&mutex);		//拿到锁，并上锁
		//生产一个数据之后等待消费者来消费
		while(dataReady){
			printf("正在等待消费者消费！\n");
			
			//使用条件变量挂起生产者，等待消费者消费
			pthread_cond_wait(&cond,&mutex);
		}
		
		usleep(200000);		//代表生产者生产花费的时间
		
		share_data = (i+1)*10;	//生产数据
		
		dataReady = 1;		//数据已经被生产了的标志
		
		printf("生产者已经生产了一个数据:%d\n",share_data);
		
		pthread_cond_signal(&cond);		//通知线程
		
		pthread_mutex_unlock(&mutex);	//解锁
	
	}
	return NULL;
}

void* consumer(void *args){
	
	for(int i=0;i<10;i++){
		pthread_mutex_lock(&mutex);		//拿到锁，并上锁，消费时不能再让生产者修改数据
		//代表消费者等待生产者生产数据，即等待生产标志dataReady=1;
		while(dataReady != 1){
			puts("消费者正在等待数据！\n");
			
			//使用条件变量等待数据，同时释放锁
			pthread_cond_wait(&cond,&mutex);
		}		
		
		//循环结束代表生产者已经生产好数据
		//消费者消费数据
		//share_data = 999;	//生产数据
		
		printf("消费者已经消费了一个数据:%d\n",share_data);
		
		dataReady = 0;		//数据已经被消费了的标志
		
		//唤醒生产者
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);	//解锁
	
	}
	return NULL;
}
 
int main(int argc, char *argv[]) {
	
	pthread_t one, two;
	
	
	if(pthread_mutex_init(&mutex,NULL) !=0){
		perror("互斥锁初始化失败");
		return 1;
	}
	if(pthread_cond_init(&cond,NULL) !=0){
		perror("条件变量初始化失败");
		return 1;
	}
	
	pthread_t producer_thread,consumer_thread;
	
	/*
	if(pthread_create(&producer_thread,NULL,producer,NULL) != 0){
		perror("互斥锁线程创建失败");
		return 1;
	}
	*/
	if(pthread_create(&consumer_thread,NULL,consumer,NULL) != 0){
		perror("条件变量线程创建失败");
		return 1;
	}
	sleep(1);
	if(pthread_create(&producer_thread,NULL,producer,NULL) != 0){
		perror("互斥锁线程创建失败");
		return 1;
	}
	
	pthread_join(producer_thread,NULL);
	pthread_join(consumer_thread,NULL);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	
	puts("-------end--------");
	
    return 0;
}
	


