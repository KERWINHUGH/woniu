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

 
int main(int argc, char *argv[]) {

	int a = 100;

	int *p = malloc(sizeof(int));   //分配内存，没有问题可以运行
	if(p == NULL){
		perror("内存分配失败！");
		return 1;
	}
	
	//int *p;         // 这是野指针
	//int *p = NULL;    // 这个指针，有初始值NULL，但是不能解引用。 
	
	// 可以通过编译，但运行会有错误。
	//*p = a;  // 野指针，不可以解引用操作。会有段错误。
	
	*p = 999;
	printf("p指向的地址：%p,  值是：%d \n",p,  *p );	

	free(p);
	puts("----------- 指针已经被释放 ---------------");
	p = NULL;
	printf("p指向的地址：%p, \n",p );	
	
    return 0;
}


















