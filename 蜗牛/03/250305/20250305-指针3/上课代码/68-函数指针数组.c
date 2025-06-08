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

	void (*p[4])(float, float);
	
	p[0] = add;
	p[1] = sub;
	p[2] = muti;
	p[3] = division;

	float a, b;
	char mark;
	
	puts("请输入第一个数：");
	scanf("%f", &a);
	puts("请输入第二个数：");
	scanf(" %f", &b);
	puts("请输入运算符：");
	scanf(" %c", &mark);
	
	
	switch(mark){
		case '+':
			p[0](a, b);
		break;
		
		case '-':
			p[1](a, b);
		break;
				
		case '*':
			p[2](a, b);
		break;
				
		case '/':
			p[3](a, b);
		break;
	}

    return 0;
}

























