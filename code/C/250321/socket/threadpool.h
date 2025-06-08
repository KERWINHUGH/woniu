/***************************************************
# File Name:    86-线程池.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 18 Mar 2025 02:06:03 PM CST
****************************************************/

#ifndef THREADPOOL_H
#define THREADPOOL_H

// 任务结构体
typedef struct Task{
	void (*function) (void* args); // 任务函数指针
	void *args;                    // 对应的参数

}Task;

// 任务队列
typedef struct TaskQueue {
	Task *tasks;
	int capacity;   // 容量
	int size;       // 任务数
	int front;
	int rear;
	
	pthread_mutex_t lock;  // 互斥锁
	pthread_cond_t cond;   // 条件变量用于通知

}TaskQueue;

// 线程池结构体
typedef struct ThreadPool {
	pthread_t *threads;        // 线程数组
	int thread_count;          // 线程池中的线程数
	TaskQueue task_queue;      // 任务队列
	
	bool is_stopping;          // 是否停止
	pthread_mutex_t lock;  // 互斥锁

}ThreadPool; 


// 初始化任务队列
void task_queue_init(TaskQueue *queue, int capacity);
// 初始化线程池：                                         线程数        任务队列容量
void thread_pool_init( ThreadPool *pool, int thread_count , int capacity );
// 添加任务到队列
bool task_queue_add( TaskQueue *queue, Task task );
// 从任务队列中取出任务
bool task_queue_out( TaskQueue *queue, Task *task , bool *is_stopping );
// 线程函数：
void* worker_thread(void* args);
// 向线程池提交任务
bool thread_pool_submit(ThreadPool *pool, void (*function)(void *), void *args);
// 任务队列销毁
void task_queue_destroy( TaskQueue *queue );
// 销毁线程池：
void thread_destroy( ThreadPool *pool );

// 测试函数：
void test_task(void *args);


#endif




































