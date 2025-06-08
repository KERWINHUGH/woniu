/***************************************************
# File Name:    23-数组练习.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 04:50:44 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

/*
从键盘输入5个学生的成绩
- 如果遇到大于100或者小于 0 的成绩需要提示输入错误重新输入
- 之后计算5个学生的总成绩和平均成绩
*/

#define SIZE 5
// 关于数组的初始化方式：
void one(){
	/*
	// 当使用变量做为长度时，不能直接初始化
	int length = 5;
	int arr[length];
	puts("-----手动初始化-----");
	for(int i = 0; i <length; i++){
		arr[i] = 0;
	}
	*/
	
	// 定义宏（全局变量）
	int arr[SIZE] = {0};
	
	puts("-----遍历-----");
	for(int i = 0; i < SIZE; i++){
		printf("%d\n",arr[i]);
	}
}

void two(){
	int length = 5;
	int scores[length];
	
	//int temp;
	for(int i = 0; i < length; i++){
		printf("请输入%d号位置，学生的分数\n", i);
		scanf(" %d", &scores[i]);
		
		if(scores[i] > 100 || scores[i] <0){
			printf("对不起，%d 不是正常的分数，请重输！\n", scores[i] );
			i--;
		}
	}
	// 分数输入完毕，我们应该遍历所有的分数：
	for(int i = 0; i < length; i ++){
		if(i == length - 1){
			printf("%d ", scores[i]);
		}else {
			printf("%d , ", scores[i]);
		}
	}
	puts("------计算总分数和平均分数------");
	int sum = 0;
	for(int i = 0; i < length; i ++){
		sum += scores[i];
	}
	printf("总分数是：%d , 平均成绩是：%d \n", sum, sum / length );
	// 请统计，及格的人数。
	
	printf("\n");
}

void three(){
	puts("请输入一个数：");
	int n;
	
	scanf("%d", &n );
	
	int arr[n];
	
	for(int i = 0; i < n ; i++){
		if(i == 0 || i == 1 ){
			arr[i] = 1;
		}else {
			arr[i] = arr[i-1] + arr[i-2];
		}
	}
	puts("-------- 遍历数列 ---------");
	for(int i = 0; i < n ; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n");
	
	printf("第%d位数列的值是：%d \n", n, arr[n-1]);
}
 
int main(int argc, char *argv[]) {
	
	three();
	
    return 0;
}














