/***************************************************
# File Name:    06-判断.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 03:19:42 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {
	// 流程控制-> 判断判断		
	int one = 100;
	int two = 3;

	char mark = '/'; 


	if( mark == '+' ){
		printf("加法运算的结果是：%d \n", one + two );
	
	}else if(mark == '-'){
		printf("减法运算的结果是：%d \n", one - two );
	
	}else if(mark == '*'){
		printf("乘法运算的结果是：%d \n", one * two );
	
	}else if(mark == '/'){	
		printf("除法运算的结果是：%d \n", one / two );

	}else {
		puts("对不起，运算符有误！");
	
	}

	puts("-----end-----");
    return 0;
}
