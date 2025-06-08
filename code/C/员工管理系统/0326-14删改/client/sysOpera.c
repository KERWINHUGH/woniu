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
#include <time.h>	//引入时间函数
#include <regex.h>	//引入正则表达式
//自定义头文件
#include "sysOpera.h"
#include "data.h"			//引入系统所需要的结构体




void writeLog(char *name, char *log){
	// 写日志
    FILE *fp = fopen("operation_log.txt", "a");
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", p);
    fprintf(fp, "时间：%s，用户：%s，操作：%s\n", buffer, name, log);
    fclose(fp);
}

//用户名输入验证
/*
** 参数：1.用户名，从终端接收，函数调用后做出判断；2.用户名长度，用于指定从终端接收字符的长度
** 返回值：成功：返回从终端接收的用户名；失败，返回NULL
*/
char * name_verifi( char * namebuf){
	char * ret_val;				//fgets返回值，从终端读取成功返回读取到的字符串首地址，否则返回NULL
	int reti;
	regex_t regex;				//正则变量
	char *user_reg = "^[a-zA-Z0-9]{4,12}$";	// 用户名规则：以大写字母开头，包含大小写和数字的4-12位字符
	
	reti = regcomp( &regex, user_reg, REG_EXTENDED );	// 编译正则
	if(reti != 0){
		fprintf(stderr, "Could not compile regex\n");
		return NULL;
	}
	//使用fgets从终端接收用户输入
	ret_val = fgets(namebuf, USER_LENGTH, stdin);	
	// 把fgets() 的换行去掉：
	char *newStr = strchr(namebuf, '\n');
	if(newStr != NULL){
		*newStr = '\0';
	}
	//进行正则匹配，判断输入是否合法
	if(ret_val != NULL ){
		//1.用户输入不为空，则先判断输入用户名是否合法（符合正则表达）
		// 执行匹配：
		reti = regexec( &regex, ret_val, 0 , NULL , 0 );
		if(reti == 0){
			//用户名符合规则，返回从终端输入的字符串
			return ret_val;
		}else if(reti == REG_NOMATCH ){
			//用户名不符合规则
			puts("对不起，用户名是包含大小写字母和数字的4-12位字符！");
			//printf("输入的是：%s \n",namebuf);
			return NULL;	
		}else {
			//正则匹配失败
			char msgbuf[100];
		    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		    return NULL;
		}
	}
	return NULL;
}
//用户密码输入验证
/*
** 参数：1.用户密码，从终端接收，函数调用后做出判断；2.用户密码长度，用于指定从终端接收字符的长度
** 返回值：成功：返回从终端接收的用户密码；失败，返回NULL
*/
char * password_verifi( char * passbuf){
	char * ret_val;				//fgets返回值，从终端读取成功返回读取到的字符串首地址，否则返回NULL
	int reti;
	regex_t regex;				//正则变量
	char *user_reg = "^[A-Z][a-zA-Z_0-9]{3,11}$";	// 密码规则：以大写字母开头，包含大小写和数字的4-12位字符
	
	reti = regcomp( &regex, user_reg, REG_EXTENDED );	// 编译正则
	if(reti != 0){
		fprintf(stderr, "Could not compile regex\n");
		return NULL;
	}
	//使用fgets从终端接收用户输入
	ret_val = fgets(passbuf, USER_LENGTH, stdin);	
	// 把fgets() 的换行去掉：
	char *newStr = strchr(passbuf, '\n');
	if(newStr != NULL){
		*newStr = '\0';
	}
	//进行正则匹配，判断输入是否合法
	if(ret_val != NULL ){
		//1.用户输入不为空，则先判断输入用户名是否合法（符合正则表达）
		// 执行匹配：
		reti = regexec( &regex, ret_val, 0 , NULL , 0 );
		if(reti == 0){
			//用户名符合规则，返回从终端输入的字符串
			return ret_val;
		}else if(reti == REG_NOMATCH ){
			//用户名不符合规则
			puts("对不起，用户密码是以大写字母开头，包含大小写字母和数字和下划线的4-12位字符！");
			//printf("输入的是：%s \n",namebuf);
			return NULL;	
		}else {
			//正则匹配失败
			char msgbuf[100];
		    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		    return NULL;
		}
	}
	return NULL;
}
