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

	double arr[6]={11,22,33,44,55,66};
	double *p=arr;
	int length =sizeof(arr)/sizeof(arr[0]);
	
	for(int i=0;i<length;i++)
	{
		printf("%lf \t",p[i]);//使用索引
	}
	printf("\n");
	puts("---------------------------");
	for(int i=0;i<length;i++)
	{
		printf("%lf \t",*(p+i));//使用指针,不改变指针指向的位置	
	}
	printf("\n");
	
	puts("---------------------------");
	for(int i=0;i<length;i++,p++)
	{
		printf("%lf \t",*p);//使用指针解引用	
	}
	printf("\n");
	
	
	double *strat_p=&arr[0];
	
	double *end_p=&arr[length-1];
	
	int length1=end_p-strat_p;
	puts("---------------------------");
	
	for(int i=0;i<length1+1;i++)
	{
		printf("%lf \t",*(strat_p+i));//使用指针,不改变指针指向的位置		
	}
	printf("\n");
	
    return 0;
}
