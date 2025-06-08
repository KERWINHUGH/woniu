/***************************************************
# File Name:    op.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月27日 星期四 01时13分24秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "operation.h"
#include "sysOpera.h"
#include "tcp_client.h"


//---------------------管理员操作------------------------
//通过链表查询所有人信息
void displayAllEmployee(Node *head){
    Node *temp = head;
	while(temp != NULL){	
			printf("%d: %s, %s, %d, %.1f, %s, %s, %s, %s",
			temp->data.id,
			temp->data.name,
			temp->data.password,
			temp->data.age,
			temp->data.salary,
			gender_to_string(temp->data.genders),
			department_to_string(temp->data.departments),
			title_to_string(temp->data.titles),
			role_to_string(temp->data.roles));
		temp = temp->next;
	}
	printf("\n");
}
//员工与管理员通用查询
void selectEmployee( OP op){
    //从数据库查询得到Employee结构体
	int employee_quantity = 0;
	//查询得到表和结构体数组大小
	Employee *p =create_client(op, NULL,&employee_quantity);
	//printf("employee_quantity：%d\n",employee_quantity);
	//打印查询到的表结构体数组
	
	for(int i=0; i< employee_quantity; i++){
		printf("查询 ------:%d\n",i);
		printf("%d: %s, %s, %d, %.1f, %s, %s, %s, %s\n",
			p->id,
			p->name,
			p->password,
			p->age,
			p->salary,
			gender_to_string(p->genders),
			department_to_string(p->departments),
			title_to_string(p->titles),
			role_to_string(p->roles));
	}
	free(p);
	return ; 
}
//增加员工
Node * adminAddEmployee(Node *head){
	//数据库新增操作
	OP op = ADD_EMPLOYEE;
	int employee_quantity = 0;
	//操作后得到表和结构体数组大小
	Employee *p =create_client(op, head,&employee_quantity);
	printf("employee_quantity：%d\n",employee_quantity);
	if( p == NULL){
		printf("管理员新增员工出错");
		return NULL;
	}
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		temp = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	print_list(head);//打印链表
	writeLog("admin","新增用户");
	return head;
}

//删除员工
Node * adminDeleteEmployee(Node *head){
	//数据库查删除操作
	OP op = DELETE_EMPLOYEE;
	int employee_quantity = 0;
	//删除后得到表和结构体数组大小
	Employee *p =create_client(op, NULL,&employee_quantity);
	printf("employee_quantity：%d\n",employee_quantity);
	if( p == NULL){
		printf("管理员删除员工出错");
		return NULL;
	}
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		temp = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	printf("管理员删除密码出错");
	writeLog("admin","删除密码");
	return NULL;
}
//修改员工
Node * adminUpdateEmployee(Node *head){
	//数据库查询操作
	OP op = UPDATE_EMPLOYEE;
	int employee_quantity = 0;
	//查询得到表和结构体数组大小
	Employee *p =create_client(op,NULL, &employee_quantity);
	printf("employee_quantity：%d\n",employee_quantity);
	if( p == NULL){
		printf("管理员修改密码出错");
		return NULL;
	}
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		temp = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	writeLog("admin","管理员修改密码");
	print_list(head);//打印链表
	return head;
}
//---------------------员工操作------------------------
//显示员工部门所有人信息
void displayEmployee(Node *head,Node *cur_user){
    Node *temp = head;
	while(temp != NULL){
		if(temp->data.departments == cur_user->data.departments){	
			printf("%d: %s, %s, %d, %.1f, %s, %s, %s, %s",
			temp->data.id,
			temp->data.name,
			temp->data.password,
			temp->data.age,
			temp->data.salary,
			gender_to_string(temp->data.genders),
			department_to_string(temp->data.departments),
			title_to_string(temp->data.titles),
			role_to_string(temp->data.roles));
		}
		temp = temp->next;
	}
	printf("\n");
}
//用户修改密码
Node * updateEmployee(Node *head,Node *cur_user){
    //从数据库查询得到Employee结构体
	OP op = UPDATE_EMPLOYEE;
	int employee_quantity = 0;
	//查询得到表和结构体数组大小
	Employee *p =create_client(op, cur_user,&employee_quantity);
	printf("employee_quantity：%d\n",employee_quantity);
	if( p == NULL){
		printf("用户修改密码出错");
		return NULL;
	}
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		temp = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	writeLog(cur_user->data.name,"修改密码");
	print_list(head);//打印链表
	return head;
}







