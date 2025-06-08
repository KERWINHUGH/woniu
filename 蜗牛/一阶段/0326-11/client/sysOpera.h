/***************************************************
# File Name:    emploee_system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月23日 星期日 17时16分10秒
****************************************************/
#ifndef SYS_OPERATION_H
#define SYS_OPERATION_H



//用户名输入验证
/*
** 参数：1.用户名，从终端接收，函数调用后做出判断；2.用户名长度，用于指定从终端接收字符的长度
** 返回值：成功：返回从终端接收的用户名；失败，返回NULL
*/
char * name_verifi( char * namebuf );
//用户密码输入验证
/*
** 参数：1.用户密码，从终端接收，函数调用后做出判断；2.用户密码长度，用于指定从终端接收字符的长度
** 返回值：成功：返回从终端接收的用户密码；失败，返回NULL
*/
char * password_verifi( char * passbuf );
void test();


#endif

