/***************************************************
# File Name:    pra2.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 02:12:09 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	int ge,shi,bai;

//	puts("请输入一个三位数");
 
//	scanf("%d",&num);
	
	
	for( int i = 100 ; i<=999 ;i++)
	{
		ge = i % 10/1;
		shi = i % 100/10;
		bai = i % 1000/100;
		
		if(ge*ge*ge+shi*shi*shi+bai*bai*bai == i)
		{
			printf("%d \n",i);
		}
	}

    return 0;
}
