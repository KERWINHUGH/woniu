/***************************************************
# File Name:    08-得到输入.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 04:58:07 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	// 得到键盘的输入：
	
	// 1: 得到整数
	int num;
	//printf("num变量的地址是：%p \n", &num );
	puts("请输入一个整数:");	
	// & 取址符 ： 把变量的地址得到
	scanf("%d" , &num ); // 阻塞式的函数：
	printf("你得到的值是：%d \n", num);
	

	// 2：得到字符
	char ch;
	puts("请输入一个字符：");
	scanf(" %c", &ch);
	printf("你得到的字符串：%c \n", ch);
	
	// 3: 得到字符串
	char name[32];
	puts("请输入你的姓名：");
	scanf(" %s", name);
	printf("你输入的姓名是：%s \n", name);

    return 0;
}
