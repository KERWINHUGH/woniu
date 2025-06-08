/***************************************************
# File Name:    list.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月26日 星期三 20时54分50秒
****************************************************/

#include <stdio.h>
#include <stdlib.h>

#ifndef LIST_H
#define LIST_H

#include "data.h"

// 定义结构体，标识链表的节点
typedef struct node {
    Employee data;              // 节点数据域
    struct node *next;     // 节点指针域
}Node;

Node *create_node(Employee data);

Node *add_node(Node *head, Employee data, int index);

Node *search_node(Node *head, char *name);

void change_node(Node *head, char *old_name, char *new_name);

void print_list(Node *head);

void free_list(Node *head);

Node *delete_node(Node *head, char *name);


#endif

