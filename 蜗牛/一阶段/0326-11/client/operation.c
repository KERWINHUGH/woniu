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
#include "tcp_client.h"

//---------------------管理员操作------------------------
//增加员工
Node * adminAddEmployee(Node *head){
	//数据库新增操作
	OP op = ADD_EMPLOYEE;
	int employee_quantity = 0;
	//操作后得到表和结构体数组大小
	Employee *p =create_client(op, NULL,&employee_quantity);
	printf("%d\n",employee_quantity);
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		head = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	print_list(head);//打印链表
	return head;
}

//删除员工
Node * adminDeleteEmployee(Node *head){
	//数据库查删除操作
	OP op = DELETE_EMPLOYEE;
	int employee_quantity = 0;
	//删除后得到表和结构体数组大小
	Employee *p =create_client(op, NULL,&employee_quantity);
	printf("%d\n",employee_quantity);
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		head = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	print_list(head);//打印链表
	return head;
}
//修改员工
Node * adminUpdateEmployee(Node *head){
	//数据库查询操作
	OP op = UPDATE_EMPLOYEE;
	int employee_quantity = 0;
	//查询得到表和结构体数组大小
	Employee *p =create_client(op,NULL, &employee_quantity);
	printf("%d\n",employee_quantity);
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		head = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	print_list(head);//打印链表
	return head;
}
//---------------------员工操作------------------------
//显示员工部门所有人信息
void displayEmployee(Node *head,Node *cur_user){
    Node *temp = head;
	while(temp != NULL){
		if(temp->data.departments == cur_user->data.departments){	
			printf("\nEmployee %d: %s, %s, %d, %.1f, %s, %s, %s, %s",
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
	printf("%d\n",employee_quantity);
	Node *temp = head;  // 定义变量指针
	//将查询到的表结构体数组，依次赋值给链表中的元素
	for(int i=0; i< employee_quantity; i++){
		head = add_node(temp, p[i], i+1);    // 在链表的头部插入节点1
	}
	print_list(head);//打印链表
	return head;
    
}







