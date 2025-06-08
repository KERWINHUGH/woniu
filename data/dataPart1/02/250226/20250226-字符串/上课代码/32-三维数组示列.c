/***************************************************
# File Name:    31-字符串.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:04:09 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


 
int main(int argc, char *argv[]) {
	
	int arr[4][3][3] = {0};
	
	int oneLength = sizeof(arr) / sizeof(arr[0]);
	int twoLength = sizeof(arr[0]) / sizeof(arr[0][0]);
	int threeLength = sizeof(arr[0][0]) / sizeof(arr[0][0][0]);
	
	for(int i = 0; i < oneLength; i++){
		for(int j = 0; j < twoLength; j++){
			for(int k = 0; k < threeLength; k++){
				arr[i][j][k] = 1000 + i * 100 + j * 10 + k;
			}
		}
	}
	puts("----遍历-----");
	for(int i = 0; i < oneLength; i++){
		for(int j = 0; j < twoLength; j++){
			for(int k = 0; k < threeLength; k++){
				printf("%d\t", arr[i][j][k] );
			}
			printf("\n");
		}
		puts("======================================");
	}
	
    return 0;
}























