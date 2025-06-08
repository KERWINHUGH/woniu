/***************************************************
# File Name:    str.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:39:58 PM CST
****************************************************/

#include <stdio.h>
#include <string.h>
 
 void test1()
 {
 	char str[10][10];
 	int length=sizeof(str)/sizeof(str[0]);
 	
 	for(int i=0;i<length;i++)
 	{
 		 printf("请输入字符串str[%d] \n",i);
 		 scanf("%s",str[i]);
 	}
	 
	for(int i=0;i<length;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
	printf("\n");
 }
 
 void test2()
 {
 	
 	char str[10][10];
 	
 	int length=sizeof(str)/sizeof(str[0]);
 	
 	
 	
 	for(int i=0;i<length;i++)
 	{
 		 printf("请输入字符串str[%d] \n",i);
 		 scanf("%s",str[i]);
 	}
	 
	for(int i=0;i<length;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
	printf("\n");
 	
 	printf("------选择排序 ------\n");
 	char temp[length];
 	for(int i=0;i<length-1;i++)
 	{
 		for(int j=i+1;j<length;j++)
 		{
 			if(strcmp(str[i],str[j])>0)
 			{
 				strcpy(temp,str[i]);
 				strcpy(str[i],str[j]);
 				strcpy(str[j],temp);
 			}
 		}
 	}
 	
 	for(int i=0;i<length;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
	printf("\n");
	
 	printf("------冒泡排序 ------\n");
 	
 	for(int i=0;i<length-1;i++)
 	{
 		for(int j=0;j<length-1-i;j++)
 		{
 			if(strcmp(str[j],str[j+1])>0)
 			{
 				strcpy(temp,str[j]);
 				strcpy(str[j],str[j+1]);
 				strcpy(str[j+1],temp);
 			}
 		}
 	}
 	
 	for(int i=0;i<length;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
	printf("\n");
 }
 
void test3()
 {
 	
 	char str[10][10];
 	
 	int length=sizeof(str)/sizeof(str[0]);
 	
 	char temp[10][length];
 	
 	for(int i=0;i<length;i++)
 	{
 		 printf("请输入字符串str[%d] \n",i);
 		 scanf("%s",str[i]);
 	}
	 
	for(int i=0;i<length;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
	printf("\n");
 	
 	printf("------选择排序 ------\n");
 	
 	for(int i=0;i<length-1;i++)
 	{
 		for(int j=i+1;j<length;j++)
 		{
 			if(strcmp(str[i],str[j])>0)
 			{
 				strcpy(temp[j],str[i]);
 				strcpy(str[i],str[j]);
 				strcpy(str[j],temp[j]);
 			}
 		}
 	}
 	
 	for(int i=0;i<length;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
	printf("\n");
	
 	printf("------冒泡排序 ------\n");
 	
 	for(int i=0;i<length-1;i++)
 	{
 		for(int j=0;j<length-1-i;j++)
 		{
 			if(strcmp(str[j],str[j+1])>0)
 			{
 				strcpy(temp[j],str[j]);
 				strcpy(str[j],str[j+1]);
 				strcpy(str[j+1],temp[j]);
 			}
 		}
 	}
 	
 	for(int i=0;i<length;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
 	 printf("使用strcat拼接后：%s \n",strcat(str[0],str[length-1]));
	printf("\n");
 }
 
 
void test4()
{
 	char str[5][32]={0};
 	int oneLength=sizeof(str)/sizeof(str[0]);
 	int twoLength=sizeof(str)/sizeof(str[0]);
 	
 	for(int i=0;i<oneLength;i++)
 	{
 		 printf("请输入字符串str[%d] \n",i);
 		 scanf("%s",str[i]);
 	}
	 
	for(int i=0;i<oneLength;i++)
 	{
 		 printf("%s \t",str[i]);
 	}
 	printf("\n");
    int num=0;
 	//for(int i=0;i<oneLength;i++)
 	//{
 		//int sum=0;
 		
 		for(int j=0;j<twoLength;j++)
 		{
 			num += strlen(str[j]);
 			printf("%s\n",str[j]);
 			//sum+=num;
 		}
 	//}
 	printf("二维数组中共有%d个有效字符 \n",num);
 	
	printf("\n");
}


int main(int argc, char *argv[]) {

	//test1();
	//test2();
	//test3();
	test4();
	
    return 0;
}
