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
	puts("欢迎使用蜗牛门禁系统v1.0");
	
	char name[32];
	char password[32];
	
	bool f = true;
	while(f){
		puts("请选择：  1：登录  2：注册  3：退出");
		int op;
		scanf("%d", &op);
		
		switch(op){
			case 1: {
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
				break;
			}
			case 2:
				puts("请输入新用户名：");
				scanf("%s" , name );
				puts("请输入新用户密码：");
				scanf(" %s" , password );
				
				puts("---注册成功---");
				
				break;
			case 3:
				puts("---欢迎下次使用---");
				f = false;
				break;
			default:
				puts("---对不起，选项有误！---");
		}
	
	}
	
	
	
	puts("---end---");

    return 0;
}
