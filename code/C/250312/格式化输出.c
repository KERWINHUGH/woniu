/***************************************************
# File Name:    格式化输出.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Wed 12 Mar 2025 12:05:21 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>


#include <string.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {
	char name[20],buffer[100];
	printf("Enter your name: ");
	scanf("%s",name);
	snprintf(buffer,sizeof(buffer),"grep '%s' ./student.txt",name);
	system(buffer);
/*
FILE *fp = fopen("student.txt","a");
	if(fp == NULL){
		perror("打开文件失败");
		return -1;
	}
	
	int id,score;
	char name[20],buffer[100];
	printf("请输入学号：");
	scanf("%d",&id);
	printf("请输入姓名：");
	scanf("%s",name);
	printf("请输入成绩：");
	scanf("%d",&score);
	snprintf(buffer,sizeof(buffer),"%d\t%s \t%d\n",id,name,score);
	if(fputs(buffer,fp)==EOF){
		perror("写入文件失败");
		return -1;
	}
	fclose(fp);
*/
/*
	FILE *fp = fopen("student.txt","a");
	if(fp == NULL){
		perror("打开文件失败");
		return -1;
	}
	
	int id,score;
	char name[20];
	printf("请输入学号：");
	scanf("%d",&id);
	printf("请输入姓名：");
	scanf("%s",name);
	printf("请输入成绩：");
	scanf("%d",&score);
	if(fprintf(fp,"%d\t%s\t%d\n",id,name,score)<0){
		perror("写入文件失败");
		return -1;
	}
	fclose(fp);
*/
/*
	FILE *fp1 = fopen("student.txt","r");
	FILE *fp2 = fopen("new.tex","w");
	if((fp1==NULL)||(fp2==NULL)){
		perror("打开文件失败");
		return -1;
	}
	char buffer[100];
	
	while(fgets(buffer,sizeof(buffer),fp1)!=NULL){
		fputs(buffer,fp2);
	}
*/
    return 0;
}
