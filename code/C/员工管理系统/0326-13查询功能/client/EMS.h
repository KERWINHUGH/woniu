/***************************************************
# File Name:    emploee_system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月23日 星期日 17时16分10秒
****************************************************/
#ifndef EMS_H
#define EMS_H

#include "list.h"

//系统初始化
Node * sys_init();
//登录
void login(Node *head);
//管理员登录后界面
void admin_first_UI(Node *head);
//员工登录后界面
void employee_first_UI(Node *head,Node *cur_user);


#endif


