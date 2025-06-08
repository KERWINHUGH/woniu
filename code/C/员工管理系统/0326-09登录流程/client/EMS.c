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
#include "data.h"
#include "sysOpera.h"
//#include "singleList.h"
//#include "list.h"
#include "tcp_client.h"		//引入客户端操作，可以进行查询数据库等
#include "operation.h"		//引入用户操作



//系统初始化
Node * sys_init(){
	//从数据库查询得到Employee结构体
	puts("---------------------初始化----------------------");
	OP op = INQUR_EMPLOYEE;
	int employee_quantity = 0;
	//查询得到表和结构体数组大小
	Employee *p =create_client(op, NULL,&employee_quantity);
	//printf("%d\n",employee_quantity);
	Node *head = NULL;  // 定义头指针，初始化为NULL
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		head = add_node(head, p[i], i+1);    // 在链表的头部插入节点1
	}
	//print_list(head);//打印链表
	return head;
}

//登录界面
void login(Node *head){
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
			//查询输入用户名是否在链表中
			Node* cur_user = search_node(head, namebuf);
			if( cur_user == NULL){
				printf("用户名不存在\n");
       			 return ;
			}
			//判断用户输入是否为Employee,rolse[0]为管理员
			if(cur_user->data.roles == 0 ){
			//当前登录用户为管理员
				printf("输入为管理员\n");
				printf("请输入密码：\n");
				ret_pass = password_verifi( passbuf );
				if(ret_pass == NULL){
					printf("密码输入不合法 \n");
					break;
				}else {
					if(strcmp( cur_user->data.password,passbuf) != 0){
						printf("密码错误\n");
       			 		return;
					}
					printf("管理员登录成功 \n");
					admin_first_UI(head);
					break;
				}		
			}else if( cur_user->data.roles == 1 ){
				printf("请输入密码：\n");
				ret_pass = password_verifi( passbuf );
				if(ret_pass == NULL){
					printf("密码输入不合法 \n");
					break;
				}else {
					if(strcmp( cur_user->data.password,passbuf) != 0){
						printf("密码错误\n");
       			 		return;
					}
					printf("用户登录成功 \n");
					employee_first_UI(head, cur_user);
					break;
				}
			}	
		}
	}
}
void admin_first_UI(Node *head){
        while(1){
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("1-显示所有用户\n2-新增用户\n3-删除用户\n4-修改用户\n0-退出\n");
            printf("请选择服务：");
            int choice;
            int result = scanf(" %d", &choice);
            if(!result){
				// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
				while( getchar() != '\n' ){ }
				continue;
			}
            if(choice == 1){
                print_list(head);  // 显示所有员工信息
            }else if(choice == 2){
                adminAddEmployee(head);  	//增加员工
            }else if(choice == 3){
                adminDeleteEmployee(head);	//删除员工
            }else if(choice == 4){
                adminUpdateEmployee(head);	//修改员工
            }if(choice == 0){
                exit(0);
            }else{
                printf("没有该服务，请重新输入！\n");
            }
        }
}
void employee_first_UI(Node *head,Node *cur_user){
	// 普通用户界面
        while(1){
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("1-显示部门详细信息\n2-修改密码\n3-退出\n");
            printf("请选择服务：");
            int choice;
            int result = scanf(" %d", &choice);
            if(!result){
				// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
				while( getchar() != '\n' ){ }
				continue;
			}
            if(choice == 1){
            	displayEmployee(head, cur_user);
            }else if(choice == 2){
				updateEmployee(head, cur_user);
            }else if(choice == 3){
                exit(0);
            }else{
                printf("没有该服务，请重新输入！\n");
            }
        }
}

int main(){
	Node * head = sys_init();
	login(head);	
	
	free_list(head);
	
	
    return 0;
}
