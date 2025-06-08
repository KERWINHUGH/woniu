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
 
void* one(){

	//int currentticket = *((int *)ticket);
	while(ticket!=0){
		printf("线程1卖出第%d张票\n",ticket--);
		//usleep(100000);
	}
	
	return NULL;
}
void* two(){

	//int currentticket = *((int *)ticket);
	while(ticket!=0){
		printf("线程2卖出第%d张票\n",ticket--);
		//usleep(100000);
	}

	return NULL;
}
 
int main(int argc, char *argv[]) {
	pthread_t pid1;
	pthread_t pid2;
	
	if(pthread_create(&pid1,NULL,one,&ticket) != 0){
		perror("线程1创建失败");
		return 1;
	}
	if(pthread_create(&pid2,NULL,two,&ticket) != 0){
		perror("线程2创建失败");
		return 1;
	}
	
	//sleep(2);
	
	//int result1 = pthread_cancel(pid1);
	//int result2 = pthread_cancel(pid2);
	/*
	if(result1 != 0){
		perror("线程1取消失败");
		exit(EXIT_FAILURE);
	}
	printf("设置取消是否成功:%d \n",result1);
	if(result2 != 0){
		perror("线程2取消失败");
		exit(EXIT_FAILURE);
	}
	printf("设置取消是否成功:%d \n",result2);
	*/
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	
	puts("-------end--------");
	
    return 0;
}
	


