/***************************************************
# File Name:    86-线程池.c
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
#include "threadpool.h"


// ------------------------------------------------------------------------

// 初始化任务队列
void task_queue_init(TaskQueue *queue, int capacity){
	Task* temp = (Task *)malloc(sizeof(Task) * capacity );
	if(temp == NULL){
		perror("内存分配失败！");
		return;
	}
	queue->tasks = temp;
	queue->capacity = capacity;
	queue->size = 0;
	queue->front = 0;
	queue->rear = -1;
	pthread_mutex_init( &queue->lock,NULL );
	pthread_cond_init( &queue->cond,NULL );
}

// 初始化线程池：                                         线程数        任务队列容量
void thread_pool_init( ThreadPool *pool, int thread_count , int capacity ){
	
	pool->threads = (pthread_t *)malloc( sizeof(pthread_t) * thread_count );
	pool->thread_count = thread_count;
	// 任务队列初始化：
	task_queue_init( &pool->task_queue, capacity);
	pool->is_stopping = false;    // 不是停止状态
	// 初始化线程池的锁
	pthread_mutex_init( &pool->lock, NULL);
	
	// 创建线程，放到线程池数组中：
	for(int i = 0; i < thread_count; i++){
		pthread_create( &pool->threads[i], NULL, worker_thread , pool );
	}
}

// 添加任务到队列
bool task_queue_add( TaskQueue *queue, Task task ){
	// 加锁
	pthread_mutex_lock( &queue->lock );	
	
	// 判断队列是否已经满了
	if(queue->size == queue->capacity){
		// 释放锁
		pthread_mutex_unlock( &queue->lock );	
		return false;  // 队列满了，无法添加任务
	}
	// 添加任务到尾部：
	queue->rear = (queue->rear + 1) % queue->capacity; // 先求出，可以放数据的索引
	queue->tasks[queue->rear] = task;                  // 放置任务到数组里
	queue->size++;
	
	// 通知等待的线程来拿任务
	pthread_cond_signal( &queue->cond );

	// 释放锁
	pthread_mutex_unlock( &queue->lock );	
	
	return true;
}

// 从任务队列中取出任务
bool task_queue_out( TaskQueue *queue, Task *task , bool *is_stopping ){
	// 加锁
	pthread_mutex_lock( &queue->lock );	
	
	// 如果没有任务，就等待。。。。
	while( queue->size == 0 && !*is_stopping ){
		pthread_cond_wait( &queue->cond, &queue->lock );
	}
	// 如果线程池是停止状态，并没有任务
	if(*is_stopping && queue->size == 0){
		pthread_mutex_unlock( &queue->lock );
		return false;
	}
	// 出队：
	*task = queue->tasks[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;

	// 释放锁
	pthread_mutex_unlock( &queue->lock );	
	return true;
}

// 线程函数：
void* worker_thread(void* args){
	ThreadPool *pool = (ThreadPool *)args;
	while(true){
		// 加锁
		pthread_mutex_lock( &pool->lock );
		// 线程池是关闭状态，并且没有任务，退出
		if(pool->is_stopping && pool->task_queue.size == 0){
			// 释放锁
			pthread_mutex_unlock( &pool->lock );
			break;
		};
		// 释放锁
		pthread_mutex_unlock( &pool->lock );
		
		Task task;
		bool f = task_queue_out( &pool->task_queue, &task , &pool->is_stopping);
		if(!f){
			break;
		}
		// 执行任务
		task.function( task.args );
	}
	
	return NULL;
}
// 向线程池提交任务
bool thread_pool_submit(ThreadPool *pool, void (*function)(void *), void *args){

	Task task;
	task.function = function;
	task.args = args;

	return task_queue_add( &pool->task_queue , task);
}

// 任务队列销毁
void task_queue_destroy( TaskQueue *queue ){
	free(queue->tasks);
	pthread_mutex_destroy(&queue->lock);
	pthread_cond_destroy(&queue->cond);
	puts("-----队列销毁完成-----");
}

// 销毁线程池：
void thread_destroy( ThreadPool *pool ){
	// 设置关闭锁：
	pthread_mutex_lock( &pool->lock);
	pool->is_stopping = true;
	pthread_mutex_unlock( &pool->lock);
	
	// 条件变量：通知所有线程
	pthread_cond_broadcast( &pool->task_queue.cond );	
	
	// 等待所有任务结束
	for(int i = 0; i < pool->thread_count; i++){
		pthread_join(pool->threads[i],NULL);
	}
	// 释放掉所有线程：
	free( pool->threads );
	// 任务队列销毁
	task_queue_destroy( &pool->task_queue );
	// 销毁线程池的锁
	pthread_mutex_destroy( &pool->lock);
	puts("******线程池销毁完成******");

}


// 测试函数：
void test_task(void *args){
	int num = *((int *)args);
	printf("线程：%ld --> 正在运行任务。。。 相关的值是：%d \n", pthread_self(),  num);
	free(args);

	//sleep(3);
}








































