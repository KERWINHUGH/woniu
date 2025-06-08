/***************************************************
# File Name:    pra5.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 02:47:58 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	int x , y;
	puts("请输入第一个数");
	scanf("%d",&x);
	puts("请输入第二个数");
	scanf("%d",&y);
	int z = 1;

	for(int i=0;i<y;i++)
	{
		z=x*z;
	}
	printf("%d的%d次方是%d \n",x,y,z);


    return 0;
}
