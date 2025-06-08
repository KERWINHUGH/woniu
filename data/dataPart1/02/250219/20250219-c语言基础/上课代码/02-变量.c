/***************************************************
# File Name:    02-变量.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 10:39:24 AM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	// 用变量来存储数据：
	int age = 21; // = 是赋值符号	
	
	// 输出变量的值：
	puts("老张的年龄是：30" );
	printf("小张的年龄是：%d \n", age );
		

	// 用一个变量存名字：  
	char name[] = "张三";  // 双引号，引住的字符：字符串
	printf("新来的同事名是：%s \n", name );
	

	printf("新学生的姓名：%s ，年龄：%d \n", name, age);


    return 0;
}
