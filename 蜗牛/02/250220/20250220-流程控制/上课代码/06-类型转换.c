/***************************************************
# File Name:    03-逻辑运算符.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 06:33:57 PM PST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
int main(int argc, char *argv[]) {
	// c语言中，小数默认是double 
	//float f = 6.6f;
	
	// 6.6默认是double类型，赋值给一个float类型，这里有一个隐式转换。
	// 强转（ 大->小 ） 由大转小，可能会损失精度
	float f = (float)6.6;
	
	// 5.5f 是float类型的值，赋值给double类型，这里有一个隐式转换。
	double ff = 5.5f;

	printf("float: %f , double: %f \n", f, ff );
	
	puts("---------------------------------");
	
	// 00000000 00000000 10000000 00000000
	int a = 32768;  // 32768
	short b = (int)a;
	printf("short b: %d \n", b);
	
	
	puts("---------------------------------");
	float x = 7.0f;
	int y = x;
	
	printf("int y = %d \n", y);
	
	// 大转小（强转）， 可能损失精度
	// 小给大，直接赋值
	
	char ch = 'a';
	int z = ch;
	printf("int z = %d \n", ch);
	
	int w = 65;
	ch = w;
	printf("char ch = %d , %c \n", ch, ch);
	

    return 0;
}








