/***************************************************
# File Name:    01-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 05:29:15 PM PST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

/*
	char str[] = "女";
	int length = sizeof(str) / sizeof(str[0]);
	for(int i = 0; i < length; i ++){
		printf("%c , %d \n", str[i], str[i]);
	}
*/


	char name[32];
	//puts("请输入名称：");
	//scanf("%s", name);

	int age;
	//puts("请输入年龄：");
	//scanf(" %d", &age);

	char gender[32];
	//puts("请输入性别：");
	//scanf(" %s", gender);
	
	puts("请输入一个学生的信息：按名字，年龄，性别顺序输入：");
	scanf("%s %d %s", name, &age, gender);
	
	printf("学生的姓名：%s ，年龄：%d ，性别：%s \n", name, age, gender );

    return 0;
}






