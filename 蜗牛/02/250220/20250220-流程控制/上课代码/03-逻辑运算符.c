/***************************************************
# File Name:    03-逻辑运算符.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 06:33:57 PM PST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
int main(int argc, char *argv[]) {
	int a = 100;
	int b = 10;
	// & 与运算规则：所有条件为真，整个表达式才为真。
	// | 或运算规则：有一个条件为真，整个表达式就为真。
	
	// && : 当表达式中有一个false, 则后面的表达式不运算
	// || : 当表达式中有一个true, 则后面的表达式不运算
	
	if(++b > 10 || ++a >100 ){
		printf("--条件满足--\n");
	}else {
		printf("=====条件不满足！=====\n");
	}

	printf("a: %d, b:%d \n", a, b);
	
	// ! 是取反符号：真的变假的，假的变真的。
	bool f = false;
	bool f2 = true;
	
	printf("bool运算：%d \n", f - f2);
	
	//int num = 0;
	
	char num = 'x';
	
	if(num){   
		puts("---是真的---");
	}else {
		puts("**** 是假的 ****");
	}
	

    return 0;
}








