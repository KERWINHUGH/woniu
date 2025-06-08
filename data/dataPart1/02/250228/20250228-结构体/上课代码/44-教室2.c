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
	Student stus[6];
	
	//Student stus[]; // 柔性数组 ，必须写在最后
}ClassRoom;


void toString(Student s){
	printf("学生信息[学号：%s, 姓名：%s, 年龄：%d, 性别：%s ]\n", 
						s.id, s.name, s.age, s.gender );
}

int main(){
	
	ClassRoom room = {
		.name = "高一3班",
		6,
		{
			{"No.001", "jack", 23, "male"},
			{.id = "No.002", .name = "李四", .age= 27, .gender = "male"},
			"No.003", "王五", 19, "male",
			"No.004", "李强", 21, "male",
			"No.005", "rose", 20, "female",
			"No.006", "赵六", 25, "male",
		}
	};

	printf("教室信息：%s , 人员信息：[\n", room.name);
	int length = sizeof(room.stus) /sizeof(room.stus[0]);
	
	for(int i = 0; i < length; i++){
		toString(room.stus[i]);
	}
	printf("] \n");


	puts("----------------------------------");
	
	Student temp = {0};
	toString(temp);
	
	Student ss = {.id = "No.002", .name = "李四", .age= 27, .gender = "male"};
	temp = ss;
	toString(temp);


	return 0;
}

































