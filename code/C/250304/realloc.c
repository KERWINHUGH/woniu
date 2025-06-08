/***************************************************
# File Name:    realloc.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Tue 04 Mar 2025 02:28:12 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 
char *my_strcat(char *target,char *Primary)
{
	int length1 =strlen(target);
	int length2 =strlen(Primary);
	int length=length1+length2+1;
		
	char *p=malloc(length);
	memset(p,0,length);
	
	for(int i=0;i<length1;i++)
	{
			p[i]=target[i];
	}
	for(int i=length1;i<length-1;i++)
	{	
			p[i+1]=Primary[i];	
	}
	return p;
	/*
		for(int i=1;i<length;i++)
	{
		printf("%d",p[i]);
		if(i==length-1)
		{
			p[i]='\0';
		}	
	}*/
}
 

char *my_strcat1(char *target,char *Primary)
{
	int length =strlen(target);
	
		
	char *p1=malloc(length);
	memset(p1,0,length);
	
	for(int i=0;i<length;i++)
	{
		*(p1+i)=*(target+i);
	}
	
	int newlength =length+strlen(Primary)+1;
	//int length=length1+length2+1;
	
	char *temp=realloc(p1,newlength);
	
	memset(temp+length,0,strlen(Primary)+1);
	
	for(int i=0;i<strlen(Primary);i++)
	{
			*(temp+i+length+1)=*(target+i);
	}
	/*
	for(int i=length1;i<length-1;i++)
	{	
			p[i+1]=Primary[i];	
	}
	*/
	return temp;
	/*
		for(int i=1;i<length;i++)
	{
		printf("%d",p[i]);
		if(i==length-1)
		{
			p[i]='\0';
		}	
	}*/
}

void my_free(char *p)
{
	free(p);
}
int main(int argc, char *argv[]) {
	
	char s1[]="hello";
	char s2[]="world";
	int length1 =strlen(s1);
	int length2 =strlen(s2);
	int length=length1+length2+1;
	
	char *s=my_strcat1(s1,s2);
	printf("%s\n",s);
	my_free(s);
	

    return 0;
}
