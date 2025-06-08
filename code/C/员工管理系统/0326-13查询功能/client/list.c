/***************************************************
# File Name:    list.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月26日 星期三 20时54分50秒
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Node *create_node(Employee data){
    // 创建并返回一个节点
    Node *node = (Node *)malloc(sizeof(Node));  // 申请内存空间
    node->data = data;    // 为节点数据域赋值
    node->next = NULL;    // 为节点指针域赋值
    return node;
}

Node *add_node(Node *head, Employee data, int index){
    // Node *head，链表头指针
    // int data，要插入的数据
    // int index，要插入的位置
    if(index == 1){
        // 在链表的头部插入新节点
        Node *node = create_node(data);
        node->next = head;    // 将新节点的指针域指向原首元节点
        head = node;          // 将头指针指向新节点
        return head;
    }
    // 在链表的中间或者末尾插入新节点
    Node *temp = head;
    // 查找链表第index-1个节点，即插入位置的直接前驱节点
    for(int i=1; i<index-1; i++){
        temp = temp->next;
        if(temp == NULL){
            printf("链表长度不够，无法插入\n");
            return head;
        }
    }
    Node *node = create_node(data);    // 创建新节点
    node->next = temp->next;           // 将新节点的指针域指向直接后继节点，即插入位置处的原节点
    temp->next = node;                  // 将直接前驱节点的指针域指向新节点
    return head;
}

Node *search_node(Node *head, char *name){
    // 查找链表中包含指定数据的节点
    if(head == NULL){
        printf("链表为空\n");
        return NULL;
    }
    Node *temp = head;
    while(temp != NULL){
        if(strcmp(temp->data.name, name )== 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void change_node(Node *head, char *old_name, char *new_name){
    // 修改链表中包含指定数据的节点的数据域
    Node *temp = search_node(head, old_name);  // 查找包含修改数据的节点
    if(temp == NULL){
        printf("链表中没有找到包含数据%s的节点\n", old_name);
        return;
    }
    strcpy(temp->data.name , new_name);   // 修改节点数据
}

void print_list(Node *head){
    // 打印链表
    Node *temp = head;
    while(temp != NULL){
        //printf("%d ", temp->data.id);
        printf("\nEmployee %d: %s, %s, %d, %.1f, %s, %s, %s, %s",
               temp->data.id,
               temp->data.name,
               temp->data.password,
               temp->data.age,
               temp->data.salary,
               gender_to_string(temp->data.genders),
               department_to_string(temp->data.departments),
               title_to_string(temp->data.titles),
               role_to_string(temp->data.roles));
        temp = temp->next;
    }
    printf("\n");
}

void free_list(Node *head){
    // 释放链表
    Node *temp = head;
    while(temp != NULL){
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
}

Node *delete_node(Node *head, char *name){
    if(search_node(head, name) == NULL){
        printf("链表中没有找到包含数据%s的节点\n", name);
        return head;
    }
    // 删除首元节点
    if(strcmp(head->data.name, name )== 0){
        Node *temp = head;
        head = head->next;    // 将头指针指向原首元节点的下一个节点
        free(temp);           // 释放首元节点
        return head;
    }
    // 删除中间或者末尾节点
    Node *temp = head;
    // 查找包含删除数据节点的直接前驱节点
    while(temp->next != NULL && strcmp(temp->next->data.name, name)){
        temp = temp->next;
    }
    Node *del = temp->next;
    temp->next = temp->next->next;  // 将删除节点的直接前驱指向直接后继
    free(del);
    return head;
}
/*
int main(){
    Node *head = NULL;  // 定义头指针，初始化为NULL
    head = add_node(head, 1, 1);    // 在链表的头部插入节点1
    head = add_node(head, 2, 1);    // 在链表的头部插入节点2
    head = add_node(head, 3, 1);    // 在链表的头部插入节点3
    head = add_node(head, 4, 3);    // 在链表的第3个节点处插入节点4
    head = add_node(head, 5, 2);    // 在链表的第2个节点处插入节点5
    head = add_node(head, 6, 4);
    head = add_node(head, 7, 7);    // 在链表的第7个节点处插入节点7
    print_list(head);
    if(search_node(head, 4) != NULL){
        printf("链表中找到了包含数据4的节点\n");
    }else{
        printf("链表中没有找到包含数据4的节点\n");
    }
    change_node(head, 4, 8);
    print_list(head);
    head = delete_node(head, 17);
    print_list(head);
    free_list(head);
    return 0;
}
*/

