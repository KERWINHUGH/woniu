/***************************************************
# File Name:    hmwk.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Tue 04 Mar 2025 05:25:07 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
** 定义一个字符串数组(指针数组)，记录字母a出现的总次数并输出
** char *words[4]={"aabbcc","admin","aaahhh","halo"},
*/
int Statistics(char *arr[],int length,int length2)
{
	//int i=0;
	
	int count =0;
	
	//while(arr[i][j]!='\0')
	//{
		for(int i=0;i<length;i++)
		{
		 int j=0;
			//for(int j=0;j<length2;j++)
			//{
			while(arr[i][j]!='\0')
			{
				
				if(arr[i][j]=='a')	
				{
					count++;
				}	
				//printf("arr[%d][%d]:%c \n",i,j,arr[i][j]);	
				j++;
			}	
			
		}
		//printf("%d \n",j);
		//j++;
	//}
	/*
	int i=0;
	int j=0;
	int count=0;
	while(arr[i][j]!='\0')
	{
			if(arr[i][j]=='a')	
			{
				count++;
			}	
		i++;
		j++;
	}
	
	return count;
	*/
	return count;
}
/*
编写一个程序，利用malloc来生成一个长度为10的数组，用户输入一个数组的值 ，然后使用指针找出数组中的最大值和最小值。
*/
int* findMaxAndMin()
{
	
	int *arr=malloc(sizeof(int)*10);
	memset(arr,0,sizeof(int)*10);
	
	for(int i=0;i<10;i++)
	{
		printf("请输入arr[%d]:",i);
		scanf("%d",&arr[i]);
	}
	for(int i=0;i<10;i++)
	{
		printf("%d\t",arr[i]);
	}
	int max=arr[0],min=arr[0];
	
	int temp[2]={0};
	for(int i=0;i<10;i++)
	{
		if(max<arr[i])
		{
			max=arr[i];
			
		}else if(min>arr[i])
		{
			min=arr[i];
		}
	}
	//printf("min:%d\t max:%d:",min,max);
	temp[0]=min;
	temp[1]=max;
	
	int *p=temp;
	
	return p;
}

/*
编写一个函数模拟strcat函数功能:完成两个字符串的合并，用指针实现。realloc
*/
char* my_strcat(char *one, char *two){
	// 分配内存存每一个字符串
	int length = strlen(one);
	
	char *p1 = malloc( length );
	memset( p1, 0 , length );

	for(int i = 0; i < length ; i++){
		*(p1+i) =  *(one+i);
	}
	
	// 第二个字符串处理：
	int newLength = length + strlen(two) + 1;
	char *temp = realloc( p1, newLength);
	
	// 对新分配的内存进行初始化操作：  （ 这里加了1，我们后面就不用手动补 '\0' ）
	memset( temp + length  , 0 , strlen(two) + 1 );
	
	// 把第二个字符串的值，给到新的内存里：
	for(int i = 0; i < strlen(two); i++){
	  *(temp + length + i) = *(two + i );
	}
	// 最后，补上结束符(前面处理过了，就不用手动补)：
	return temp;
}

void myFree(void *p){
	free(p);
}

int main(int argc, char *argv[]) {

	/*//hmwk1:记录字母a出现的总次数并输出
	char *words[4]={"aabbcc","admin","aaahhh","halo"};
	int length=sizeof(words)/sizeof(words[0]);
	int length2=sizeof(*words[0])/sizeof(words[0][0]);
	
	printf("%d \n",length);
	
	int count =Statistics(words,length,length2);
	printf("count:%d \n",count);
	*/
	/*
	//hmwk2:记录字母a出现的总次数并输出
	//int arr[2]={0};
	int *p=findMaxAndMin();
	//p[0]=arr[0];
	//p[1]=arr[1];
	printf("最小值是：%d\n最大值是：%d\n",p[0],p[1]);
	*/
	//hmwk3:模拟strcat函数功能:完成两个字符串的合并
	char a[] = "hello,";
	char b[] = "world!";
	char *p = my_strcat(a,b);
	printf("%s \n", p);
	
	myFree(p);
	
    return 0;
}
