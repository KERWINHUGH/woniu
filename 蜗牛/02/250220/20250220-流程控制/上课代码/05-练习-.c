/***************************************************
# File Name:    03-逻辑运算符.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 06:33:57 PM PST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
int main(int argc, char *argv[]) {
/*
	int time;
	puts("请输入时间：");
	scanf("%d", &time);
	
	char ch = time < 12 ? 'A' : 'P';
	
	printf("当前时间==>  %c : %d \n", ch, time);
*/
	// -----------------------------------------------
	// 如果要进行两值交换，应该如何实现？
	int a = 5;
	int b = 8;
		
	int temp = a;   // temp = 5;
	a = b;          // a = 8;
	b = temp;       // b = 5;
		
	printf("a:%d , b:%d \n", a, b);
	
	puts("------------- 不用第三方变量，使用异或实现 -------------------");
	int x = 5; // 0101
	int y = 8; // 1000
	
	x = x ^ y;   // 1101
	y = x ^ y;   // 0101
	x = x ^ y;   // 1000
	
	printf("x:%d , y:%d \n", x, y);	

    return 0;
}








