/***************************************************
# File Name:    03-逻辑运算符.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 06:33:57 PM PST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
int main(int argc, char *argv[]) {
	
	int one = 10;
	int two = 5;
	
	
	int result;

		puts("请输入运算符：");
		char mark;
		scanf(" %c", &mark);
		switch(mark){

			case '+':
				// 这样写，是在case里设置了一个作用域 其它的case 无法访问变量x;
				result = one + two;
				printf("加法运算结果是：%d \n", result);

				int x = 9999;
				printf("x的值是：%d \n", x);
				
				break;
				
			case '-':
				result = one - two;
				printf("减法运算结果是：%d \n", result);
				
				printf("x的值是：%d \n", x);
				
				break;

			case '*':
				result = one * two;
				printf("乘法运算结果是：%d \n", result);
				break;
				
			case '/':
				result = one / two;
				printf("除法运算结果是：%d \n", result);
				break;

			default:
				printf("对不起，运算符有误！\n");
				break;
				
		}

	
	
	
	puts("------end-------");
    return 0;
}
















