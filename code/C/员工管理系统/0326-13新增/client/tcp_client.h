/***************************************************
# File Name:    system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月20日 星期四 21时55分11秒
****************************************************/

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H 

#define SERVER_ADDR "127.0.0.1"		//定义服务器地址
#define SERVER_PORT 8080			//定义服务器端口号
#define BUFF_SIZE 1024				//定义缓冲区大小

#include "list.h"


//管理员操作-----------------------------------------------------
//创建客户端连接并发送用户操作
Employee * create_client(OP op, Node * node,int *employee_quantity);
//客户端通信发送用户Employee的操作
Employee* client_write(int client_fd ,OP op,Node *node, int *employee_quantity);
//查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
bool EmployeeName_is_exist( int client_fd,char *name );
//查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
bool EmployeePassword_is_exist(int client_fd, char *password);
//跟新管理员用户操作-----增操作
Employee *clientAddEmployee(Node * node, int client_fd);
//跟新管理员用户操作-----删操作
Employee *clientDeleteEmployee(Node * node,int client_fd);
//跟新管理员用户操作-----改操作
Employee *clientAdminUpdate(Node * node,int client_fd);
//员工操作--------------------------------------------------------
//查询Employee表并返回结构体数组
Employee *clientInqurEmployee(int client_fd ,int *Employee_quantity);
//员工修改密码操作
Employee *clientEmployeeUpdate(Node * head,int client_fd);
//服务端操作--------------------------------------------------------
//接收服务端发送的数据表，并转为Employee结构体
Employee * client_read(int client_fd ,int *Employee_quantity);





#endif






