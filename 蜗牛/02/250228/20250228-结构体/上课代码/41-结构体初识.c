/***************************************************
# File Name:    41-结构体
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 28 Feb 2025 10:53:32 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 定义一个学生： id name age gender
struct Student {
	char id[32];
	char name[32];
	int age;
	char gender[10];
};
void toString(struct Student s){
	printf("学生信息[学号：%s, 姓名：%s, 年龄：%d, 性别：%s ]\n", s.id, s.name, s.age, s.gender);
}
int main(int argc, char *argv[]) {
	// 结构体的使用方式：
	// 1:
	struct Student s01 = {
		.age = 22,
		.name = "jack",
		.gender = "male",
		.id = "No.001"
	};
	toString(s01);
	// 2:
	struct Student s02 = {
		"No.002",
		"张三",
		26,
		"男"
	};
	toString(s02);
	// 3: 
	struct Student s03 = {0};
	
	//s03.id = "No.003";  这么写是错误的！
	strcpy(s03.id , "No.003");
	strcpy(s03.name , "rose");
	s03.age = 21;
	strcpy(s03.gender , "female");
	
	// 给s03的各属性赋值。。。
	toString(s03);
	

    return 0;
}








