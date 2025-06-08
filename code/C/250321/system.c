/***************************************************
# File Name:    system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月20日 星期四 21时55分11秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "sqlope.h"

//int login_status = 0;

void firstUi();
void login();

void firstUi(){
    // 一级界面
    char flag = '1';
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("- - - - - - - - -  欢迎使用蜗牛门禁系统 - - - - - - - -\n");
    
    while(flag == '1'){
        printf("- - - - - - - - - 1-登录 2-注册 3-退出 - - - - - - - -\n");
        printf("请选择服务：");
        char choice;
        scanf(" %c", &choice);
        switch (choice) {
            case '1': //login_status = login();flag = '0';break;
				   login();
				   flag = '0';
				   break;
            case '2': addUser();break;
            case '3': exit(0);break;
            default: printf("输入错误，请重新输入！\n");break;
        }
    }
}

int login(){
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    char password[20],flag0='1',flag1='0';
    int error = 0;   // 记录密码连续错误次数
    while(flag0=='1'){
        printf("请输入用户名：");
        scanf("%s",username);
        if(searchUser(username) == -1){
            printf("用户名不存在，请重新输入\n");
            printf("继续输入请按1，结束请按其他键: ");
            scanf(" %c",&flag0);
            if(flag0 != '1'){
                return 0;
            }
            continue;
        }
        flag0 = '0';
        flag1 = '1';
    }

    while(flag1=='1'){
        printf("请输入密码：");
        scanf("%s",password);      
        User *current = getUserInfo(username);  // 用户存在，则获取到该用户的信息保存在结构体中
        // 检查密码是否正确
        if(strcmp(password,current->password)==0){
            // 检查状态是否正常，为0
            if(current->status == 0){
                // 检查账户是否为锁定状态，如果是继续检查锁定时间是否已达到5分钟
                if(current->lock_status == 1 && current->lock_time + 300 > time(NULL)){
                    printf("账户已被锁定，请稍后再试\n");
                    return 0;
                }
                printf("登录成功\n");
                current->lock_status = 0;
                current->lock_time = 0;
                role = current->type;   // 记录当前登录用户角
                
                //writeLog(username, "登录");
                
                return 1;
            }else{
                printf("账户状态异常，请联系管理员\n");
                return 0;
            }
        }
        error += 1;
        // 检查连续错误次数是否达到3次，达到则将账号锁定5分钟
        if(error == 3){
            printf("密码连续错误3次，账号锁定5分钟！\n");
            current->lock_status = 1;
            current->lock_time = time(NULL);
            writeUserInfo(username,current);   // 将当前用户的锁定信息写入用户文件
			writeLog(username,"账户被锁定");     // 记录登录失败，账户锁定日志
			
            return 0;
        }
        printf("密码错误，请重新输入！\n");
        printf("继续输入请按1，结束请按其他键: ");
        scanf(" %c",&flag1);
        if(flag1 != '1'){
            return 0;
        }
    }
}

int addUser(){
    // 新增用户
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    char user[20],password[20],realname[20],address[20],phone[12];
    while(1){
        printf("请输入用户名: ");
        scanf("%s",user);
        if(strlen(user) > 20){
            printf("用户名长度不能超过20个字符！\n");
            continue;
        }
        if(searchUser(user) == 1){
            printf("用户名已存在！\n");
            continue;
        }
        break;
    }
    while(1){
        printf("请输入密码: ");
        scanf("%s",password);
        if(strlen(password) > 20){
            printf("密码长度不能超过20个字符！\n");
            continue;
        }
        break;
    }
    printf("请输入姓名：");
    scanf("%s",realname);
    printf("请输入地址：");
    scanf("%s",address);
    printf("请输入电话号码：");
    scanf("%s",phone);
    
    
    //将用户信息保存到数据库
	//增加用户操作
	
	char sql[] = "insert into user (username, password, age,) values ( ? , ? , ? )";
	//char sql[] = "insert into user (username, password, age, phone, address) values ( ? , ? , ? , ? , ?)";
	//char sql[] = "delete from user where id >= ? ";
	insertData(sql);

    
    
    
    /*
    // 将用户信息保存到结构体中
    User *userinfo = (User *)malloc(sizeof(User));  // 申请内存
    userinfo->type = 1;
    strcpy(userinfo->password,password);
    strcpy(userinfo->realname,realname);
    strcpy(userinfo->address,address);
    strcpy(userinfo->phone,phone);
    userinfo->status = 1;
    userinfo->lock_status = 0;
    userinfo->lock_time = 0;
    
    */
    if(role == 0){
    	
    	pthread_t writeLogpid;		//创建记录日记信息的线程
			if(pthread_create( &writeLogpid, NULL, writeLog,  "添加用户") != 0){
				perror("创建线程失败！");
				return 1;
			}
		pthread_join(writeLogpid,NULL);		//回收线程
    
        //writeLog(username,"添加用户");
    }else{
    
    	pthread_t writeLogpid;		//创建记录日记信息的线程
			if(pthread_create( &writeLogpid, NULL, writeLog,  "添加用户") != 0){
				perror("创建线程失败！");
				return 1;
			}
		pthread_join(writeLogpid,NULL);		//回收线程
    
    
        //writeLog("新注册","添加用户");
    }
    
    return writeUserInfo(user,userinfo);
}
int main(int argc, char *argv[]) {

	firstUi();
    if(login_status == 1){
        secondUi();
    }	
	/*

	
/*
	// 新增
	char sql[] = "insert into user (user_name, password)values (?, ?)";
	Param params[2];
	params[0].type = Type_string;
	params[0].value.s = "小丽丽";
	params[1].type = Type_string;
	params[1].value.s = "x123456";

	// 删除
	char sql[] = "delete from user where id = ? ";
	Param params[1];
	params[0].type = Type_int;
	params[0].value.i = 6 ;
	
	// 修改
	char sql[] = "update user set user_name = ?, password = ? where id = ?";
	Param params[3];
	params[0].type = Type_string;
	params[0].value.s = "张三";
	params[1].type = Type_string;
	params[1].value.s = "z889900";
	params[2].type = Type_int;
	params[2].value.i = 7 ;
	
	int length = sizeof(params) / sizeof(params[0]);
	
	int rows = updateData(sql,params , length );
	printf("sql执行影响行数是：%d \n", rows );
*/

	// 查询 ---------------------------------------
	//char sql[] = "select * from user";
	//char sql[] = "select * from user where id = ?";
	char sql[] = "select * from user limit ?, ?";
	
	Param params[2];
	params[0].type = Type_int;
	params[0].value.i = 0 ;
	params[1].type = Type_int;
	params[1].value.i = 3 ;
	
	int length = sizeof(params) / sizeof(params[0]);
	sqlite3_stmt *stmt = selectData(sql, params, length );
	
	int count = 0;
	User *user = dataToUser(stmt, &count); 	
	for(int i = 0; i < count; i++){
		printf("id=%d , name=%s , password=%s \n", user[i].id, user[i].userName, user[i].password );
	}


	free(user);
    return 0;
}


