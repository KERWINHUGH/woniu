/***************************************************
# File Name:    单链表练习1.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月16日 星期日 14时03分13秒
****************************************************/

#ifndef SINGLE_LITS_H
#define SINGLE_LITS_H

typedef struct User{
	char acc[16];
	char name[16];
	char pass[16];
	char phone[16];
	char addr[16];
}User;

typedef struct Node{
	User data;
	struct Node *next;
}Node;

Node *createNode(User user);
Node *insertNode(Node **head, char *acc,User user);
Node *delNode(Node **head, char *acc);
Node *inquireNode(Node *head,char *acc);
Node *modifyNode(Node *head,char *acc,User user);
void print(Node *head);

#endif

