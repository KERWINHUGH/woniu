/***************************************************
# File Name:    class3.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 04:28:19 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	int score[5]={0};
	int length=sizeof(score)/sizeof(score[0]);
	int scores = 0;
	for(int i=0;i<length;i++)
	{
		printf("请输入学生的分数: \n");
		scanf("%d",&score[i]);
		if(score[i]>100||score[i]<0)
		{
			puts("输入错误，请重新输入！");
			i--;
		}
	}
	for(int i=0;i<length;i++)
	{
		scores += score[i];
	}
	printf("%d个学生的总分为%d,平均分为%d \n",length,scores,scores/length);

	for(int i=0;i<length;i++)
	{
		if(i==length-1)
		{
			printf("%d \n",score[i]);
		}else
		{
			printf("%d ,\n",score[i]);
		}
	}
    return 0;
}
