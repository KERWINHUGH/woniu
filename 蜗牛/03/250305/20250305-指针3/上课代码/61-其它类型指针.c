/***************************************************
# File Name:    61-其它类型指针.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 05 Mar 2025 02:03:56 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

 
int main(int argc, char *argv[]) {

	int a = 100;
	a+= 5;
	printf("a=%d \n", a);
	printf("a的地址是：%p \n", &a);
	
	// const修饰的变量是常量，常量不可变   "hello" 也是常量 ：
	const int b = 99;
	//b = 9999;
	printf("b=%d \n", b);
	
	
	const int *p = &a;
	//*p = 200;  常量指针，指向的数据，不能修改。
	
	printf("指针p指向的地址是：%p \n", p);
	
	puts("---------------------------------");	
	int num = 88;
	p = &num;	
	printf("指针p指向的地址是：%p \n", p);
	
	
	puts("---------------------------------");	

	char str[] = "hello";
	char str2[] = "hello";
	
	printf("str的地址是：%p \n", &str);
	printf("str2的地址是：%p \n", &str2);
	
	char *sp = "hello";
	printf("sp指向的地址是：%p , 值是：%s \n", sp , sp);

	char *sp2 = "hello";
	printf("sp2指向的地址是：%p ,值是：%s \n", sp2, sp2 );
	
	//puts("--------------修改sp的指向值-------------------");	
	//sp = "world!";
	
	puts("--------------通过解引用修改sp的指向地址的值-------------------");	
	//*sp = 'X';  // 解引用不能使用，会报错
	
	printf("sp指向的地址是：%p ,  值是：%c \n", sp , *sp);
	printf("sp2指向的地址是：%p , 值是：%c \n", sp2 , *sp2);
	
	
	int *x;

    return 0;
}


















