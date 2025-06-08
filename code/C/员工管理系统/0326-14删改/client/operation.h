/***************************************************
# File Name:    op.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月27日 星期四 01时13分24秒
****************************************************/

#ifndef EMPLOYEE_OPERATION_H
#define EMPLOYEE_OPERATION_H

#include "list.h"

//---------------------管理员操作------------------------
//通过链表查询所有人信息
void displayAllEmployee(Node *head);
//增加员工
Node * adminAddEmployee(Node *head);
//删除员工
Node * adminDeleteEmployee(Node *head);
//修改员工
Node * adminUpdateEmployee(Node *head);
//---------------------员工操作------------------------
//显示员工部门所有人信息
void displayEmployee(Node *head,Node *cur_user);
//用户修改密码
Node * updateEmployee(Node *head,Node *cur_user);
//根据操作查询，得到返回的表
void selectEmployee( OP op);


#endif


