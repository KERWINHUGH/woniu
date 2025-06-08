/***************************************************
# File Name:    class1.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 10:46:54 AM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	for(int j=1;j<=9;j++){
    for(int i=1;i<=j;i++)
	{
		printf("%d*%d=%d \t",i,j,i*j);
	}
	printf("\n");
	}
	return 0;
}
