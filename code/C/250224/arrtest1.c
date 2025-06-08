/***************************************************
# File Name:    arrtest1.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 02:34:28 PM CST
****************************************************/

#include <stdio.h>

void arr1()
{	
		int arr[10] = {5};
	    int length= sizeof (arr)/sizeof(arr[0]);
		for(int i=length-1;i>=0;i--)
		{
			arr[i]=(i+1)*5;
			//arr[0]=5;
		}
		for(int i=length-1;i>=0;i--)
		{
			printf("%d \n",arr[i]);
		}
}

void arr2()
{
		int arr[10] = {5};
	    int length= sizeof (arr)/sizeof(arr[0]);
		for(int i=0;i<length;i++)
		{
			arr[i]=(i+1)*5;
			//arr[0]=5;
		}
		for(int i=0;i<length;i++)
		{
			printf("%d \n",arr[i]);
		}
}

int main(int argc, char *argv[]) {

		arr2();
		puts("-----------------------------------");
		arr1();
		int score=0;
		

    return 0;
}
