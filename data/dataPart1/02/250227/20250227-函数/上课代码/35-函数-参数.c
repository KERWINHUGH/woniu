/***************************************************
# File Name:    31-字符串.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:04:09 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// 当数组以参数的形式，传递给形参，它其实是一个指针。
void getMax(int *arr , int length ){
	//int length = sizeof(arr) / sizeof(arr[0]);
	
	int max = arr[0];
	for(int i = 0 ;i < length; i ++){
		if(arr[i] > max){
			max = arr[i];
		}
	}
	printf("数组的最大值是：%d \n", max);
}

int main(int argc, char *argv[]) {

	int arr[] = {11,21,33,120,1,66,77,88};
	int length = sizeof(arr) / sizeof(arr[0]);
	
	getMax(arr , length );	
	
    return 0;
}
























