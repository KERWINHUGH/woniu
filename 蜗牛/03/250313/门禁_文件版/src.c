#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h> 
#include <unistd.h> 

typedef struct user {
    char password[20];
    char realname[20];
    char phone[12]; 
    char address[20];
    int type;     // 类型，1表示普通用户，0表示管理员
    int status;   // 状态，0表示正常，1表示异常
    int lock_status;  // 锁定状态，0表示正常，1表示锁定
    long lock_time;   // 锁定时间，时间戳标识
}User;

char *dir_path = "./users";
char username[20];       // 当前登录用户名
int role = 1;            // 当前登录用户角色，1表示普通用户，0表示管理员

void writeLog(char *username, char *log){
	// 写日志
    FILE *fp = fopen("log.txt", "a");
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", p);
    fprintf(fp, "%s\t%s\t\t%s\n", buffer, username, log);
    fclose(fp);
}

User *getUserInfo(char *username){
    // 根据用户名找到指定文件，从文件中读取用户信息保存在结构体中
    User *user = (User *)malloc(sizeof(User));  // 申请内存
    char file_path[100];
    sprintf(file_path, "%s/%s", dir_path, username);  // 得到文件路径
    FILE *fp = fopen(file_path, "r");
    if(fp == NULL){
        printf("文件打开失败\n");
        return NULL;
    }
	// 格式化读取文件内容
    fscanf(fp, "%s %s %s %s %d %d %d %ld", user->password, user->realname, user->phone, user->address, &user->type, &user->status, &user->lock_status, &user->lock_time);
    fclose(fp);
    return user;
}

int writeUserInfo(char *username, User *user){
    // 更新用户信息，即写入文件，成功返回1，否则返回-1
    char file_path[100];
    sprintf(file_path, "%s/%s", dir_path, username);
    FILE *fp = fopen(file_path, "w");
    if(fp == NULL){
        printf("文件打开失败\n");
        return -1;
    }
    fprintf(fp,"%s\t%s\t%s\t%s\t%d\t%d\t%d\t%ld",user->password, user->realname, user->phone, user->address, user->type, user->status, user->lock_status, user->lock_time);
    if(ferror(fp)){
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 1;
}

int searchUser(char *username){
    // 根据用户名搜索用户信息，即查找指定文件是否存在，存在返回1，否则返回-1
    char file_path[100];
    sprintf(file_path, "%s/%s", dir_path, username);
    // printf("文件路径：%s\n",file_path);
    if(access(file_path, F_OK) == 0){
        return 1;
    }
    return -1;
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
                role = current->type;   // 记录当前登录用户角色
                writeLog(username, "登录");
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
    if(role == 0){
        writeLog(username,"添加用户");
    }else{
        writeLog("新注册","添加用户");
    }
    
    return writeUserInfo(user,userinfo);
}

void displayAllUsersInfo(){
	// 管理员查询显示所有用户信息
    DIR *dir = opendir(dir_path);  // 打开目录
    struct dirent *ptr;  
    User *userinfo;
    int id = 1;
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("编号\t\t用户名\t\t姓名\t\t%-12s\t状态\n","地址");
    while((ptr = readdir(dir)) != NULL){
        if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
            continue;
        userinfo = getUserInfo(ptr->d_name);
        printf("%d\t\t%s\t\t%s\t\t%-12s\t%d\n",id,ptr->d_name,userinfo->realname,userinfo->address,userinfo->status);
        id += 1;
    }
    closedir(dir);
    writeLog(username, "获取所有用户");
}

void displayUserInfo(){
	// 显示用户详细信息
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    if(role == 0){
        printf("请输入用户名：");
        scanf("%s",username);
		if(searchUser(username) == -1){
			printf("用户不存在\n");
			return;
		}
    }
    printf("- - - - - - - - - - 详细信息  - - - - - - - - - - - -\n");
    User *userinfo = getUserInfo(username);
    printf("用户名: %s\t\t姓    名: %s\n", username, userinfo->realname);
    printf("手机号: %s\t地    址: %s\n", userinfo->phone, userinfo->address);
    char *role, *status;
    if(userinfo->type == 0){
        role = "管理员";
    }else{
        role = "普通用户";
    }
    if(userinfo->status == 1){
        status = "正常";
    }else{
        status = "异常";
    }
    printf("状  态: %s\t\t角    色: %s\n", status, role);
    if(userinfo->lock_status == 1){
        char buffer[100];
        time_t t = userinfo->lock_time;
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&t));
        printf("锁  定: 已锁定\t\t锁定时间: %s\n", buffer);
    }
    writeLog(username, "查询详细信息");
}

int deleteUser(){
	// 管理员删除用户
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("请输入要删除的用户名: ");
    char username[20];
    scanf("%s", username);
    if(searchUser(username) == -1){
        printf("用户不存在!\n");
        return -1;
    }
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "rm -rf %s/%s", dir_path, username);
    system(buffer);  // 执行删除文件命令
    printf("删除成功!\n");
    writeLog(username, "删除用户");
    return 1;
}

int modifyUserInfo(int choice){
	// 修改用户信息
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    if(role == 0){
        printf("请输入用户名: ");
        scanf("%s", username);
        if(searchUser(username) == -1){
            printf("用户不存在!\n");
            return -1;
        }
    }
    User *userinfo = getUserInfo(username);
    if(choice == 2 || choice == 5){
        char old[20],new[20],rep[20];
        if(role == 1){
            printf("请输入原密码: ");
            scanf("%s", old);
            if(strcmp(old, userinfo->password) != 0){
                printf("原密码错误!\n");
                return -1;
            }
        }
        printf("请输入新密码: ");
        scanf("%s", new);
        printf("请再次输入新密码: ");
        scanf("%s", rep);
        if(strcmp(new, rep) != 0){
            printf("两次输入的密码不一致!\n");
            return -1;
        }
        strcpy(userinfo->password, new);
        writeLog(username, "修改密码");
    }else if(choice == 3 || choice == 6){
        char p[12];
        printf("请输入新手机号: ");
        scanf("%s", p);
        strcpy(userinfo->phone, p);
        writeLog(username, "修改手机号");
    }else if(choice == 4 || choice == 7){
        char address[20];
        printf("请输入新地址: ");
        scanf("%s", address);
        strcpy(userinfo->address, address);
        writeLog(username, "修改地址");
    }else if(choice == 8){
        // 修改状态
        userinfo->status = 0;
        writeLog(username, "修改用户状态");
    }else if(choice == 9){
        // 解除锁定
        userinfo->lock_status = 0;
        userinfo->lock_time = 0;
        writeLog(username, "解除锁定");
    }
    return writeUserInfo(username, userinfo);
}


// int main(){
//     User *p = getUserInfo("user102");
//     printf("%d\n", p->lock_status);
//     return 0;
// }