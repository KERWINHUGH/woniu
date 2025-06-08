/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 全局变量 ， （函数内部的变量是局部变量,只有在函数内才能访问）
char names[10][32] = {"admin"};
char passwords[10][32] = {"1234"};
int length = sizeof(names) / sizeof(names[0]);

void addUser(){
	char newName[32];
	char newPassword[32];
	
	puts("请输入登录用户名：");
	scanf(" %s" , newName );
	puts("请输入登录户密码：");
	scanf(" %s" , newPassword );
	
	int index = -1;
	// 要先选中可以写入数据的索引
	for(int i = 0; i < length; i++){
		//printf("%d号位置的值是：---%s===\n", i, names[i]);
		if(strcmp(names[i],"") == 0 ){
			index = i;
			break;
		}
	}
	
	if(index >= 0){
		strcpy(names[index], newName );
		strcpy(passwords[index], newPassword );
		puts("---注册成功---");
	}else {
		puts("--- 对不起,数据已经满了 ---");					
	}
}

 
int main(int argc, char *argv[]) {
	puts("欢迎使用蜗牛门禁系统v1.0");
	
	
	bool f = true;
	
	
	while(f){
		puts("请选择：  1：登录  2：注册  3：退出");
		int op;
		scanf("%d", &op);
		
		switch(op){
			case 1: {
				char loginName[32];
				char loginPassword[32];
				
				puts("请输入登录用户名：");
				scanf("%s" , loginName );
				puts("请输入登录户密码：");
				scanf(" %s" , loginPassword );
				
				// 循环遍历数组，匹配需要的值：
				bool f = false;
				for(int i = 0; i < length; i++){
					if(strcmp(names[i], loginName) == 0 && strcmp(passwords[i], loginPassword) == 0 ){
						f = true;
						break;
					}
				}
				
				if(f){
					int op;
					while(true){
						puts("请选择：   1：显示所有用户   2：新增用户   3：修改用户   4：删除用户   5：退出");
						scanf(" %d", &op);
						
						printf("op---->%d\n", op );
						if(op == 1){
							for(int i = 0; i < length; i++){
								if(strcmp(names[i],"") != 0 ){
									printf("用户名：%s , 密码：%s \n", names[i], passwords[i]);
								}
							}
						
						}else if(op == 2){
							// 调用我们自己写的，新增用户的函数。
							addUser();
						
						}else if(op == 3){
						
						}else if(op == 4){
						
						}else if(op == 5){
							break;
						}else {
							puts("请不起，请输入正确的选项！");
						}
					}
					
				}else {
					puts("username or password error!");
				}
				break;
			}
			case 2:{
					// 调用我们自己写的，新增用户的函数。
					addUser();
					
					break;
				}
			case 3:
				puts("---欢迎下次使用---");
				f = false;
				break;
			default:
				puts("---对不起，选项有误！---");
		
		}
	
	}
	
	
	
	puts("---end---");

    return 0;
}
