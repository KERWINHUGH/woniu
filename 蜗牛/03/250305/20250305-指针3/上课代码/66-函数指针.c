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

int getMax(int a, int b){
	return a > b ? a : b;
}
 
int main(int argc, char *argv[]) {a

	// 使用一个函数指针，指向getMax()函数
	int (*p)(int,int) = getMax;
	
	// 现在p指针就代表函数getMax()
	int max = p(9,3);
	
	printf("最大值是：%d \n", max);
	
	
    return 0;
}

























