/***************************************************
# File Name:    hmwk_2.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 08:21:06 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	float a;
	float b;
	
	puts("请输入第一个数");
	scanf("%f",&a);

	puts("请输入第二个数");
	scanf("%f",&b);

	printf("两数之和为：%.2f\n",a+b);

	printf("两数之差为：%.2f\n",a-b);

	printf("两数之积为：%.2f\n",a*b);
	
	printf("两数的商为：%.2f\n",a/b);
	
	//printf("两数的余数为：%.2f\n",a%b);

    return 0;
}
