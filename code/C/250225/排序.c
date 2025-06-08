/***************************************************
# File Name:    class1.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 25 Feb 2025 11:18:26 AM CST
****************************************************/

#include <stdio.h>
 
void choice()//选择排序
{
	int a[]={21,3,56,29,86,100,38};
	
	int length = sizeof(a)/sizeof(a[0]);
	int temp;

	//选择排序
	for(int i=0;i<length-1;i++)//第一次循环时，第一个元素与后续每个元素进行比较，所以需要比较length-1次
	{
		for(int j=i+1;j<length;j++)//第二次开始时，因为最小值已经放到最前面，所以循环开始条件变为从i+1开始，循环会执行length-（i+1）次
		{
			if(a[i]>a[j])//从a[i=0]开始，与后面（a[j]=a[i+1]）每个元素作比较，如果a[i=0]大于后面的值，则交换两个元素的值
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	for(int i=0;i<length;i++)
	{
		printf("%d \t",a[i]);
	}
	printf("选择排序 \n");
	
}

void pao()//冒泡排序
{
	int a[]={21,3,56,29,86,100,38};
	
	int length = sizeof(a)/sizeof(a[0]);
	int temp;
	
	//冒泡排序
	for(int i=0;i<length-1;i++) //第一层循环执行length-1次比较，因为是两两作比较，即第一层只需要比较length-1次
	{
	    //后续每层循环都执行lenth-1-i次循环，因为第一次已经找到最大值，将其放到最后，后面不需要再做比较这个最大值，即后面每次循环都会减少i次
		for(int j=0;j<length-1-i;j++)
		{
			if(a[j]>a[j+1])//如果前者大于后者，交换两个元素的值
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	for(int i=0;i<length;i++)
	{
		printf("%d \t",a[i]);
	}
	printf("冒泡排序  \n");
	
}

void turn()
{
	//数组反转
	int a[]={11,22,33,44,55,66,77,88};
	int length = sizeof(a)/sizeof(a[0]);
	int temp;
	
	for(int i=0;i<length/2;i++)
	{
	    //数组首尾元素进行交换，其次是a[i]与a[length-1-i]进行交换
		temp=a[i];
		a[i]=a[length-1-i];
		a[length-1-i]=temp;
	}
	
	for(int i=0;i<length;i++)
	{
		printf("%d \t",a[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {

	choice();
	pao();
	turn();
			//if(a[i]>max)
			//{
				//max=a[i];
				//maxIndex =i;
			//}
			//if(a[i]<min)
			//{
			//	min=a[i];
			//	minIndex =i;
			//}
	

	//printf("最大值是%d，最小值是%d 最大值索引%d,最小值索引%d \n",max,min,maxIndex,minIndex);

	
    return 0;
}
