/***************************************************
# File Name:    单链表练习1.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月16日 星期日 14时03分13秒
****************************************************/

#ifndef SINGLE_LITS_H
#define SINGLE_LITS_H

#include "data.h"

typedef struct Node{
	Employee data;
	struct Node *next;
}Node;

//尾插
Node *addNode(Node *head ,Employee user);
Node *createNode(Employee user);
Node *insertNode(Node **head, char *acc,Employee user);
Node *delNode(Node **head, char *acc);
Node *inquireNode(Node *head,char *acc);
Node *modifyNode(Node *head,char *acc,Employee user);
void print(Node *head);
void printList(Node *head);

#endif

