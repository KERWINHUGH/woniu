/***************************************************
# File Name:    24-homework20250225.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 25 Feb 2025 09:44:27 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>  // 包含这个头文件以使用 rand() 和 srand()

void one(){
	int arr[4][3] = {0};
	
	arr[0][0] = 100;
	arr[1][1] = 111;
	arr[2][2] = 122;
	
	int oneLength = sizeof(arr) / sizeof(arr[0]);
	int twoLength = sizeof(arr[0]) / sizeof(arr[0][0]);
	
	// 二维数组的遍历
	
	// 外层循环，循环的是第一维度（层数）
	for(int i = 0; i < oneLength ; i++){
		// 里层循环，循环的是第二维度（列数）
		for(int j = 0; j < twoLength; j++){
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}		
// 练习：
// 创建一个二维数组：1维的长度是：5， 2维的长度是：4 
// 给每个维度赋值：值100+一维索引（十位）+二维索引（个位）
// 比如 arr[3][2] 的值是：132 
// 遍历该二维数组：
void two(){
	int arr[5][4] = {0};
	
	int oneLength = sizeof(arr)/ sizeof(arr[0]);
	int twoLength = sizeof(arr[0])/ sizeof(arr[0][0]);
	
	// 赋值
	for(int i = 0; i < oneLength; i++){
		for(int j = 0; j < twoLength; j++){
			arr[i][j] = 100 + i * 10 + j;
		}
	}
	// 遍历
	for(int i = 0; i < oneLength; i++){
		for(int j = 0; j < twoLength; j++){
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}

 
int main(int argc, char *argv[]) {
	// 二维数组的定义：
	// 1:  int arr[3][4] = {0};
	//     int arr[3][2] = { {1,2},{21,22},{31,32} };
	
	// 2：线性初始化
	//int arr[][3] = {1,2,3,4,5,6,7,8};
	
	int arr[][5] = {1,2,3,4,5,6,7};
	
	
	int oneLength = sizeof(arr)/ sizeof(arr[0]);
	int twoLength = sizeof(arr[0])/ sizeof(arr[0][0]);
	// 遍历
	for(int i = 0; i < oneLength; i++){
		for(int j = 0; j < twoLength; j++){
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	
	
    return 0;
}


























































