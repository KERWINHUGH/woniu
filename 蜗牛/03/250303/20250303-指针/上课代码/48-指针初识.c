/***************************************************
# File Name:    48-指针初识.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 03 Mar 2025 11:35:19 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void changeX(int* p);

void changeValueByInt(int x){
	x += 5;
	printf("x:%d \n", x);
}

 
int main(int argc, char *argv[]) {
	int a = 10;

	// 使用指针，存住变量a的地址：
	// 指针：存的是一个变量的地址。
	int *p;
	p = &a;

	
	// 通过地址，找到值：
	printf("a的内存地址是：%p \n", &a );
	printf("p存的内存地址是：%p \n", p );
	//                        解引用：通过指针，找到该指针指向的地址存的值
	printf("p指向内存的值：%d \n", *p );
	// 通过指针，改变指向变量的值
	*p += 9;

	printf("a: %d \n", a);
	
	// 练习：有一个变量，值为20，写函数，改变该变量的值。（通过指针实现）
	int x = 20;
	
	int* pp = NULL;
	
	printf("pp存的值: %p \n", pp );
	printf("pp自己的地址: %p \n", &pp );
	pp = &x;
	
	
	changeX( pp );
	
	printf("x的值为：%d \n", x);
	
	float *pp2;

	printf("point size: %ld \n", sizeof(pp2));



    return 0;
}

void changeX(int *p){
	*p += 3;
}










