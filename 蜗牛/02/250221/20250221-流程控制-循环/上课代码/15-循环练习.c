/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// 输出100内的所有偶数,并统计偶数的个数
void one(){
	int count = 0;
	// 模型：循环 - 判断 - 统计
	for(int i = 1 ; i <= 100; i++){
		if(i % 2 == 0){
			count++;
			printf("偶数：%d \n", i);
		}	
	}
	printf("100以内偶数的个数是：%d \n", count );

}
// 键盘输入一个数，输出这1到这个数之间的偶数之和，奇数之和，并计算两和之间的差
void two(){
	puts("请输入一个数：");
	int num;
	scanf("%d", &num );
	
	int evenSum = 0; // 偶数和
	int oddSum = 0;  // 奇数和
	
	for(int a = 1; a <= num ; a++ ){
		if(a % 2 == 0){
			// 累加
			evenSum += a;   // evenSum = evenSum + a;
		}else {
			oddSum += a;
		}
	}
	printf("1~%d之间的偶数和是：%d , 奇数和是：%d ,它们之间的差是：%d \n", num, evenSum, oddSum, evenSum - oddSum );

}

 
int main(int argc, char *argv[]) {
	//one();
	two();
	
	puts("---end---");

    return 0;
}
