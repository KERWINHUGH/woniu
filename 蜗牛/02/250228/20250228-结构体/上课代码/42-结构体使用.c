/***************************************************
# File Name:    42-结构体使用.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 28 Feb 2025 10:53:32 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// 定义一个结构体，也描述日期
typedef struct {
	int year;
	int month;
	int day;
} Date;

// 定义一个学生： id name age gender
typedef struct Student {
	char id[32];
	char name[32];
	int age;
	char gender[10];
	
	// 结构体的嵌套：在结构体内部，又有一个结构体成员
	Date birthday;
	
}Student ;

void toString(Student s){
	printf("学生信息[学号：%s, 姓名：%s, 年龄：%d, 性别：%s ,生日：%d 年- %d 月-%d 日]\n", 
						s.id, s.name, s.age, s.gender, s.birthday.year, s.birthday.month, s.birthday.day );
}
int main(){
	Student s = {
		.id = "No.001",
		.age = 22,
		.name = "jack",
		.gender = "male",
		.birthday = {
			2020,
			6,
			23
		}
	}; 
	toString(s);

	return 0;
}





