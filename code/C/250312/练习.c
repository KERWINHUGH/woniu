/***************************************************
# File Name:    IO.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Wed 12 Mar 2025 09:29:46 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 /*
文件students.txt内容如下，每一行保存了学生的语文、数学、英语成绩，现要求计算出每个学生的总成绩，
并且按总成绩从高到低排序，并输出到文件students_sort.txt中（第1行为列名：序号，姓名，语文，数学，英语，总成绩）。
1   张三        87      89      90
2   李四        88      89      90
3   王五        76      78      79
4   赵六        45      67      66
5   孙七        78      77      88
*/

typedef struct Student{
	int id;
	char name[32];
	int s1;
	int s2;
	int s3;
	int sum;
}student;

int main(int argc, char *argv[]) {

	
	FILE *fp = fopen("student.txt","r");
	FILE *fp1 = fopen("student_sort.txt","w");
	if(fp == NULL||fp1==NULL){
		perror("打开文件失败");
		return -1;
	}
	
	int length=0;
	
	student *stu=malloc(sizeof(student));
	int i=0;
	while(fscanf(fp,"%d\t\t%s\t%d\t%d\t%d\n",stu[i]->id,stu[i]->name,stu[i]->s1,stu[i]->s2,stu[i]-.s3)!=EOF){
		
		stu[i]->sum=stu->s1+stu.s2+stu.s3;
		
		i++;	
	}
	
	for(int k=0;k<i-1;k++){
		stu temp;
		for(int j=0;j<i-1-k,j++){
			if(stu[j]->sum>stu[j+1]->sum){
				temp=stu[j];
				stu[j]=stu[j+1];
				stu[j+1]=temp;
			}
		}
	}
	int k=0;
	while(fprintf(fp2,"序号:%d，姓名:%s，语文:%d，数学:%d，英语:%d，总成绩:%d",stu[k]->id,stu[k]->name,stu[k]->s1,stu[k]->s2,stu[k]->s3,stu[k]->sum)!=EOF){
		k++;
	}
	

	
	
	fclose(fp);
	fclose(fp1);
	free(stu);

    return 0;
}
