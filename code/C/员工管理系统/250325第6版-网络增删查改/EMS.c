/***************************************************
# File Name:    emploee_system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月23日 星期日 17时16分10秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>	//引入正则表达式
//自定义头文件
#include "EMS.h"
#include "sysOpera.h"
#include "singleList.h"
#include "tcp_client.h"		//引入客户端操作，可以进行查询数据库等

//系统初始化
void sys_init(){
	//从数据库查询得到Admin结构体
	OP op = INQUR_ADMIN;
	int Admin_quantity = 0;
	Admin *p =create_client(op, &Admin_quantity);
	//循环遍历数据表结构体数组判断该用户密码是否正确
	puts("EMS中");
	for(int i=0; i<Admin_quantity; i++){
		printf("%d %s %s\n",p[i].id,p[i].name,p[i].password);

	}
	//将结构体中数据初始化到链表中
	
	//从数据库查询得到User结构体
	
	//将结构体中数据初始化到链表中
	//Node *head = NULL;	//定义头结点
}
/*
//登录界面
void test(){
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("- - - - - - - - - - 欢迎使用员工管理系统 - - - - - - - - - -\n");
	char namebuf[USER_LENGTH];			//定义存放用户输入用户名的缓冲数组
	char passbuf[USER_LENGTH];			//定义存放用户输入密码的缓冲数组
	char *ret_name;						//存放用户输入终端返回值，用于验证用户名，NULL表示输入非法
	char *ret_pass;						//存放用户输入终端返回值，用于验证用户密码，NULL表示输入非法
	printf("请输入用户名：\n");
	while(TRUE){	
		//用户输入验证
		ret_name = name_verifi( namebuf);
		if(ret_name == NULL){
			printf("用户名输入不合法 \n");
			break;
		}else {
			//判断用户输入是否为admin,rolse[0]为管理员
			if(strcmp( namebuf,roles[0] ) == 0 ){
			//当前登录用户为管理员
				printf("输入为管理员\n");
				printf("请输入密码：\n");
				ret_pass = password_verifi( passbuf );
				if(ret_pass == NULL){
					printf("密码输入不合法 \n");
					break;
				}else {
					printf("密码输入合法 \n");
					break;
				}		
			}else {
			//当前登录用户为普通用户
				//printf("输入为用户名\n");
				//判断用户名是否存在
				printf("请输入密码：\n");
				ret_pass = password_verifi( passbuf );
				if(ret_pass == NULL){
					printf("密码输入不合法 \n");
					break;
				}else {
					printf("密码输入合法 \n");
					break;
				}
			}	
		}
	}
	//用户名验证完成，区分出管理员和用户角色，分别验证密码
	
	//用户名和密码验证完成，区分出管理员和用户角色，执行进入二级菜单操作
	//printf("二级菜单\n");
}
*/
int main(int argc, char *argv[]){
	sys_init();
	//test();	
	
    return 0;
}
