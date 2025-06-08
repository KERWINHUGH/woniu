/***************************************************
# File Name:    07-运算符.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 04:36:55 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {
	// 赋值运算：
	int a = 10;

	//a += 5;		// a = a + 5;
	
	//a -= 6;       // a = a - 6;
	
	//a *= 3;	    // a = a * 3;

	//a /= 3;	    // a = a / 2;

	//a %= 3 ;	

	//a++;           // 自增  
	//--a;           // 自减	

	
	//printf("%d \n", ++a);     // 先运算，再执行
	printf("%d \n", a++);       // 先执行，再运算




    return 0;
}
