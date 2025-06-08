/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>

void one(){
	puts("欢迎使用蜗牛门禁系统v1.0");
	puts("请选择：  1：登录  2：注册  3：退出");
	int op;
	scanf("%d", &op);
	
	switch(op){
		case 1:
			puts("执行登录的操作。。。");
			break;
		case 2:
			puts("执行注册的操作。。。");
			break;
		case 3:
			puts("---欢迎下次使用---");
			break;
		default:
			puts("---对不起，选项有误！---");
	}
}

void two(){
	puts("欢迎使用蜗牛门禁系统v2.0");
	puts("请选择：  1：登录  2：注册  3：退出");
	int op;
	scanf("%d", &op);
	
	if(op == 1){
		puts("执行登录的操作。。。");
	
	}else if(op == 2){
		puts("执行注册的操作。。。");
	
	}else if(op == 3){
		puts("---欢迎下次使用---");
		
	}else {
		puts("---对不起，选项有误！---");
	
	}
}

void three(){
	// 编写一个程序，从用户输入的三个整数中找出最大的一个，并输出。
	int a, b, c;
	
	puts("请输入三个数：");
	scanf("%d %d %d",&a, &b, &c);
	
	int max = a > b ? a : b;	
	max = max > c ? max : c;
	
	printf("最大值是：%d \n", max);
}

void four(){
	// 闰年的条件是年份能被 4 整除但不能被 100 整除，或者能被 400 整除。
	int year;
	puts("请输入一个年份：");
	scanf("%d",&year);
	
	if( year % 4 == 0 && year % 100 !=0 || year % 400 == 0 ){
		printf("%d,是闰年\n", year);
	}else {
		printf("%d,不是闰年\n", year);
	}
}

 
int main(int argc, char *argv[]) {
	
	two();
	//three();

	//four();

    return 0;
}
