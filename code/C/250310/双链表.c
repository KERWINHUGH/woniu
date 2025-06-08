/***************************************************
# File Name:    单链表.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Mon 10 Mar 2025 03:50:41 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// 定义结构体，标识链表的节点
typedef struct Node {
    int data;           // 数据域
    struct Node *next;  // 指针域，指向直接后继节点
    struct Node *prev;  // 指针域，指向直接前驱节点
}Node;

Node *createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

Node *insertNode(Node *head, int data, int index){
    Node *node = createNode(data);   // 创建新节点
    if(index == 1){
        node->next = head;    // 新节点的next指针域指向原第1个节点
        head->prev = node;    // 原第1个节点的prev指针域指向新节点
        head = node;          // 头指针指向新节点
        return head;
    }
    // 找到第index-1个节点，即插入位置的前一个节点
    Node *temp = head;
    for(int i = 1; i < index-1; i++){
        temp = temp->next;
        if(temp == NULL){
            printf("链表长度不够，无法插入\n");
            return head;
        }
    }
    if(temp->next == NULL){   // 插入位置在尾部
        temp->next = node;
        node->prev = temp;
    }else{   // 插入位置在中间
        node->next = temp->next;   // 新节点的next指针指向第index个节点
        temp->next->prev = node;   // 第index个节点的prev指针指向新节点
        node->prev = temp;         // 新节点的prev指针指向第index-1个节点
        temp->next = node;         // 第index-1个节点的next指针指向新节点
    }
    
    return head;

}

Node *deleteNode(Node *head, int data){
    // 删除包含指定数据的节点
    Node *temp = head;
    while(temp != NULL){
        if(temp->data == data){
            if(temp->prev == NULL){  // 删除节点为链表的第1个节点
                head = temp->next;   // 头指针指向第2个节点
                head->prev = NULL;   // 第1个节点的prev指针置为NULL
                free(temp);           // 释放内存
                return head;          // 返回头指针
            }
            if(temp->next == NULL){  // 删除节点为链表的最后一个节点
                temp->prev->next = NULL;   // 将删除节点的前一个节点的next指针指向NULL
                free(temp);
                return head;
            }
            // 删除中间节点
            temp->next->prev = temp->prev;   // 将删除节点的后一个节点的prev指针指向删除节点的前一个节点
            temp->prev->next = temp->next;   // 将删除节点的前一个节点的next指针指向删除节点的后一个节点
            free(temp);
            return head;
        }
        temp = temp->next;
    }
    printf("要删除的节点不存在\n");
    return head;
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

Node *searchNode(Node *head, int data) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    printf("未找到包含%d的节点\n",data);
    return NULL;
}

int updateNode(Node *head, int data, int newData) {
    // 修改节点数据，成功返回1，失败返回-1
    Node *temp = searchNode(head, data);   // 查找包含数据data的节点
    if (temp != NULL) {
        temp->data = newData;
        return 1;
    }
    return -1;
}

void freeList(Node *head){
    Node *temp = head;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
}

int main() {
    Node *head = createNode(1);  // 头指针，指向第一个节点
    // 在第1个位置插入新节点
    head = insertNode(head, 2, 1);
    head = insertNode(head, 3, 1);
    head = insertNode(head, 4, 1);
    head = insertNode(head, 5, 1);
    printList(head);
    // 在第2个位置插入新节点，即在当前的2个节点之间插入1个新节点
    head = insertNode(head, 6, 2);
    printList(head);
    // 删除第1个节点，包含数据5的节点
    head = deleteNode(head, 5);
    printList(head);
    // 删除最后一个节点，包含数据1的节点
    head = deleteNode(head, 1);
    printList(head);
    // 删除第2个节点，包含数据4的节点
    head = deleteNode(head, 4);
    printList(head);
    // 将链表中包含数据6的节点，修改为数据8
    updateNode(head, 6, 8);
    printList(head);
    freeList(head);   // 释放链表
    return 0;
}
