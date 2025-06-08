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

// 二级指针，基本概念
void one(){
 	int num = 100;
	printf("num的地址是：%p, 值是：%d \n", &num, num);
	int *p = &num;
	printf("p的地址是：%p, 值是：%p   ,目标变量的值：%d \n", &p, p , *(p) );
	int **pp = &p;
	printf("pp的地址是：%p, 值是：%p , 目标变量的值:%d \n", &pp, pp,  *(*pp) );
}
 
int main(int argc, char *argv[]) {
	
	int arr[][3] = {11,22,33,44,55,66,77,88,99};
	// 使用指针数组
	int *p[3];
	
	p[0] = arr[0];   // 指向二维数组的第0行
	p[1] = arr[1];
	p[2] = arr[2];
	
	printf( "0号位置： %p \n", &arr[0] );
	printf( "1号位置： %p \n", &arr[1] );
	printf( "2号位置： %p \n", &arr[2] );
	
	int oneLength = sizeof(arr) / sizeof(arr[0]);
	int twoLength = sizeof(arr[0]) / sizeof(arr[0][0]);
	
	puts("-----------------------------------");
	int **pp = p;
	
	for(int i = 0; i < oneLength; i++){
		//printf( "%d号位置： %p \n",i,  pp[i] );
		for(int j = 0; j < twoLength; j++){
			printf("[%d][%d]值：%d , %d , %d \t", i, j , pp[i][j] ,  *(pp[i]+j) ,   *(*(pp + i)+j)  );
		}
		printf("\n");
	}
	
    return 0;
}























