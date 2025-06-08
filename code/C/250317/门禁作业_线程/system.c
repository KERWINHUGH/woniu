#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include "system.h"

char *dir_path = "./users";    //当前登录路径
char username[32];    //当前登录用户名
int role;        //当前登录用户类型

//写日志
void writeLog(char *username,char *log){
    FILE *fp = fopen("log.txt",'a');
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    char buffer[128];
    strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",p);
    fprintf(fp,"%s\t%s\t\t%s\n",buffer,username,log);
    fclose(fp);
}

//根据用户名找到指定文件，从文件中读取用户信息保存在结构体中
User *getUserInfo(char *username){
    User *user = (User *)malloc(sizeof(User));
    char file_path[100];    //数组用来存放用户文件夹路径
    sprintf(file_path,"%s/%s",dir_path,username);
    //以读取方式打开拼接好的用户文件夹
    FILE *fp = fopen(file_path,"r");
    if(fp == NULL){
        printf("文件打开失败!\n");
        return NULL;
    }
    //格式化读取拼接好且打开的用户文件夹中的内容
    fscanf(fp,"%s %s %s %s %d %d %d %ld",user->password,user->realname,user->phone,user->address,user->type,&user->status,&user->lock_status,&user->lock_time);
    fcolse(fp);
    return user;
}

//更新用户信息，写入文件，成功返回1，否则返回-1
//根据传入的用户名，找到用户所在文件夹，然后开始写入用户信息
int writeUserInfo(char *username,User *user){
    char file_path[100];    //数组用来存放用户文件夹路径
    //拼接用户文件夹路径
    sprintf(file_path,"%s/%s",dir_path,username);
    //以清空写入方式打开拼接好的用户文件夹
    FILE *fp = fopen(file_path,"w");
    if(fp == NULL){
        printf("文件打开失败!\n");
        return NULL;
    }
    fprintf(fp,"%s %s %s %s %d %d %d %ld",user->password,user->realname,user->phone,user->address,user->type,&user->status,&user->lock_status,&user->lock_time);
    if(ferror(fp)){
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 1;
}

//根据用户名拼接用户文件夹路径，搜索用户文件夹是否存在，存在返回1，不存在返回-1
int seachUser(char *username){
    char file_path[100];
    sptintf(file_path,"%s/%s",dir_path,username);
    if(access(file_path,F_OK)==0){
        return 1;
    }
    return -1;
}

//登录函数，登录成功写入日志并返回1，否则返回0
int login(){
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    char error = 0; //记录用户密码输入错误的次数
    //flag0、flag1用于判断用户是否继续输入
    char password[32],flag0 = '1', flag1 = '0';
    //使用do while先判断一次用户名是否存在，若存在然后再进行其他操作，不存在返回0
    do{
        printf("请输入用户名：");
        scanf(" %s",username);
        //用户名不存在
        if(searchUser(username) == -1){
            printf("用户名不存在，请重新输入!\n");
            printf("继续输入请按1，结束请按其他键：");
            scanf("%c",&flag0);
            if(flag0 != '1'){   //flag0=0，用户放弃继续输入，退出登录
                return 0;
            }
            //当次do while循环结束重新输入用户名，不执行flag0与flag1赋值
            continue;
        }
        //用户名存在
        flag0 = '0'; //退出当前循环    
        flag1 = '1'; //可以继续执行下面登录的操作
    }while(flag0 == '1');
    //用户存在的操作
    while(flag1 == '1'){
        printf("请输入密码：");
        scanf("%s",password);
        //将该用户信息读取出来保存到cunrrent临时结构体中
        User *current = getUserInfo(username);
        //检查密码是否正确
        if(strcmp(password,current->password)==0){
            if(current->status==0){
                //密码正确，在判断账户是否为锁定状态，current=1为锁定状态，记录的锁定时间+300s大于当前时间说明，锁定时间未达到五分钟
                if(current->lock_status == 1&&current->lock_time + 300>time(NULL)){
                    printf("账户已被锁定，请稍后再试或联系管理员。\n");
                    return 0;
                }
                //密码正确，账户未被锁定
                printf("登录成功\n");
                current->lock_status = 0;   //重新设定当前账户的锁定状态
                current->lock_time = 0;  //重新设定当前账户的锁定状态时间
                role = current->type;   //记录当前登录的类型
                return 1;
            }else{
                //账户状态异常情况
                printf("账户状态异常，请联系管理员！\n");
                return 0;
            }
        }
        //密码错误情况
        error +=1;  //记录输入密码错误次数
        //密码错误三次后锁定账号五分钟
        if(error == 3){
            printf("密码已连续输入错误3次，账号将锁定5分钟");
            current->lock_status = 1;   //将当前账户账号设为锁定状态
            current->lock_time = time(NULL);    //记录当前账号锁定时间
            writeUserInfo(username,current);    //将当前账户的锁定信息写入用户文件
            writeLog(username,"登录失败，账户被锁定");    //记录登记登记，账户锁定日志
            return 0;
        }
        //密码错误未达到三次的情况
        printf("密码错误，请重新输入！");
        printf("继续输入请按1，结束请按其他键：");
        scanf("%c",&flag1);
        if(flag1 != '1'){   //flag1=0，用户放弃继续输入密码，退出登录
            return 0;
        }

    }    
}

//新增用户
int addUser(){
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    char user[32],password[32],realname[32],address[128],phone[16];
    //一直循环判断用户名是否已经存在且用户名长度是否超过数组长度
    while(1){
        printf("请输入用户名");
        scanf("%s",user);
        if(strlen(user) > 32){
            printf("用户名长度不能超过32个字符！\n");
            continue;   //超过指定长度，继续重新输入用户名
        }
        if(searchUser(user) == 1){
            printf("用户名已存在！\n");
            continue;   //用户名存在也重新输入
        }
        //输入的用户名合法则退出当前whie循环
        break;
    }
    while(1){
        printf("请输入密码：");
        scanf("%s",password);
        if(strlen(password)>32){
            printf("密码长度不能超过32个字符");
            continue;
        }
        //密码合法则退出while循环
        break;
    }
    //输入用户名和密码均合法，保存其他用户信息
    printf("请输入姓名：");
    scanf("%s",realname);
    printf("请输入地址");
    scanf("%s",address);
    printf("请输入电话号码");
    scanf("%s",phone);
    //创建用户并保存输入的用户信息
    User *userinfo = (User *)malloc(sizeof(User));
    userinfo->type = 1;
    strcpy(userinfo->password,password);
    strcpy(userinfo->realname,realname);
    strcpy(userinfo->address,address);
    strcpy(userinfo->phone,phone);
    userinfo->status = 1;
    userinfo->lock_status = 0;
    userinfo->lock_time = 0;

    if(role == 0){//如果是管理员用户写日志
        writeLog(username,"添加用户");
    }else{//如果是普通用户写日志
        writeLoh("新注册","添加用户");
    }
    //将用户信息写入用户文件
    return writeUserInfo(user,userinfo);//写入成功返回1
}

//管理员类型查询所有用户信息
void displayAllUserInfo(){
    
}