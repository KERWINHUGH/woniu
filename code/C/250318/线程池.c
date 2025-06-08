/***************************************************
# File Name:    线程池.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月18日 星期二 16时29分30秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//任务结构体
typedef struct Task{
	void (*fun) (*args);	//任务函数指针
	void *args;				//函数参数
}Task;

//任务队列
typedef struct TaskQueue{
	Task *tasks;	
	int front;
	int rear;
	int size;		//任务数 
	int capacity;
	
	pthread_t lock;	//互斥锁		用于任务互斥		？
	pthread_t cond;		//条件变量
}TaskQueue;
 

typedef struct TreadPool{
	pthread_t *threads;	//线程数组
	int thread_count;	//线程池中线程数量
	TaskQueue task_queue;	//任务队列
	
	int is_status;		//用于判断线程池的状态，为1时任务不能再进入线程池，线程池将被销毁
	pthread_t lock;	//用于线程取任务时互斥
}TreadPool; 



int main(int argc, char *argv[]) {

    return 0;
}


