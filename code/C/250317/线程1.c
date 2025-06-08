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
 
void* one(){
	pthread_t pid = pthread_self();
	printf("线程函数里面得到的id:%ld \n",pid);
	
	//设置线程不可取消：
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	for(int i=1;i<=100;i++){
		printf("one:%d-----------\n",i);
		//sleep(2);		//隐式取消点
		usleep(100000);	//隐式取消点
		
		//prhread_testcancel();	//检查是否有取消请求,需要外部调用之前线程为自动取消
	}
	return NULL;
}
 
int main(int argc, char *argv[]) {
	pthread_t pid;
	
	if(pthread_create(&pid,NULL,one,NULL) != 0){
	
		perror("线程创建失败");
		return 1;
	}
	
	sleep(2);
	
	int result = pthread_cancel(pid);
	
	if(result != 0){
		perror("线程取消失败");
		exit(EXIT_FAILURE);
	}
	printf("设置取消是否成功:%d \n",result);
	pthread_join(pid,NULL);
	
	puts("-------end--------");
	
    return 0;
}
	


