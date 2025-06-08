/***************************************************
# File Name:    list.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Mon 10 Mar 2025 10:09:35 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>


#include <string.h>
#include <stdlib.h>
 
//定义结构体，标识链表的节点
typedef struct nod{
    int data;           //节点数据域
    struct nod *next;   //节点指针域
}Node;

Node *creat_node(int data){
    //创建并返回一个节点
    Node *node =(Node *)malloc(sizeof(Node));
    node->data =data;   //为节点数据域赋值
    node->next =NULL;   //为节点指针域赋值
    return node;
}

int main(){
    Node *head =NULL;   //定义头指针，初始化为NULL
    head =creat_node(1);    //创建首元结点，保存数据1；并将头指针指向首元结点
    printf("%d \n",head->data);
    //在首元结点位置插入新节点
    Node *new_node = creat_node(2); //创建第二个节点
    new_node->next =head;   //  将新节点的指针指向原首元结点
    head = new_node;    //  将头指针指向新节点

    printf("%d\n",head->data);  //输出首元结点的数据域的值
    printf("%d\n",head->next->data);    //输出第二个节点的数据域的值
}
