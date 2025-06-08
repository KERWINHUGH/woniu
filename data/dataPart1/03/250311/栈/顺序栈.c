#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

int push(int *stack, int top, int data){
    // int *stack，顺序栈
    // int top，栈顶指针
    // int data，要入栈的数据
    // 检查栈是否已满
    if(top == MAXSIZE - 1){
        printf("栈已满\n");
        return top;
    }
    printf("入栈元素：%d\n", data);
    stack[++top] = data;  // 入栈，栈顶指针加1，栈顶元素赋值
    return top;
}

int pop(int *stack, int top){
    // 检查栈是否为空
    if(top == -1){
        printf("栈为空\n");
        return top;
    }
    printf("出栈元素：%d\n", stack[top--]);
    return top;
}

int main(){
    int stack[MAXSIZE];    // 顺序栈
    int top = -1;          // 栈顶指针
    for(int i=0; i<=MAXSIZE; i++){
        top = push(stack, top, i);
    }
    for(int i=0; i<=MAXSIZE; i++){
        top = pop(stack, top);
    }
}