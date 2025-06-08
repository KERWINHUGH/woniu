/***************************************************
# File Name:    函数指针.c
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月16日 星期五 10时49分01秒
u****************************************************/

#include <stdio.h>
 
int add(int a,int b){
	return a+b;
}

int sub(int a,int b){
	return a-b;
}

typedef struct Ctest{
	int (*a)(int ,int);
	int (*b)(int ,int);
}Ctest;

int main(int argc, char *argv[]) {
	
	Ctest t = {0};

	t.a = add;
	int c = t.a(1,2);
	printf("a = %d\n",c);

	t.b = sub;
	int d =t.b(2,1);
	printf("b = %d\n",d);
    return 0;
}
