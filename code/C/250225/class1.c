/***************************************************
# File Name:    class1.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 25 Feb 2025 11:18:26 AM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	int a[]={21,3,56,29,86,100,38};
	
	int length = sizeof(a)/sizeof(a[0]);
	int temp;
	
	int max=a[0];
	int min=a[0];
	int maxIndex =0;
	int minIndex =0;
	
	for(int i=0;i<length;i++)
	{
			if(a[i]>max)
			{
				max=a[i];
				maxIndex =i;
			}
			if(a[i]<min)
			{
				min=a[i];
				minIndex =i;
			}
	}

	printf("最大值是%d，最小值是%d 最大值索引%d,最小值索引%d \n",max,min,maxIndex,minIndex);

    return 0;
}
