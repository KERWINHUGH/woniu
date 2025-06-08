/***************************************************
# File Name:    hmwk.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Thu 27 Feb 2025 10:21:37 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
int test1(int x,int y);
void test2(int x,int y,int z);
void test3(char arr[][32],int olength,int tlength);
int test4(int num);
void test5();
void test6();

int main(int argc, char *argv[]) {

	//puts("请输入底数");
	//int x;
	//scanf("%d",&x);
	//puts("请输入指数");
	//int y;
	//scanf("%d",&y);
	//int sum =test1(x,y);
	//printf("%d的%d次方是%d \n",x,y,sum);


	//puts("请输入长");
	//int x;
	//scanf("%d",&x);
	//puts("请输入宽");
	//int y;
	//scanf("%d",&y);
	//puts("请输入高");
	//int z;
	//scanf("%d",&z);	
	//test2(x,y,z);

	//char str[][32] ={"jack","lili","mike","jerry","rose"};
	//int olength = sizeof(str)/sizeof(str[0]);
	//int tlength = sizeof(str[0])/sizeof(str[0][0]);
	//test3(str,olength,tlength);

	//puts("请输入一个数");
	//int num;
	//scanf("%d",&num);
	//int count =test4(num);
	//printf("输入的数字长度是%d \n",count);
	//int count =test4(num);
	
	//test5();
	test6();
	
    return 0;
}

int test1(int x,int y)
{
	int sum=1;
	for(int i=0;i<y;i++)
	{
		sum*=x;
	}
	return sum;
}
void test2(int x,int y,int z)
{
	printf("长方体的体积为%d \n",x*y*z);
	printf("长方体的三个面分别为%d,%d,%d \n",x*y,x*z,y*z);
	
}
void test3(char arr[][32],int olength,int tlength)
{
	int count=0;
	printf("一共有%d个人 \n",olength);
	printf("第5个人是%s \n",arr[5-1]);
	puts("姓名以i开头的有：");
	for(int i=0;i<olength;i++)
	{
		if(arr[i][0]=='i')
		{
			printf("%s \t",arr[i]);
		}
	}
	for(int i=0;i<olength;i++)
	{
		if(arr[i][0]=='j')
		{
			count++;	
		}
	}
	printf("姓名以j开头的有：%d 个 \n",count);
}

int test4(int num)
{
	int count=0;
	for(int i=1;i<num;i*=10)
	{
		if(num/i==0)
		{	
			count++;
			break;
		}else
		{
			count++;
		}
	}
	return count;
}
void test5()
{
	int num;
	puts("请输入一个数");
	scanf("%d",&num);
	int count=test4(num);
	//double temp=test1(10,count-1);
	
	int arr[count];
	int x=10;
	int y=1;
	for(int i=count-1;i>=0;i++)
	{
		//for(int j=0;j<count;j++)
		//{
			arr[i]=num%x/y;
			x*=10;
			y*=10;
		//}

	}
	for(int j=0;j<count;j++)
	{
		if(j!=count-1)
		{
			printf("%d**** \t",arr[j]);
		}else
		{
			printf("%d \t",arr[j]);
	    }
			
	}
    printf("\n");
	//return arr;
}
void test6()
{
	char number[32];
	puts("请输入数字：");
	scanf("%s",number);
	int length = strlen(number);
	for(int i=0;i<length;i++)
	{
		if(i!=length-1)
		{
			printf("%c***",number[i]);
		}else
		{
			printf("%c",number[i]);
		}
	
	}
}
