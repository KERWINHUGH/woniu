/***************************************************
# File Name:    03-逻辑运算符.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 06:33:57 PM PST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
int main(int argc, char *argv[]) {
	char gender = 'M';
	
	if(gender == 'M'){
		printf("是男生\n");
		
	}else if(gender == 'F'){
		printf("是女生\n");
	
	}
	puts("------使用分支语句：求两数中的最大值-------");
	
	int a, b;
	puts("请输入两个整数：");
	scanf("%d %d" ,&a, &b );
	
	int max ;
	if(a > b){
		max = a;
	}else {
		max = b;
	}
	printf("%d 和 %d 之间，最大值是：%d \n", a, b, max);
	

	puts("------使用分支语句：判断一个数是正数还是负数-------");
	if(a >= 0){
		printf("%d是正数\n", a);
	}else {
		printf("%d是负数\n", a);
	}
	
	puts("------使用分支语句：由键输入一个数，判断它是偶数还是奇数-------");
	if(b % 2 == 0){
		printf("%d是偶数\n", b);
	}else {
		printf("%d是奇数\n", b);
	}

	puts("------end-------");
    return 0;
}








