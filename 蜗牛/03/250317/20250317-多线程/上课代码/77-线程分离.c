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
	pthread_t pid = pthread_self();
	printf("线程函数里面得到的id: %ld \n", pid );

	for(int i = 1; i<= 10; i++){
		printf("one函数里：%d ------\n ", i);
		//sleep(1);
		usleep( 100000 );
	}
	return NULL;
}
 
int main(int argc, char *argv[]) {
	
	pthread_t pid;

	if(pthread_create( &pid , NULL, one , NULL) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	printf("main 新线程的id: %ld \n", pid );
	
	
	// 设置隔离线程
	int result = pthread_detach(pid);
	
	if(result != 0){
		perror("线程隔离错误！");
		return 1;
	}
	printf("线程隔离设置是否成功：%d \n", result );
	
	
	for(int i = 1; i<= 10; i++){
		printf("main函数里：%d ====================\n ", i);
		//sleep(1);
		usleep( 100000 );
	}
	
	// 等待线程执行完成：(设置了线程隔离，pthread_join就无效了，因为它们是互斥的。)
	//pthread_join( pid , NULL );
	
	puts("----end----");

    return 0;
}





