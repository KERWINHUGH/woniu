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
 
void *one(int *args){
	puts("---------one执行-------------");
	int *result = malloc(sizeof(int));//为要返回的指针分配空间存储返回值，在调用函数之和释放空间，不分配空间会导致函数运行结束指针变量被销毁，应该也可以直接为args指针划分空间，最后返回args
	if(result == NULL){
		perror("内存分配失败！");
		pthread_exit(NULL);
	} 
	int value = *((int *)args);//指针不能直接用来计算，定义一个int型变量存储传进来的值再用来计算，又因为传进来的值是无类型的，需要先将其转成想要的类型才可有下面的操作
	value *= 10;
	*result = value;
	return result;
}
 
int main(int argc, char *argv[]) {
	pthread_t pid;
	
	int para = 99;
	if(pthread_create(&pid,NULL,one,&para) != 0){
		perror("线程创建失败");
		return 1;
	}
	
	int *result = NULL;
	
	if(pthread_join(pid, (void**)&result) != 0){
		perror("jion线程执行失败");
		return 1;
	}
	printf("线程执行结果是:%d\n",*result);
	free(result);
	puts("-------end--------");
	
    return 0;
}
	


