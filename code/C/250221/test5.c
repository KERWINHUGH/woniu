/***************************************************
# File Name:    test5.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 03:52:54 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {
	
	int num;
	int add = 0;

	do
	{
		scanf(" %d",&num);
		if(num%2 == 0)
		{
			add=add+num;
		}
	}while(num != 0);
	printf("输入的数字里偶数之和是%d \n",add);
    return 0;
}
