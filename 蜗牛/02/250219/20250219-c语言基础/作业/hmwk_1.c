/***************************************************
# File Name:    hmwk_1.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 07:12:42 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	char name[10]; //= "jony";
	int age; //= 22;
	char gender[10]; //="male";
	int salary; //= 5000;
	int birth; //=0617;
	int num; //= 189xxxx1234;
	char add[10]; //= "xian";
	
	puts("请输入姓名：");
	scanf("%s",name);

	puts("请输入年龄：");
	scanf("%d",&age);

	puts("请输入性别：");
	scanf("%s",gender);

	puts("请输入工资：");
	scanf("%d",&salary);

	puts("请输入生日：");
	scanf("%d",&birth);

	puts("请输入电话：");
	scanf("%d",&num);

	puts("请输入地址：");
	scanf("%s",add);

	
	printf("姓名：%s,年龄：%d,性别：%s,薪水：%d,生日：%d,电话：%d,地址：%s\n",name,age,gender,salary,birth,num,add);
	
    return 0;
}
