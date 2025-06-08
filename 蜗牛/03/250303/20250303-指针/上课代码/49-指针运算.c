/***************************************************
# File Name:    48-指针初识.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 03 Mar 2025 11:35:19 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int a = 10;
	printf("变量a的地址：%p \n", &a);
	
	int *p = &a;
	printf("指针p指向的地址：%p \n", p );

	puts("---------向后--------------");
	// 实现上是指针向后移动一位
	p++;
	printf("指针p指向的地址：%p \n", p );


	puts("---------char向后--------------");
	char ch = 'c';
	char *pp = &ch;
	printf("指针pp指向的地址：%p \n", pp );
	
	pp--;
	
	printf("指针pp指向的地址：%d \n", *pp );
	
	

    return 0;
}











