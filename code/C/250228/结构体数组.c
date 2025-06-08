/***************************************************
# File Name:    结构体数组.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Fri 28 Feb 2025 03:54:36 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 

 
typedef struct
{
	char id[];
	char name[];
	int age;
	int number;
	Students student[3];
}Students;

 void prit()
 {
 	printf("学生信息：{学生ID：%s,学生姓名：%s,学生年龄：%s，学生数量：%d}",s.id,s.name,s.age,s.number);
 }
 
int main(int argc, char *argv[]) {

	Students stu=
	{
		.id="k1",
		.name="jack",
		.age=17,
		.number=20
		.student=
		{
			
		}
	};
	student[]={0};
	stu.student.name
	
	
    return 0;
}
