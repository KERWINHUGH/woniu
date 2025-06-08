/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// 数组的初始容量
int size = 3; 
// length是用户的个数
int length = 0;

typedef struct User {
	char name[32];
	char password[32];
	int age;
	char tel[32];
	char address[128];
	// 记录上次登录时间
	char loginTime[128];

}User;

// 用户的数组，改成了指针（为了可以动态分配内存）
User *users;

// 初始化函数
void init(){
	users = (User *)malloc( sizeof(User) * size );
	
	strcpy(users->name, "admin");
	strcpy(users->password, "123456");
	users->age = 23;
	strcpy(users->tel, "15888990000");
	strcpy(users->address, "中国南京");
	
	length++;
}
// 回收内存
void myFree(){
	free(users);
}


// 新增用户
void addUser(char *userName, char *password);
// 登录功能
int loginByUser( char* userName, char* password );

// 根据用户名，找到相应的索引
int isExist(char* userName);

void toString(User* u);

// 得到时间
char* getTime();

 
int main(int argc, char *argv[]) {
	// 初始化的函数要先调用。
	init();

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
					//  得到当前用户的上次登录时间：
					int index = isExist(loginName);
					if( strcmp( users[index].loginTime , "") != 0 ){
						printf("上次登录时间是：%s \n", users[index].loginTime);
					}else {
					
						puts("---- 这是你第一次登录 ---");
					}
					
					char *t = getTime();
					// 把当前时间，设置进用户的数据里					
					strcpy( users[index].loginTime, t );
				
				
					int op;
					while(true){
						puts("请选择：   1：显示所有用户   2：新增用户   3：修改用户   4：删除用户   5：退出");
						// 正常返回 1， 不正常返回 0
						int result = scanf(" %d", &op);
						
						printf("scanf输入之后的，返回值：%d \n" , result );
						
						if(!result){
							// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
							while( getchar() != '\n' ){ }
							continue;
						}
						
						
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
	
	// 释放内存
	myFree(users);
	
	puts("---end---");

    return 0;
}


// 注册用户：
void addUser(char *userName, char *password){
	
	if(length == size){
		puts("--- 对不起,数据已经满了！要扩容---");
		// 双倍扩容
		size = size * 2;
		
		User *temp = realloc( users , sizeof(User) * size);
		if(temp == NULL){
			fprintf(stderr, "对不起，扩容失败");
			return;
		}
		// 初始化新分配的内存
		memset( temp + size / 2 , 0 , sizeof(User) * size / 2 );
		
		users = temp;
	}
	
	//  写入数据
	strcpy(users[length].name, userName );
	strcpy(users[length].password, password );
	length++;
	puts("---注册成功---");
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
		printf("用户名：%s \n", users[i].name );
	
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



char* getTime(  ){
	char *t = (char *)malloc(128);
	
    time_t rawtime;
    struct tm *now;

    // 获取当前时间
    time(&rawtime);
    now = localtime(&rawtime);

    // 格式化日期和时间，但不包括星期
    strftime(t, 128, "%Y年%m月%d日 %H:%M:%S ", now);

	printf("getTime: %s \n", t);
	
	return t;
}









