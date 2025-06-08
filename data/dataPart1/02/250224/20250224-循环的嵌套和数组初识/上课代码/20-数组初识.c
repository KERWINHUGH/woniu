/***************************************************
# File Name:    18-20250224-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 10:03:44 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	// 同时储存多个数字，11 22,33,44...88 这8个数，应该怎么做？
	//int arr[] = {11,22,33,44,55,66,77,88};
	// 定义了一个长度为10的数组，并把所有的位置初始化为：0
	int arr[10] = {0};
	// 从数组里面取值：数组名[索引] 
	/*
	printf("%d \n", arr[0] );
	printf("%d \n", arr[1] );
	printf("%d \n", arr[4] );
	printf("%d \n", arr[7] );
	*/
	// 给数组的某个位置赋值： 数组名[索引] = 值
	arr[3] = 33;
	arr[5] = 55;
	
	// 遍历：访问数组里的所有数据
	int index = 0;
	printf("%d \n", arr[index] );
	// 求出数组的长度：（长度：代表数组里可以存几个数据）	
	int arr_size = sizeof(arr) ;
	
	printf("数组的字节数：%d \n", arr_size);

	// 数组的长度：数组的总字节数 /  数组的0号位置的字节数
	int length = sizeof(arr) / sizeof(arr[0]);
	printf("数组的长度：%d \n", length );
	
	puts("----------------- 数组的遍历 ------------------------");
	for(int i = 0; i < length; i++ ){
		printf("%d \n", arr[i] );
	}

    return 0;
}







































