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
 
int ticket=100;
 
pthread_mutex_t mutex;


void* save(void *args){
	
	char *id =(char *)args;
	
	while(ticket!=0){
	pthread_mutex_lock(&mutex);
		if(ticket>0){
			
			usleep(100000);
			printf("%s卖出第%d张票\n",id,ticket--);
			
			pthread_mutex_unlock(&mutex);
			
		}else{
			pthread_mutex_unlock(&mutex);
			break;
		}
	}
	return NULL;
}

 
int main(int argc, char *argv[]) {
	
	if(pthread_mutex_init(&mutex,NULL) !=0){
		perror("互斥锁初始化失败");
		return 1;
	}
	
	pthread_t pid1;
	pthread_t pid2;
	pthread_t pid3;
	
	char *p1[] ={"微信","支付宝","12306"};
	
	if(pthread_create(&pid1,NULL,save,&p1[0]) != 0){
		perror("线程1创建失败");
		return 1;
	}
	if(pthread_create(&pid2,NULL,save,&p1[1]) != 0){
		perror("线程2创建失败");
		return 1;
	}
	if(pthread_create(&pid3,NULL,save,&p1[2]) != 0){
		perror("线程3创建失败");
		return 1;
	}
	
	

	
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	pthread_join(pid3,NULL);
	
	pthread_mutex_destroy(&mutex);
	
	puts("-------end--------");
	
    return 0;
}
	


