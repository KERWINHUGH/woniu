/***************************************************
# File Name:    testReg.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Sat 22 Mar 2025 04:05:04 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

// 在 C 中使用正则表达式
int main(int argc, char *argv[]) {
	
	// 用户名规则：
	char *user_reg = "^[a-zA-Z][a-z|A-Z|0-9]{3,11}$";
	
	regex_t regex;
	int reti;
	
	// 编译正则
	reti = regcomp( &regex, user_reg, REG_EXTENDED );
	if(reti == 0){
		puts("ok!");
	}else {
		fprintf(stderr, "Could not compile regex\n");
		return 1;
	}
	
	// 进行正则匹配：
	char str[32];
	puts("请输入：");
	fgets( str, sizeof(str)-1, stdin );
	
	// 把fgets() 的换行去掉：
	char *newStr = strchr(str, '\n');
	if(newStr != NULL){
		*newStr = '\0';
	}
	printf("你输入的是：%s\n", str);
	
	// 执行匹配：
	reti = regexec( &regex, str, 0 , NULL , 0 );
	if(reti == 0){
		puts("符合规则！");
		
	}else if(reti == REG_NOMATCH ){
		puts("对不起，用户就应该是：首字符以英文开始的6-12位英文数字混输字符！");

	}else {
		char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
	}
	

    return 0;
}




















