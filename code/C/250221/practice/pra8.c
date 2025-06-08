/***************************************************
# File Name:    pra8.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Sat 22 Feb 2025 11:23:03 AM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {
	int num;
	puts("请输入一个数");
	scanf("%d",&num);
 
	if(num<=1)
	{
		puts("请输入一个大于1的数");
	}else if(num == 2)
		{
			printf("%d是一个质数 \n",num);
		}
    for(int i=3;i*i<=num;i+=2)
	{
		if(num%i==0)
		{
			printf("%d不是一个质数 \n",num);
			return 0;
		}else
		{
			printf("%d是一个质数 \n",num);
			return 0;
		}
	}

    return 0;
}
