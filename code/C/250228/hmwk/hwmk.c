/***************************************************
# File Name:    hwmk.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Sat 01 Mar 2025 11:00:19 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//homework1:
typedef struct StudentGrade
{
	char id[32];
	char name[32];
	float ChineseGrade;
	float MathGrade;
	float EnglishGrade;
}StudentGrade;

StudentGrade s1[]=
{
	{.id={"junior1603"}, .name={"mike"}, .ChineseGrade=0, .MathGrade=0, .EnglishGrade=0},
	{.id={"junior1605"}, .name={"jesyk"}, .ChineseGrade=0, .MathGrade=0, .EnglishGrade=0}
};
StudentGrade s2[]=
{
	{.id={"10101"}, .name={"sun"}, .ChineseGrade=96, .MathGrade=0, .EnglishGrade=0},
	{.id={"10103"}, .name={"wang"}, .ChineseGrade=98.5, .MathGrade=0, .EnglishGrade=0},
	{.id={"10110"}, .name={"li"}, .ChineseGrade=100, .MathGrade=0, .EnglishGrade=0},
	{.id={"10108"}, .name={"ling"}, .ChineseGrade=83.5, .MathGrade=0, .EnglishGrade=0},
	{.id={"10106"}, .name={"zhang"}, .ChineseGrade=88, .MathGrade=0, .EnglishGrade=0}

};
int length1 =sizeof(s1)/sizeof(s1[0]);
int length2 =sizeof(s2)/sizeof(s2[0]);
/*
void prtf(StudentGrade s[],int sum)
{	

		if(sum=1)
		{
		printf("学号为%s的名字为%s的语文成绩是：%lf \t数学成绩是：%lf  \t 英语成绩是：%lf \n",s[0].id,s[0].name,s[0].ChineseGrade,s[0].MathGrade,s[0].EnglishGrade);
		
		}else if(sum=0)
		{
		printf("学号为%s的名字为%s的语文成绩是：%lf \t数学成绩是：%lf  \t 英语成绩是：%lf \n",s[1].id,s[1].name,s[1].ChineseGrade,s[1].MathGrade,s[1].EnglishGrade);
		
		}

}
*/
void scf(StudentGrade s[])
{
	for(int i=0;i<length1;i++)
	{
		puts("请输入学生的学号");
		scanf("%s",s[i].id);
		
		puts("请输入学生的名字");
		scanf("%s",s[i].name);
		
		puts("请输入学生的语文成绩");
		scanf("%f",&s[i].ChineseGrade);
		
		puts("请输入学生的数学成绩");
		scanf("%f",&s[i].MathGrade);
		
		puts("请输入学生的英语成绩");
		scanf("%f",&s[i].EnglishGrade);
	}
}

//homework2:
void cmpGrade(StudentGrade s[])
{
	scf(s1);
	int stusum1=0;
	int stusum2=0;
	stusum1=s[0].ChineseGrade+s[0].MathGrade+s[0].EnglishGrade;
	stusum2=s[1].ChineseGrade+s[1].MathGrade+s[1].EnglishGrade;
		
	printf("sum1:%d \n",stusum1);
	printf("sum2:%d \n",stusum2);
	if(stusum1>stusum2)
	{	
		printf("学号为%s的名字为%s的语文成绩是：%lf \t数学成绩是：%lf  \t 英语成绩是：%lf \n",s[0].id,s[0].name,s[0].ChineseGrade,s[0].MathGrade,s[0].EnglishGrade);
		//return true;
	}else
	{
		printf("学号为%s的名字为%s的语文成绩是：%lf \t数学成绩是：%lf  \t 英语成绩是：%lf \n",s[1].id,s[1].name,s[1].ChineseGrade,s[1].MathGrade,s[1].EnglishGrade);
		//return false;
	}
}
//homework3:
void sort(StudentGrade s[])
{
	int z;
	StudentGrade temp={0};
	//按照学号排序
	for(int i=0;i<length2-1;i++)
	{
		for(int j=i+1;j<length2;j++)
		{
			//z=s[i].id-s[j].id;
			if(strcmp(s[i].id,s[j].id)>0)
			{
				temp=s[i];
				s[i]=s[j];
				s[j]=temp;
			}
		}
	}
	for(int i=0;i<length2;i++)
	{
		printf("学号：%s，姓名：%s,成绩:%f \n",s[i].id,s[i].name,s[i].ChineseGrade);
	}
	//按照成绩排序
	for(int i=0;i<length2-1;i++)
	{
		for(int j=i+1;j<length2;j++)
		{
			
			if(s[i].ChineseGrade>s[j].ChineseGrade)
			{
				temp=s[i];
				s[i]=s[j];
				s[j]=temp;
			}
		}
	}
	for(int i=0;i<length2;i++)
	{
		printf("学号：%s，姓名：%s,成绩:%f \n",s[i].id,s[i].name,s[i].ChineseGrade);
	}
}

//homework4:


//homework5:

typedef struct Date
{
	int year;
	int month;
	int day; 
}Date;

Date date[6]=
{
	1805,12,5
	1917,11,20
	1975,5,5
	1563,2,10
	1860,8,10
	1627,4,4
};

int length3 =sizeof(date)/sizeof(date[0]);

typedef struct Book
{
	char id[32];
	char name[32];
	float prince;
	Date date[32];
}Book;



Book s3[]=
{
	{.id={"10101"}, .name={"sun"}, .prince=96, .date="17" },
	{.id={"10103"}, .name={"wang"}, .prince=98.5, .date="17"},
	{.id={"10110"}, .name={"li"}, .prince=100, .date="17"},
	{.id={"10108"}, .name={"ling"}, .prince=83.5, .date="17"},
	{.id={"10106"}, .name={"zhang"}, .prince=88, .date="17"}

};

void sortBook(Book s[])
{
	Book temp={0};
	//按照学号排序
	for(int i=0;i<length3-1;i++)
	{
		for(int j=i+1;j<length3;j++)
		{
			
			if(s[i].prince>s[j].prince)
			{
				temp=s[i];
				s[i]=s[j];
				s[j]=temp;
			}
		}
	}
	for(int i=0;i<length3;i++)
	{
		printf("书名：%s，作者：%s,价格:%f \n",s[i].id,s[i].name,s[i].prince);
	}
}

int main(int argc, char *argv[]) {
	
	
	//homework2:
	//cmpGrade(s1);
	
	//int f=cmpGrade(s1);
	//prtf(s1,f);
	
	sortBook(s3);
	
    return 0;
}
