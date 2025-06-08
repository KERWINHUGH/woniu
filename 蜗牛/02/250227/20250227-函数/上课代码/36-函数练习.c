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

// 申明函数：只需要头不需要函数体

//方式一：参数写全
int getAvgFromArray(int array[], int length);
int isExist(int arr[], int length, int value);

//方式二：只写参数类型
int getRadom(int);
int getRadom(int);
bool isPrimeNumber(int);

int main(int argc, char *argv[]) {
	int arr[] = { 10, 20, 30, 60, 70, 80 };
	int length = sizeof(arr) / sizeof(arr[0]);
	// 调用函数，是实参
	int avg = getAvgFromArray(arr, length);
	//printf("数组的平均数是：%d \n", avg);
	
	//int radom = getRadom(10);
	//printf("随机数已经生成，值是：%d \n", radom);
	
	//int value = 100;
	//int index = isExist(arr, length, value);
	//printf("%d,存在于数组的%d号位置.\n", value , index );
	
	int n = 12;
	bool f = isPrimeNumber(n);
	printf("%d是不是质数：%d \n", n, f );
	
	
    return 0;
}



//定义函数，传入一个数组，获取该数组的平均值
//           定义函数：形参
int getAvgFromArray(int array[], int len){
	// 函数体
	int sum = 0;
	for(int i = 0; i < len; i++){
		sum += array[i];
	}
	int avg = sum / len;
	// 把平均数，返回给函数的调用者	
	return avg;
}


//定义函数，传入1个数字，获取1到该数字之间的随机整数
int getRadom(int n){
	srand(time(NULL));
	return (rand() % n) + 1; // 生成1到99之间的随机数
}


//定义函数，传入一个数组以及一个数字，判断该数字是否存在于数组中
// 如果存在，则返回所在的位置
int isExist(int arr[], int length, int value){
	int index = -1;
	for(int i = 0; i < length; i++){
		if(value == arr[i]){
			index = i;
			break;
		}
	}
	return index;
}

//定义函数，传入一个数字，判断该数字是否是质数
bool isPrimeNumber(int n){
	
	for(int i = 2; i < n/2; i++){
		if(n % i == 0){
			return false;	
		}
	}
	return true;
}






















