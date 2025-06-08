/***************************************************
# File Name:    02-变量.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 10:39:24 AM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	// 用变量来存储数据：
	
	// 申明一个变量
	// 类型   变量名  =   值
	int num = 21; // = 是赋值符号	
	printf("%d \n", num );

	num = 30; // 这里是变更的重新赋值
	printf("%d \n", num );


	//同一个作用域里，不能出现两个同名的变量
	//char num = 'a';
	//printf("%d \n", num );

	// 同时申明了三个变量：没有赋值（没有初始化）
	int a,b,c;
	int _a;
	int A,B,C;


	int student_age;
	int student_age2;

	int studentAge = 22;



	return 0;
}
