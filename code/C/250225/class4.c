/***************************************************
# File Name:    class3.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 25 Feb 2025 03:08:27 PM CST
****************************************************/

#include <stdio.h>

void arr2()
{
	 int arr[5][4]={0};
	 int oneLength=sizeof(arr)/sizeof(arr[0]);
	 int twoLength=sizeof(arr[0])/sizeof(arr[0][0]);
	 
	 for(int i=0;i<oneLength;i++)
	 {
	 	for(int j=0;j<twoLength;j++)
	 	{
	 		arr[i][j]=100+i*10+j;
	 	}
	 }
	 
	 for(int i=0;i<oneLength;i++)
	 {
	 	for(int j=0;j<twoLength;j++)
	 	{
	 		printf("%d\t",arr[i][j]);
	 	}
	 	printf("\n");
	 }
	
}

 
int main(int argc, char *argv[]) {

	
	arr2();
    return 0;
}
