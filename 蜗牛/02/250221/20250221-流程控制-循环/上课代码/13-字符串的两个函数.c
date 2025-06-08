/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
int main(int argc, char *argv[]) {
	char name[32];
	char password[32];
	
	puts("请输入新用户名：");
	scanf("%s" , name );
	puts("请输入新用户密码：");
	scanf(" %s" , password );
	
	printf("得到的用户名：%s 和密码:%s \n", name, password);
	
	char loginName[32];
	char loginPassword[32];
	
	puts("请输入登录用户名：");
	scanf("%s" , loginName );
	puts("请输入登录户密码：");
	scanf(" %s" , loginPassword );
	
	int n_t = strcmp(name, loginName);
	int p_t = strcmp(password, loginPassword);
	
	if(!n_t && !p_t){
		puts("login success");
	}else {
		puts("username or password error!");
	}
	
	
	
	puts("---end---");

    return 0;
}
