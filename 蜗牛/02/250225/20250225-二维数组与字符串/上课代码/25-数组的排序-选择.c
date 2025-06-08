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
	// 两值交换
	int a = 99;
	int b = 5;
	
	int temp = a;
	a = b;
	b = temp;
	
	printf("a=%d, b=%d \n", a, b);
	
	int x = 99;
	int y = 5;
	
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
	printf("x=%d, y=%d \n", x, y);

}

void two(){
	// 求出数组的最大值和最小值，即它们的索引。
	int arr[] = {21, 3, 56, 29, 86, 100, 38};
	
	int max = arr[0];
	int min = arr[0];
	int maxIndex = 0;
	int minIndex = 0;
	
	int length = sizeof(arr) / sizeof(arr[0]);
	
	for(int i = 1; i < length; i ++){
		if(max < arr[i]){
			max = arr[i];
			maxIndex = i;
		}
		
		if(min > arr[i]){
			min = arr[i];
			minIndex = i;
		}
	}
	printf("数组里的最小值是：%d , 索引是：%d \n 最大值是：%d , 索引是：%d \n", min, minIndex, max, maxIndex );
	
}

// 选择排序
void three(){
	// 数组的排序：
	int arr[] = {21, 3, 56, 29, 86, 100, 38};
	int length = sizeof(arr) / sizeof(arr[0]);
	
	int temp;
	int count = 0;
	
	for(int i = 0; i < length -1; i ++){
		// arr[i]
	
		for(int j = i + 1; j < length; j++){
			count++;
			if(arr[i] > arr[j]){
				//temp = arr[i];
				//arr[i] = arr[j];
				//arr[j] = temp;
				
				arr[i] = arr[i] ^ arr[j];
				arr[j] = arr[i] ^ arr[j];
				arr[i] = arr[i] ^ arr[j];
			}
		}
	}
	
	for(int i = 0; i <length; i ++){
		printf("%d \t", arr[i]);
	}
	printf("%d次。\n",count);
}
// 冒泡排序：
void four(){
	int arr[] = {21, 3, 56, 29, 86, 100, 38};
	int length = sizeof(arr) / sizeof(arr[0]);
	int count = 0;
	int temp;
	for(int i = 0; i < length -1; i++){
		for(int j = 0; j <length - 1 - i; j++){
			count++;
			if(arr[j] > arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
 	printf("%d次。\n",count);

	for(int i = 0; i <length; i ++){
		printf("%d \t", arr[i]);
	}
	printf("%d次。\n",count);
}
// 数组的反转
void five(){
	int arr[] = {11,22,33,44,55,66,77,88};
	int length = sizeof(arr) / sizeof(arr[0]);
	
	for(int i = 0; i < length / 2 ; i++){
		arr[i] = arr[i] ^ arr[length - 1 - i ];
		arr[length - 1 - i ] = arr[i] ^ arr[length - 1 - i ];
		arr[i] = arr[i] ^ arr[length - 1 - i ];
	}
	for(int i = 0; i <length; i ++){
		printf("%d \t", arr[i]);
	}
	printf("\n");
	
}

 
int main(int argc, char *argv[]) {

	five();
	
    return 0;
}
















































