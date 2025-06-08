/***************************************************
# File Name:    72-queue.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 06 Mar 2025 02:00:56 PM CST
****************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#define INIT_SIZE 6

typedef struct {
	int *data;
	int length;
	int capacity;
	int front;        // 头
	int rear;         // 尾

}Queue;

// 初始化队列
Queue* init();
// 入队
void add(Queue *q, int value);

// 出队
int out(Queue *q);

// 扩容：
void toBig(Queue *q);

// 回收内存
void freeQueue(Queue *q);

void toString(Queue *q);


 
#endif






