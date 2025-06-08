/***************************************************
# File Name:    pointer.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Mon 03 Mar 2025 11:50:36 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void change(int *p)
{
	//int a=20;
	*p=25;
	printf("调用后*p的值：%d\n",*p);
	//printf("调用后a的地址：%p\n",&a);
	printf("调用后p的值：%p\n",p);
	
}
 
int main(int argc, char *argv[]) {

	int a=20;
	int *p=&a;
	printf("调用前*p的值：%d\n",*p);
	printf("调用前a的地址：%p\n",&a);
	printf("调用前p的值：%p\n",p);
	change(p);
	
    return 0;
}
