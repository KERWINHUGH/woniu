/***************************************************
# File Name:    test4.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 11:20:56 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
int main(int argc, char *argv[]) {

		
	int num;
	char name[32];
	char password[32];

	char loginName[32];
	char loginPassword[32];

	int n_t,p_t;
	
	puts("欢迎使用蜗牛门禁系统！");
	
	while(1)
	{

	puts("请选择需要的操作：1：注册    2：登录    3：退出");

	scanf("%d",&num);

	switch(num)
	{
		case 1:
			puts("请输入新用户名");
			scanf("%s",name);
			puts("请输入新用户密码");
			scanf("%s",password);

			puts("注册成功！");

			break;
		case 2:

			puts("请输入登录用户名");
			scanf("%s",loginName);
			puts("请输入登录用户密码");
			scanf("%s",loginPassword);
			
			n_t = strcmp(name,loginName);
			p_t = strcmp(password,loginPassword);

			if(n_t)
			{
				puts("username error!");
			}else if(p_t)
			{
				puts("password error!");
			}else if(!n_t &&!p_t)
			{
				puts("login success!");
			} 

			break;
		case 3:
			puts("您已退出系统。");

			return 0;

		default:
			puts("输入错误,请重新输入！");
			break;

	}
	}
    return 0;
}
