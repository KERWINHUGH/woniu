/***************************************************
# File Name:    test1.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Thu 27 Feb 2025 10:56:23 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
 
 
 
void xTOy(int x,int y,int z);
int test1(int a[],int length);
int test2(int num);
bool test3(int a[],int length,int n);
bool test4(int num);
int test5(int a,int b);

int main(int argc, char *argv[]) {
	
	
	int a[3]={1,2,3};
	int length =sizeof(a)/sizeof(a[0]);
	
	//xTOy(100,108,3);
	
	//测试1的内容
	//int aver = test1(a,length);
	//printf("test1:平均数是:%d \n",aver);
	
	
	//测试2的内容
	//int n = test2(50);
	//printf("test2:radom:%d \n",n);
	
	//测试3的内容
	//puts("请输入一个数字");
	//int num;
	//scanf("%d",&num);
	//bool f = test3(a,length,num);
	//if(f)
	//{
	//	printf("test3:%d在数组中 \n",num);
	//}else
	//{
	//	printf("test3:%d不在数组中 \n",num);
	//}
	
	//测试4的内容
	//int number=100;
	//bool f1 = test4(number);
	//if(f1)
	//{
	//	printf("test4:%d是一个质数 \n",number);
	//}else
	//{
	//	printf("test4:%d不是一个质数 \n",number);
	//}
	
	int b=5;
	int c=6;
	printf("交换前b的值是%d,c的值是%d \n",b,c);
	int d=test5(b,c);
	printf("交换后b的值是%d,c的值是%d \n",b,c);
	printf("d的值是%d \n",d);
    return 0;
}

int test1(int a[],int length)
{
	int sum=0;
	int aver=0;
	for(int i=0;i<length;i++)
	{
		sum+=a[i];
	}
	aver=sum/length;
	return aver;
	
}

int test2(int num)
{
	srand(time(NULL));
	return (rand()%num)+1;
	
}

bool test3(int a[],int length,int n)
{
	for(int i=0;i<length;i++)
	{
		if(a[i]==n)
		return true;
	}
	return false;
}

bool test4(int num)
{
	for(int i =2;i<num/2;i++)
	{
		if(num%i==0)
		{
			return false;
		}
	}
	return true;
}

int test5(int b,int c)
{
	int temp;
	temp=b;
	b=c;
	c=temp;
	
	return b,c;
}

void xTOy(int x,int y,int z)
{
	for(int i =x;i<=y;i+=z)
	{
		printf("%d \n",i);
	}
}
