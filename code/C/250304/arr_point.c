/***************************************************
# File Name:    realloc.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Tue 04 Mar 2025 02:28:12 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 
void test1()
{
	int a=10,b=20,c=30;
	int *p[3];
	p[0]=&a;
	p[1]=&b;
	p[2]=&c;
	
	for(int i=0;i<3;i++)
	{
		printf("%d\n",*p[i]);
	}
}

void test2()
{
	int arr[][3]={11,22,33,44,55,66,77};
	int *p[3];
	p[0]=arr[0];
	p[1]=arr[1];
	p[2]=arr[2];
	
	int onelength =sizeof(arr)/sizeof(arr[0]);
	int twolength =sizeof(arr[0])/sizeof(arr[0][0]);
	
	for(int i=0;i<onelength;i++)
	{
		for(int j=0;j<twolength;j++)
		{
			printf("[%d][%d]的位置的值是:%d \t",i,j,p[i][j]);
		}
		printf("\n");
	}
}

void tset3()
{
	char a[]="abc";
	char b[]="def";
	char c[]="ghi";
	char *p[3];
	p[0]=a;
	p[1]=b;
	p[2]=c;
	
	for(int i=0;i<3;i++)
	{
	//for(int j=0;j<3;j++)
		printf("%s\n",p[i]);
	}
}


int main(int argc, char *argv[]) {
	
	test1();
	test2();
	tset3();
	

    return 0;
}
