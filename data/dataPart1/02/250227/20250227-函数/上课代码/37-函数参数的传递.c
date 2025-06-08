/***************************************************
# File Name:    31-字符串.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:04:09 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>  // 包含这个头文件以使用 rand() 和 srand()



void changeValue(int a, int b){
	int temp = a;
	a = b;
	b = temp;

	printf("函数里： a: %d,   b: %d \n", a, b);
}

void testOne(int x){
	x += 100;
	printf("函数里：%d \n", x);
}

void testTwo(int *x){
	*x += 100;
	printf("函数里：%d \n", *x);
}




void changeArray(int arr[]){
	arr[0] = 1199;
}


int main(){
// 1: 值传递 ------- 相当于 "实参" 把自己的值复制了一份给到 "形参" -------------------
	// 两值交换
	//int x = 100;
	//int y = 22;
	//changeValue(x, y);
	//printf("main里： x: %d,   y: %d \n", x,  y );

	// 单值改变
	//int a = 99;//testOne(a);
	//printf("main函数里：%d \n", a);

// 2: 地址传递 --------------------------
	int a = 99;
	testTwo( &a );
	printf("main函数里：%d \n", a);
	
	/*
	// 改变数组里的值：
	int ss[] = {11,22,33,44,55,66};
	changeArray(ss);
	
	for(int i = 0; i < 6; i++){
		printf("%d \t", ss[i]);
	}
	printf("\n");
	*/
	
	return 0;
}








	
