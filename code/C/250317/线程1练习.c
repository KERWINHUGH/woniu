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
	printf("线程1函数里面得到的id:%ld \n",pid);
	
	//设置线程不可取消：
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	
	FILE *fp =fopen("./test.c","w");
	
	char id[]={"NO.001"};
	char name[] = {"王者"};
	int score = 100;
	fprintf(fp,"学号：%s，姓名：%s，成绩：%d\n",id,name,score);
	//usleep(100000);	//隐式取消点
		
	fclose(fp);
	
	return NULL;
}
void* two(){
	pthread_t pid = pthread_self();
	printf("线程2函数里面得到的id:%ld \n",pid);
	
	//设置线程不可取消：
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	
	FILE *fp =fopen("./test.c","r");
	if(fp ==NULL){
		perror("打开文件失败");
		return NULL;
	}
	
	char id[16];
	char name[16];
	int score;
	fscanf(fp,"%s，%s，%d\n",id,name,&score);
	printf("读到的数据是%s，%s，%d\n",id,name,score);
	usleep(1000);	//隐式取消点
	fclose(fp);
	return NULL;
}
 
int main(int argc, char *argv[]) {
	pthread_t pid1;
	pthread_t pid2;
	
	if(pthread_create(&pid1,NULL,one,NULL) != 0){
	
		perror("线程1创建失败");
		return 1;
	}
	if(pthread_create(&pid2,NULL,two,NULL) != 0){
	
		perror("线程2创建失败");
		return 1;
	}
	
	//sleep(2);
	
	int result1 = pthread_cancel(pid1);
	int result2 = pthread_cancel(pid2);
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
	


