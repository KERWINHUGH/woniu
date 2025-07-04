/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct User {
	char name[32];
	char password[32];
	int age;
	char tel[32];
	char address[128];

}User;

// 全局变量 ， （函数内部的变量是局部变量,只有在函数内才能访问）
User users[5] = {
	{"admin","1234",23,"13344556677", "江西南昌"}
};

int length = sizeof(users) / sizeof(users[0]);

// 新增用户
void addUser(char *userName, char *password);
// 登录功能
int loginByUser( char* userName, char* password );

// 根据用户名，找到相应的索引
int isExist(char* userName);

void toString(User* u);
 
int main(int argc, char *argv[]) {
	puts("欢迎使用蜗牛门禁系统v3.0");
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
				
				// ..... login ------
				int f = loginByUser(loginName, loginPassword);
				
				if(f > 0){
					int op;
					while(true){
						puts("请选择：   1：显示所有用户   2：新增用户   3：修改用户   4：删除用户   5：退出");
						scanf(" %d", &op);
						
						printf("op---->%d\n", op );
						if(op == 1){
							for(int i = 0; i < length; i++){
								if(strcmp(users[i].name,"") != 0 ){
									// 传的是结构体的指针
									toString( &users[i]);
								}
							}
						
						}else if(op == 2){
							char newName[32];
							char newPassword[32];
							
							puts("请输入新用户名：");
							scanf(" %s" , newName );
							
							// 返回 -1 代表这个用户名，在已经有的数据里不存在。
							int index = isExist(newName);
							if(index == -1){
								puts("请输入新密码：");
								scanf(" %s" , newPassword );
								// 调用我们自己写的，新增用户的函数。
								addUser(newName, newPassword);
							}else{
								puts("对不起，用户名已经存在！");
							}
						
						}else if(op == 3){
						
						}else if(op == 4){
						
						}else if(op == 5){
							break;
						}else {
							puts("请不起，请输入正确的选项！");
						}
					}
					
				}else if(f < 0) {
					puts("sorry userName error!");
				}else {
					puts("sorry password error!");
				}
				break;
			}
			case 2:{
					char newName[32];
					char newPassword[32];
					
					puts("请输入新用户名：");
					scanf(" %s" , newName );
					
					// 返回 -1 代表这个用户名，在已经有的数据里不存在。
					int index = isExist(newName);
					if(index == -1){
						puts("请输入新密码：");
						scanf(" %s" , newPassword );
						// 调用我们自己写的，新增用户的函数。
						addUser(newName, newPassword);
					}else{
						puts("对不起，用户名已经存在！");
					}
					
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
// 注册用户：
void addUser(char *userName, char *password){
	
	int index = -1;
	// 要先选中可以写入数据的索引
	for(int i = 0; i < length; i++){
		//printf("%d号位置的值是：---%s===\n", i, names[i]);
		if(strcmp(users[i].name ,"") == 0 ){
			index = i;
			break;
		}
	}
	
	if(index >= 0){
		strcpy(users[index].name, userName );
		strcpy(users[index].password, password );
		puts("---注册成功---");
	}else {
		puts("--- 对不起,数据已经满了 ---");					
	}
}

// 登录功能：
/*
	返回：1 代表成功
	返回：-1 代表用户名有误
	返回：0 密码有误
*/
int loginByUser(char *userName, char *password){
	// 调用：根据用户名找索引的函数
	int index = isExist(userName);
	
	if(index >= 0 ){
		if(strcmp(users[index].password , password ) == 0){
			index = 1;
		}else {
			index = 0;
		}
	}
	
	return index;
}
// 根据用户名，找到相应的索引
int isExist(char *userName){
	int index = -1;
	for(int i = 0; i < length; i++){
		if(strcmp(users[i].name , userName) == 0  ){
			index = i;
			break;
		}
	}
	return index;
}


void toString(User *u){
	printf("用户信息：[ 账号：%s, 密码：%s, 年龄：%d, 电话：%s, 地址：%s ] \n", u->name, u->password, u->age, u->tel, u->address );
}













