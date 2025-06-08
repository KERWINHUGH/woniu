/***************************************************
# File Name:    pra2.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 02:12:09 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	int num,ge,shi,bai;

	puts("请输入一个三位数");
 
	scanf("%d",&num);
	
	ge = num % 10/1;
	shi = num%100/10;
	bai = num%1000/100;
	
	if(num<0 && num>1000)
	{
		puts("输入数字超出范围");
	}else if(ge*ge*ge+shi*shi*shi+bai*bai*bai == num)
			{
				printf("%d是一个水仙花数 \n",num);
			}else 
			    {	
				    printf("%d不是一个水仙花数 \n",num);
			    }

    return 0;
}
