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
	int n;
	puts("请输入行数：");
	scanf("%d", &n);

	int arr[n][n];
	
	// 两条边的值都设置成1：
	for(int i = 0; i < n ; i++){
		arr[i][0] = 1;
		arr[i][i] = 1;
	}
	// 再填充其它位置的值：
	for(int i = 0 ; i < n ; i++){
		for(int j = 1; j < i; j++){
			arr[i][j] = arr[i-1][j-1] + arr[i-1][j];
		}
	}
	puts("---------------------------");
	
	for(int i = 0 ; i < n ; i++){
		// 输出空格：
		for(int k = 0; k < n -i -1; k++){
			printf(" ");
		}
		// 输出数字
		for(int j = 0; j <= i ; j++){
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
    return 0;
}























