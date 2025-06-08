/***************************************************
# File Name:    struct.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Fri 28 Feb 2025 02:23:47 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Teacher
{
	char id[32];
	char name[32];
	int age;
	char gender[32];
	double galacy;
	long number;
	char email[32];
	char adress[32];
};

typedef struct
{
	int year;
	int month;
	int day;
}Date;

typedef struct 
{
	char name[32];
	char adr[32];
	Date date;
}Product;

typedef struct 
{
	char name[32];
	int number;
	char names[20][32];
}Classroom;

void toString(struct Teacher s)
{
	printf("老师信息{ID：%s,姓名：%s,年龄：%d,性别：%s,工资:%f,电话:%ld,邮箱：%s,地址：%s \n}",s.id,s.name,s.age,s.gender,s.galacy,s.number,s.email,s.adress);
}
void prt( Product s)
{
	printf("产品信息{产品名：%s,产地地址：%s，产品生产日期：%d年-%d月-%d日 \n}",s.name,s.adr,s.date.year,s.date.month,s.date.day);
}
void prt1( Classroom s)
{
	printf("教室信息{教室名：%s,教室人数：%s，学生名字：%s \n}",s.name,s.number,s.names[]);
}

int main(int argc, char *argv[]) {
	
	Classroom classroom
	{
		.name="28期",
		.number=16,
		.name={"zdd","szd","fhz"}
	}
	prt1( classroom );
	
	Product product =
	{
		.name="车",
		.adr="japan",
		.date=
		{
			.year=2025,
			.month=02,
			.day=28
		}
	};
	
	//prt(product);
	
	//结构体使用方式1
	struct Teacher s1=
	{
		.name="rose",
		.age=22,
		.number=12345678912,
		.email="rose12345678@kfc.com",
	};
	//toString(s1);
	//结构体使用方式2
	struct Teacher s2=
	{
		"dfg5201314",
		"rose",
		22,
		"female",
		10000,
		12345678912,
		"rose12345678@kfc.com",
		"南京路520号"
	};
	//toString(s2);
	//结构体使用方式
	struct Teacher s3={0};
		strcpy(s3.name,"jack");
		s3.age=20;
		s3.number=13579111315;
		strcpy(s3.email,"jack12345678@ufc.com");
	//toString(s3);
	
	
	
    return 0;
}
