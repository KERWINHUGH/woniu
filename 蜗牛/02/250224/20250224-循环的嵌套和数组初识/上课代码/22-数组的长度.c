/***************************************************
# File Name:    18-20250224-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 10:03:44 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	// 数组的长度：
	//int arr[6] = {11,22,33};
	
	char arr[] = "abcdefg";
	
	int length = sizeof(arr) / sizeof(arr[0]);
	for(int i = 0; i < length; i++){
		printf("%d号位置的值是：%d \n", i, arr[i]);
	}
	

    return 0;
}







































