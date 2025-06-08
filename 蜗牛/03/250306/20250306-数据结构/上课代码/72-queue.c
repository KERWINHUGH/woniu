/***************************************************
# File Name:    72-queue.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 06 Mar 2025 02:00:56 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
 
// ------------------------------------------------------------- 
int main(int argc, char *argv[]) {
	Queue *q = init();

	add(q, 100);
	add(q, 200);
	add(q, 300);
	add(q, 400);
	add(q, 500);
	add(q, 600);
	
	toString(q);
	puts("---------------------");
	out(q);
	out(q);
	out(q);
	out(q);
	out(q);
	add(q, 700);
	toString(q);

	
	freeQueue(q);


    return 0;
}
// ------------------------------------------------------------- 

// 初始化队列
Queue* init(){
	Queue *q = malloc(sizeof(Queue));
	if(q == NULL){
		perror("分配内存失败");
		return NULL;
	}
	
	q->data = malloc(sizeof(int) * INIT_SIZE);
	if(q->data == NULL){
		perror("分配内存失败");
		return NULL;
	}
	q->length = 0;
	q->capacity = INIT_SIZE;
	q->front = -1;        
	q->rear = -1;
	
	return q;
}

// 入队
void add(Queue *q, int value){
	// 扩容。。。
	toBig(q);
	
	// 向最后一个位置添加数据：
	q->data[q->rear+1] = value;
	q->rear ++;  // 尾部指针加1
	q->length++; // 长度加1
	// 首指针处理：
	if(q->front == -1){
		q->front++;
	}
	
}

// 出队
int out(Queue *q){
	// 队列中，有数据才出队操作：
	if(q->length > 0){
		// 得到需要的数据
		int temp = q->data[q->front];
		// 把头部数据置空
		q->data[q->front] = 0;
		
		if(q->length == 1){
			q->front = -1;
			q->rear = -1;
		}else {
			// 首位后移：
			q->front++;
		}
		// 元素个数减1
		q->length--;
		
		return temp;
	}
	
	return 0;
}

// 扩容：
void toBig(Queue *q){
	if(q->length == q->capacity){
		puts("------------ 双倍扩容 --------------");
		int newSize = q->capacity * 2;
		
		int *temp = realloc( q->data, newSize * sizeof(int) );
		memset( temp + q->length , 0 , sizeof(int) * newSize / 2 );
		
		q->capacity = newSize;
		
		q->data = temp;
		
	}else if( q->rear + 1 == q->capacity && q->length < q->capacity / 2  ){
		puts("------------ 数据移动扩容 --------------");
		// 2：移动数据：
		for(int i = 0, j = q->front; i < q->capacity && j <= q->rear; i++, j++){
			q->data[i] = q->data[j];
		}
		// 移动数据之后，重置首和尾的指针
		q->front = 0;
		q->rear = q->length -1;
	
	}
	
}

void toString(Queue *q){
	printf("当前元素个数:%d , 容量是:%d , 头索引:%d , 尾索引:%d \n", 
				q->length, q->capacity, q->front, q->rear );
	printf("数据：[");
	
	if(q->length > 0){
		for(int i = q->front ; i <= q->rear ; i++){
			if(i == q->rear){
				printf("%d ", q->data[i]);
			}else {
				printf("%d ,", q->data[i]);
			}
		}
	}
	
	printf("]\n");
				
}
// 回收内存
void freeQueue(Queue *q){
// 先回收成员，再回收结构体：（先小->大）
	free(q->data);
	free(q);
	
	q->data = NULL;
	q = NULL;
	puts("----内存回收完成----");
}





