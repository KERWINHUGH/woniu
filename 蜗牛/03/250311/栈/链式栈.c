#include <stdio.h>
#include <stdlib.h>

typedef struct lineStack{
    int data;
    struct lineStack *next;
}LineStack;

LineStack *push(LineStack *head, int data){
    // 元素入栈
    LineStack *newNode = (LineStack *)malloc(sizeof(LineStack));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    printf("入栈元素为：%d\n", data);
    return head;
}

LineStack *pop(LineStack *head){
    // 元素出栈
    // 检查栈是否为空
    if(head == NULL){
        printf("栈为空\n");
        return head;
    }
    LineStack *temp = head;   // 临时变量保存头结点
    printf("出栈元素为：%d\n", temp->data);
    head = head->next;  // 头结点指向下一个结点，即链表的第2个节点
    free(temp);    // 释放头节点
    return head;
}

int main(){
    LineStack *head = NULL;
    for(int i = 0; i < 5; i++){
        head = push(head, i);
    }
    for(int i = 0; i <= 5; i++){
        head = pop(head);
    }
}