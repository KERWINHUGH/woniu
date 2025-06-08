/***************************************************
# File Name:    05-数据类型.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 02:12:41 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
int main(int argc, char *argv[]) {
	puts("--------------整数----------------------");
	
	char a = 'a';
	printf("字符：%c \n", a);
	printf("字符(数字)：%d \n", a + 10);	

	short b = 100;
	printf("短整型：%d \n", b);
	// c语言中，整数默认是int类型的
	int c = 1000;
	printf("整型：%d \n", c);
	
	long d = 1000L;
	printf("长整型：%ld \n", d);

	puts("--------------浮点数（小数）----------------------");
	// c 语言中，小数默认是double类型的
	float f = 5.5f;  // 4个字节：
	printf("浮点数：%f \n", f);

	double ff = 8.888;  // 8个字节
	printf("浮点数：%.2f \n", ff);

	puts("--------------布尔--------------------");

	_Bool boo = 1;
	printf("布尔型：%d \n", boo	);

	bool t = true;  // false
	printf("布尔型2：%d \n", t);

	puts("------------ 四则运算 -----------------");
	int x = 10;
	int y = 5;

	int result = x + y;
	printf("加法结果是：%d \n", result);

	result = x - y;
	printf("减法结果是：%d \n", result);

	result = x * y;
	printf("乘法结果是：%d \n", result);

	result = x / y;
	printf("除法结果是：%d \n", result);

	puts("---求余数---");
	int z = 3;
	result = x % z ;
	printf("求余的结果是：%d \n", result);








    return 0;
}
