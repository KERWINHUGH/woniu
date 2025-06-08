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
//#include "singleList.c"


//定义客户端向服务器发送的sql操作，与OP枚举对应
//const char *op_str[] = { "add_admin","delete_admin","modify_admin","inqur_admin","add_user","delete_user","modify_user","inqur_user" };

//系统初始化
/*
void sys_init(){
	//从数据库查询得到数据表
	User u1 = {"No.01","admin1","1","123456","陕西西安"};
	Node *head = createNode(u1);
}
*/
//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
char *op_to_string(OP op){
	switch(op){
		case ADD_ADMIN:	return "ADD_ADMIN";
		case DELETE_ADMIN:	return "DELETE_ADMIN";
		case MODIFY_ADMIN:	return "MODIFY_ADMIN";
		case INQUR_ADMIN:	return "INQUR_ADMIN";
		case ADD_USER:	return "ADD_USER";
		case DELETE_USER:	return "DELETE_USER";
		case MODIFY_USER:	return "MODIFY_USER";
		case INQUR_USER:	return "INQUR_USER";
		default:	return "INQUR_USER";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的OP枚举值
*/
OP string_to_op(const char *str){
	if(strcmp(str,"ADD_ADMIN") == 0 )
	return ADD_ADMIN;
	if(strcmp(str,"DELETE_ADMIN") == 0 )
	return DELETE_ADMIN;
	if(strcmp(str,"MODIFY_ADMIN") == 0 )
	return MODIFY_ADMIN;
	if(strcmp(str,"INQUR_ADMIN") == 0 )
	return INQUR_ADMIN;
	if(strcmp(str,"ADD_USER") == 0 )
	return ADD_USER;
	if(strcmp(str,"DELETE_USER") == 0 )
	return DELETE_USER;
	if(strcmp(str,"MODIFY_USER") == 0 )
	return MODIFY_USER;
	if(strcmp(str,"INQUR_USER") == 0 )
	return INQUR_USER;
	return INQUR_USER;	//默认返回
}

//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *gender_to_string(Gender gender){
	switch(gender){
		case MALE:	return "MALE";
		case FEMALE:	return "FEMALE";
		default:	return "MALE";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Gender枚举值
*/
Gender string_to_gender(const char *str){
	if(strcmp(str,"MALE") == 0 )
	return MALE;
	if(strcmp(str,"FEMALE") == 0 )
	return FEMALE;
	return MALE;	//默认返回男性
}
//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *department_to_string(Department department){
	switch(department){
		case SALES:	return "SALES";
		case MARKETING:	return "MARKETING";
		case AFTER_SALE:	return "AFTER_SALE";
		default:	return "SALES";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Department枚举值
*/
Department string_to_department(const char *str){
	if(strcmp(str,"SALES") == 0 )
	return SALES;
	if(strcmp(str,"MARKETING") == 0 )
	return MARKETING;
	if(strcmp(str,"AFTER_SALE") == 0 )
	return AFTER_SALE;
	return SALES;	//默认返回
}
//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *title_to_string(Title title){
	switch(title){
		case MANAGER:	return "MANAGER";
		case CAPTAIN:	return "CAPTAIN";
		case SALES_WORKER:	return "SALES_WORKER";
		case MARKETING_WORKER:	return "MARKETING_WORKER";
		case AFTER_SALE_WORKER:	return "AFTER_SALE_WORKER";
		default:	return "MANAGER";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Title枚举值
*/
Title string_to_title(const char *str){
	if(strcmp(str,"MANAGER") == 0 )
	return MANAGER;
	if(strcmp(str,"CAPTAIN") == 0 )
	return CAPTAIN;
	if(strcmp(str,"SALES_WORKER") == 0 )
	return SALES_WORKER;
	if(strcmp(str,"MARKETING_WORKER") == 0 )
	return MARKETING_WORKER;
	if(strcmp(str,"AFTER_SALE_WORKER") == 0 )
	return AFTER_SALE_WORKER;
	return MANAGER;	//默认返回
}
//枚举转字符串映射函数
/*
** 参数：要转换的枚举值
**返回值：对应的字符串常量
*/
const char *role_to_string(Role role){
	switch(role){
		case role_admin:	return "role_admin";
		case role_employees:	return "role_employees";
		default:	return "role_admin";
	}
}
//字符串转枚举映射函数
/*
** 参数：str - 要转换的字符
**返回值：对应的Role枚举值
*/
Role string_to_role(const char *str){
	if(strcmp(str,"role_admin") == 0 )
	return role_admin;
	if(strcmp(str,"role_employees") == 0 )
	return role_employees;
	return role_employees;	//默认返回
}

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
		}/*else {
		
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
		}*/	
	}
	//用户名验证完成，区分出管理员和用户角色，分别验证密码
	
	//用户名和密码验证完成，区分出管理员和用户角色，执行进入二级菜单操作
	//printf("二级菜单\n");
}
/*
int main(int argc, char *argv[]) {
	//sys_init;
	test();

	
	
	
    return 0;
}
*/









