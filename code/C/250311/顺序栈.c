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
 
 
#define MAXSIZE 5

int push(int *stack, int top, int data){
	//stack,顺序栈
	//top,栈顶指针
	//data,要入栈的数据
	//入栈先检查栈是否已满
	if(top==MAXSIZE-1){
		printf("栈已满\n");
		return top;
	}
	printf("入栈元素：%d\n",data);
	stack[++top] = data;	//入栈，栈顶指针+1，站定元素赋值
	return top;
}

int pop(int *stack,int top){
	//检查栈是否为空
	if(top == -1){
	printf("栈为空 \n");
	return top;
	}
	printf("出栈元素:%d\n",stack[top--]);	//从最后一个元素开始出栈
	return top;
}

int main(int argc, char *argv[]) {
	int stack[MAXSIZE];		//顺序栈
	int top=-1;		//栈顶指针
	for(int i = 0; i<=MAXSIZE; i++){
		top = push(stack,top,i);
	}
	for(int i = 0; i<=MAXSIZE; i++){
		top = pop(stack,top);
	}
    return 0;
}
