/***************************************************
# File Name:    队列练习.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月16日 星期日 16时58分44秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


/*
*  1.基于节点的方式实现队列。特点：先进先出
*  2.结构体组成：1.头结点  2.尾节点  3.数据个数，队列长度  4.队列容量，可以指定，不指定无上限
*  3.队列操作：初始化队列（先申请队列结构体内存），创建节点，出队，入队，打印，查询，修改
**/
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
	int capacity;//（可选）
}Queue;

Node *create(User user);
Queue *initQueue(int capacity);
Queue *inQueue(Queue *q,User user);
User outQueue(Queue *q);
void print(Queue *q);

//创建节点
Node *create(User user){
	Node *newNode = malloc(sizeof(Node));
	newNode->data = user;
	newNode->next =NULL;
	return newNode;
}
//队列初始化，如果capacity为0，队列长度无上限
Queue *initQueue(int capacity){
	Queue *q =malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->length = 0;
	q->capacity = capacity;
	return q;	
}
//入队操作
Queue *inQueue(Queue *q,User user){
	if(q == NULL || q->length>0 && q->length == q->capacity){
		return q;
	}
	//创建新节点
	Node *newNode = create(user);
	//添加新节点到队列中
	//1.如果队列中没有节点，入队节点为第一个
	if(q->rear == NULL){
		q->rear = q->front = newNode;
	}else{
		q->rear->next =newNode;
		q->rear =newNode;
	}
	q->length++;
	puts("入队成功");
	return q;
}
//出队操作，返回值类型为出队元素的类型
User outQueue(Queue *q){
	User u={0};//保存要返回的数据，不能定义节点，因为节点需要释放内存，释放完返回的值就不确定了
	if(q == NULL || q->length ==0){
		return u;
	}
	//队列中是否只有一个节点Node *u
	//不可以写成if(q->front == q->rear)，因为他俩存在都为空的时候
	if(q->length == 1){
		u = q->front->data;
		free(q->front);//释放的是front指向的空间，front本身存的地址还在
		q->front = q->rear =NULL;
	}else{
	//队列有多个节点
		Node *old =q->front;
		u = q->front->data;
		q->front =q->front->next;
		free(old);
	}
	q->length--;
	return u;
}
//打印队列
void print(Queue *q){
	Node *curernt = q->front;
	while(curernt != NULL){
		printf("名字：%s，年龄：%d\n",curernt->data.name,curernt->data.age);
		curernt = curernt->next;
	}
}

int main(int argc, char *argv[]) {
	User u1={"admin1",23};
	User u2={"admin2",23};
	User u3={"admin3",23};
	User u4={"admin4",23};
	User u5={"admin5",23};
	Queue *q =initQueue(4);
	inQueue(q,u1);
	inQueue(q,u2);
	inQueue(q,u3);
	inQueue(q,u4);
	inQueue(q,u5);
	puts("-----------入队-----------");
	print(q);
	puts("-----------出队-----------");
	outQueue(q);
	User u =outQueue(q);
	if(strlen(u.name)!=0){
		puts(u.name);
	}
	/*
	if(strcmp(u.name,u2.name)==0){
		puts(u2.name);
	}else{
		puts(u1.name);
	}
	*/
	outQueue(q);
	outQueue(q);
	//outQueue(q);
	print(q);
	
	
    return 0;
}


