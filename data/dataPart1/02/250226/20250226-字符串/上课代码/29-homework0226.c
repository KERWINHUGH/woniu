/***************************************************
# File Name:    29-homework0226.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 10:40:45 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

void one(){
	int oneLength, twoLength;
	puts("请输入数组的第一维的长度：");
	scanf("%d", &oneLength);
	puts("请输入数组的第二维的长度：");
	scanf(" %d", &twoLength);

	int arr[oneLength][twoLength];
	
	//int temp;
	for(int i = 0; i < oneLength; i ++){
		for(int j = 0; j < twoLength; j++){
			printf("请输入[%d][%d]号位置的值：",i , j );
			scanf("%d", &arr[i][j]);
			//scanf("%d", &temp);
			//arr[i][j] =  temp;
		}
	}
	puts("--------- 遍历 ------------");
	for(int i = 0; i < oneLength; i ++){
		for(int j = 0; j < twoLength; j++){
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	puts("--------- 计算平均值 ------------");
	int avgArr[oneLength];
	
	for(int i = 0; i < oneLength; i ++){
		// 先计算第二维数组的总和
		int tempSum = 0;
		for(int j = 0; j < twoLength; j++){
			tempSum += arr[i][j];
		}
		// 循环结束，再算出平均数：
		avgArr[i] = tempSum / twoLength;
	}
	puts("--------- 遍历平均值 ------------");
	for(int i = 0; i < oneLength; i ++){
		printf("%d号位置的平均值是：%d \n", i, avgArr[i]);
	}

}

 
int main(int argc, char *argv[]) {
	one();



    return 0;
}
