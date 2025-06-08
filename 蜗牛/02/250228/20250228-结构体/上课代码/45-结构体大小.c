/***************************************************
# File Name:    42-结构体使用.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 28 Feb 2025 10:53:32 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Test {
	int a;       // 4
	char b[3];   // 3 + 1
	char c;      // 2 + 2
	//short d;   // 2

} Test ;


typedef struct A {
	int  a;// 4
  	char  b;//1+3
  	double c;//8
  	char  d;//1+7
} A ;//24


typedef struct B {
  	double c;   // 8
	int  a;     // 4
  	char b;     // 1
  	char d;     // 1+2
} B ;  // 16 


int main(){
	
	int length = sizeof(B);

	printf("结构体大小：%d 个字节。\n", length);

	return 0;
}

































