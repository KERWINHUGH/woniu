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
	// 设置线程不可取消：
	//pthread_setcancelstate( PTHREAD_CANCEL_DISABLE , NULL );
	pthread_setcancelstate( PTHREAD_CANCEL_ENABLE , NULL );
	
	int i = 1;
	while(true){
		
		printf("one函数里：%d ------\n ", i);
		//sleep(1);         // 隐式取消点
		//usleep( 100000 );   // 隐式取消点
		pthread_testcancel(); // 检查是否有取消请求。
		i++;
	}
	return NULL;
}
 
int main(int argc, char *argv[]) {
	
	pthread_t pid;

	if(pthread_create( &pid , NULL, one , NULL) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	
	sleep(2);
	
	int result = pthread_cancel(pid);
	if(result != 0){
		//perror("线程取消失败！");
		fprintf(stderr,"error");
		exit(EXIT_FAILURE);
	}
	
	printf("设置取消是否成功：%d \n", result );

	// 等待线程执行完成
	pthread_join( pid , NULL );
	
	puts("----end----");

    return 0;
}





