/***************************************************
# File Name:    队列练习1.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月17日 星期一 09时01分26秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct User{
	char name[16];
	int age;
}User;

typedef struct Node{
	User data;
	struct Node *next;
}Node;

typedef struct Queue{
	Node *front;
	Node *rear;
	int length;
	int capacity;
}Queue;

Node *createNode(User data){
	Node *newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next =NULL;
}

Queue *initQueue(int capacity){
	Queue *q = malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->length = 0;
	q->capacity =capacity;
}

Queue *inQueue(Queue *q,User data){
	if(q == NULL || q->length>0 && q->length == q->capacity){
		return NULL;
	}
	Node *newNode =createNode(data);
	if(q->rear ==NULL){
		q->front = q->rear =newNode;
	}else{
		q->rear->next = newNode;
		q->rear =newNode;
	}
	q->length++;
	return q;	
}

User outQueue(Queue *q){
	User u ={0};
	if(q == NULL || q->length ==0){
		return u;
	}
	if(q->length==1){
		u = q->front->data;
		//->front = q->front->next;
		free(q->front);
		q->front = q->rear =NULL;
	}else{
		Node *old = q->front;
		u =q->front->data;
		q->front=q->front->next;
		free(old);
	}
	q->length--;
	return u;
}

void print(Queue *q){
	Node *current = q->front;
	while(current != NULL){
		printf("姓名：%s，年龄：%d\n",current->data.name,current->data.age);
		current = current->next;
	}
}

int main(int argc, char *argv[]) {
	Queue *q =initQueue(4);
	User u1 ={"admin1",23};
	User u2 ={"admin2",23};
	User u3 ={"admin3",23};
	User u4 ={"admin4",23};
	User u5 ={"admin5",23};
	puts("-------------入队--------------");
	inQueue(q,u1);
	inQueue(q,u2);
	inQueue(q,u3);
	inQueue(q,u4);
	inQueue(q,u5);
	print(q);
	puts("-------------出队--------------");
	outQueue(q);
	outQueue(q);
	print(q);

    return 0;
}


