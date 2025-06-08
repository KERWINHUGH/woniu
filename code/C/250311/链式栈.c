/***************************************************
# File Name:    顺序栈.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Tue 11 Mar 2025 11:44:10 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 
 
typedef struct lineStack{
	int data;
	struct lineStack *next;
}LineStack;

LineStack *push(LineStack *head, int data){
	//stack,链式栈
	//data,要入栈的数据
	LineStack *newnode =(LineStack *)malloc(sizeof(LineStack));
	newnode->data = data;
	newnode->next = head;
	head = newnode;
	printf("入栈元素：%d\n",data);
	return head;
}

LineStack *pop(LineStack *head){
	//检查栈是否为空
	if(head == NULL){
		printf("栈为空 \n");
		return head;
	}
	LineStack *temp = head;		//临时变量保存头结点
	printf("出栈元素:%d\n",temp->data);	//从最后一个元素开始出栈
	head = head->next;		//头指针指向下一个节点
	free(temp);		//释放头结点
	return head;
}

int main(int argc, char *argv[]) {
    LineStack *head = NULL;
    for(int i = 0; i < 5; i++){
        head = push(head, i);
    }
    for(int i = 0; i <= 5; i++){
        head = pop(head);
    }
    return 0;
}
