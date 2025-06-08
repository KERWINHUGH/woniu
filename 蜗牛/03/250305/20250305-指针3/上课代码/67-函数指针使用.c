/***************************************************
# File Name:    61-其它类型指针.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 05 Mar 2025 02:03:56 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void add(float a, float b){
	printf("加法结果：%f \n", a + b);
}

void sub(float a, float b){
	printf("减法结果：%f \n", a - b);
}

void muti(float a, float b){
	printf("乘法结果：%f \n", a * b);
}

void division(float a, float b){
	printf("除法结果：%f \n", a / b);
}
 
 
int main(int argc, char *argv[]) {

	float a, b;
	char mark;
	
	puts("请输入第一个数：");
	scanf("%f", &a);
	puts("请输入第二个数：");
	scanf(" %f", &b);
	puts("请输入运算符：");
	scanf(" %c", &mark);
	
	void (*p)(float, float) = NULL;
	
	switch(mark){
		case '+':
			p = add;
		break;		
		case '-':
			p = sub;
		break;		
		case '*':
			p = muti;
		break;		
		case '/':
			p = division;
		break;
	}
	// 执行函数
	p(a,b);
	
    return 0;
}

























