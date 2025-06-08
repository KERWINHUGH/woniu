/***************************************************
# File Name:    42-结构体使用.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 28 Feb 2025 10:53:32 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 定义一个学生： id name age gender
typedef struct Student {
	char id[32];
	char name[32];
	int age;
	char gender[10];
}Student ;

typedef struct ClassRoom{
	char name[32];
	int num;
	Student stu[];

}ClassRoom;



void toString(Student s){
	printf("学生信息[学号：%s, 姓名：%s, 年龄：%d, 性别：%s ]\n", 
						s.id, s.name, s.age, s.gender );
}


int main(){
	//int a = 100;
	//int b = 20;
	//int arr[100] ;	
	
	Student stus[6] = {0};
	
	Student s = {
		"No.001",
		"jack",
		23,
		"male"
	};
	
	stus[0] = s;
	
	/*
		错误的赋值方式：
		stus[1] = {
			"No.002",
			"rose",
			21,
			"female"
		};
	*/
	
	strcpy(stus[1].id, "No.002"); 
	strcpy(stus[1].name, "rose"); 
	strcpy(stus[1].gender, "female");
	stus[1].age = 21; 
	
	// 遍历和原来的数组使用是一样的。。。。
	int length = sizeof(stus) / sizeof(stus[0]);
	for(int i = 0; i < length; i ++){
		toString(stus[i]);
	}

	return 0;
}

































